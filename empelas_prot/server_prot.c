/*
 * EmPowerElas - Maquete de Subestacao Digital
 * IED de medicao e protecao (Raspberry Pi 1): EmpElas_PROT
 *
 * Recebe as amostras de corrente e tensao da merging unit (EmpElas_MU) por
 * Sampled Values (4800 amostras por segundo) e, a cada ciclo de 60 Hz
 * (80 amostras):
 *   - calcula o valor eficaz (RMS) das correntes e tensoes das tres fases;
 *   - roda a protecao de sobrecorrente de fase (PTOC1).
 * Quando a protecao atua, o trip (PTRC1.Tr) e publicado por GOOSE para o IED
 * de controle de vao (EmpElas_CTRL), que abre o disjuntor. O trip e
 * tripolar: o disjuntor abre as tres fases juntas, qualquer que seja a fase
 * com defeito.
 *
 * Displays (LCD 1602):
 *   LCD1 linha 1: estado (CORRENTE (A) / TRIP <fases> ->GOOSE / SEM SINAL DA MU)
 *   LCD1 linha 2: correntes das fases A, B e C (A)
 *   LCD2 linha 1: TENSAO FASE (kV)
 *   LCD2 linha 2: tensoes das fases A, B e C (kV)
 *
 * Supervisorio (MMXU1, formato da norma): A (correntes), PhV (tensoes de
 * fase) e PPV (tensoes entre fases). Atualizado a cada segundo e na hora em
 * que a protecao muda de estado.
 *
 * Nao existe mais botao de falta aqui: a falta acontece na "linha", que e a
 * merging unit. Este IED so mede e decide, como um rele real.
 *
 * Compilar e rodar nesta Pi:
 *   make modelo   (sempre que o .icd mudar)
 *   make
 *   sudo ./empelas_prot
 */

#include "iec61850_server.h"
#include "hal_thread.h"
#include "sv_subscriber.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <wiringPi.h>
#include <lcd.h>            // biblioteca de LCD do wiringPi (link: -lwiringPiDev)

// ================= DISPLAY 1 (correntes) =================
#define LCD1_RS  7   // wPi 7  = Fisico 7
#define LCD1_E   11  // wPi 11 = Fisico 26
#define LCD1_D4  12  // wPi 12 = Fisico 19
#define LCD1_D5  13  // wPi 13 = Fisico 21
#define LCD1_D6  14  // wPi 14 = Fisico 23
#define LCD1_D7  26  // wPi 26 = Fisico 32

// ================= DISPLAY 2 (tensoes) ===================
#define LCD2_RS  0   // wPi 0  = Fisico 11
#define LCD2_E   6   // wPi 6  = Fisico 22
#define LCD2_D4  2   // wPi 2  = Fisico 13
#define LCD2_D5  3   // wPi 3  = Fisico 15
#define LCD2_D6  22  // wPi 22 = Fisico 31
#define LCD2_D7  27  // wPi 27 = Fisico 36

// ================= REDE ====================================
// O SV chega e o GOOSE sai pelo CABO (roteador da maquete).
#ifndef INTERFACE_SV
#define INTERFACE_SV     "eth0"
#endif
#ifndef INTERFACE_GOOSE
#define INTERFACE_GOOSE  "eth0"
#endif

// SV da merging unit: precisa bater com o empelas_mu.icd e o server_mu.c
#define SV_APPID            0x4000
#define SV_ID               "EmpElas_MU01"
static uint8_t SV_DSTMAC[6] = {0x01, 0x0C, 0xCD, 0x04, 0x00, 0x01};
#define AMOSTRAS_POR_CICLO  80
#define AMOSTRAS_POR_SEG    4800
#define ESCALA_I            0.001   // 1 unidade = 1 mA
#define ESCALA_V            0.01    // 1 unidade = 10 mV

// Sem amostras por mais que isto: medicao invalida e protecao bloqueada
#define SV_TIMEOUT_MS       100

// ================= PROTECAO ================================
#define PTOC_PARTIDA        300.0   // ajuste da sobrecorrente de fase (A)

// ============================================================

#include "static_model.h"

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

static volatile int running = 0;
static IedServer iedServer = NULL;
static int lcd1 = -1;   // handle do display 1 (correntes)
static int lcd2 = -1;   // handle do display 2 (tensoes)

void sigint_handler(int signalId) { running = 0; }

// ----------------------------------------------------------------
// Garante que so existe uma copia deste programa rodando na Pi. Duas
// copias ao mesmo tempo publicariam mensagens repetidas na rede (e a
// segunda nem consegue usar a porta 102). A trava some sozinha quando o
// programa fecha, mesmo se ele cair.
// ----------------------------------------------------------------
static int travarInstancia(const char* nome) {
    char caminho[96];
    snprintf(caminho, sizeof(caminho), "/tmp/%s.lock", nome);
    int fd = open(caminho, O_CREAT | O_RDWR, 0666);
    if (fd < 0) return 1;                         // sem trava, segue assim mesmo
    if (flock(fd, LOCK_EX | LOCK_NB) != 0) return 0;
    return 1;                                     // o arquivo fica aberto ate o fim
}

// ----------------------------------------------------------------
// Pede para a placa de rede aceitar o endereco de grupo do SV.
//
// Sem isso, a placa descarta as mensagens de SV antes de chegarem no
// programa (a versao 1.6 da libiec61850 nao faz esse pedido sozinha para
// o SV; para o GOOSE ela faz). O pedido vale enquanto este socket estiver
// aberto, ou seja, enquanto o programa rodar. O socket nao recebe nada.
// ----------------------------------------------------------------
static int sockGrupoSV = -1;

static void aceitarGrupoSV(const char* interface, const uint8_t* mac) {
    sockGrupoSV = socket(AF_PACKET, SOCK_RAW, 0);
    if (sockGrupoSV < 0) {
        LOG_PRINT("[SV] Aviso: nao consegui pedir o grupo do SV (rode com sudo).\n");
        return;
    }
    struct packet_mreq mr;
    memset(&mr, 0, sizeof(mr));
    mr.mr_ifindex = (int) if_nametoindex(interface);
    mr.mr_type = PACKET_MR_MULTICAST;
    mr.mr_alen = 6;
    memcpy(mr.mr_address, mac, 6);
    if (mr.mr_ifindex == 0 ||
        setsockopt(sockGrupoSV, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) != 0)
        LOG_PRINT("[SV] Aviso: a placa %s nao aceitou o grupo do SV. Se nada chegar, rode:\n"
                  "     sudo ip link set %s allmulticast on\n", interface, interface);
}

// Valores eficazes de um ciclo
typedef struct {
    double i[4];     // IA, IB, IC, IN (A)
    double v[4];     // VA, VB, VC, VN (V)
    double vll[3];   // VAB, VBC, VCA (V)
} Medidas;

// Ultimo ciclo completo (escrito pela thread do SV, lido pela dos displays)
static pthread_mutex_t mtxMed = PTHREAD_MUTEX_INITIALIZER;
static Medidas ultimaMedida;
static int64_t ultimoCicloMs = 0;          // relogio monotonico
static volatile uint32_t svCiclos = 0, svPerdidas = 0, svRepetidas = 0, svOutros = 0;

// Estado da protecao: fases em sobrecorrente (bit 0 = A, 1 = B, 2 = C)
static pthread_mutex_t mtxProt = PTHREAD_MUTEX_INITIALIZER;
static volatile int fasesAtuadas = 0;

static int64_t agoraMs(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (int64_t) t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

static void textoFases(int fases, char* s) {
    int k = 0;
    if (fases & 1) s[k++] = 'A';
    if (fases & 2) s[k++] = 'B';
    if (fases & 4) s[k++] = 'C';
    s[k] = '\0';
}

// ----------------------------------------------------------------
// Protecao de sobrecorrente de fase, sem atraso (funcao ANSI 50).
//
// Roda a cada ciclo, com o RMS das tres fases. So escreve no modelo quando
// o estado muda: o PTRC1.Tr.general esta no conjunto de dados do GOOSE, e
// cada mudanca dele dispara uma mensagem nova. O selo de tempo e o do
// instante da deteccao.
//
// medicaoValida = false (sem SV): a protecao fica bloqueada e solta tudo.
// ----------------------------------------------------------------
static void avaliarProtecao(const double iFase[3], bool medicaoValida, uint64_t ts) {
    int fases = 0;
    if (medicaoValida) {
        if (iFase[0] > PTOC_PARTIDA) fases |= 1;
        if (iFase[1] > PTOC_PARTIDA) fases |= 2;
        if (iFase[2] > PTOC_PARTIDA) fases |= 4;
    }

    pthread_mutex_lock(&mtxProt);
    int antes = fasesAtuadas;
    if (fases == antes) {
        pthread_mutex_unlock(&mtxProt);
        return;
    }
    fasesAtuadas = fases;
    bool geral = (fases != 0);
    bool geralAntes = (antes != 0);

    IedServer_lockDataModel(iedServer);
    // Partida (Str) e operacao (Op): sem atraso, mudam juntas
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_general, geral);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_phsA, (fases & 1) != 0);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_phsB, (fases & 2) != 0);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_phsC, (fases & 4) != 0);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_t, ts);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_general, geral);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_phsA, (fases & 1) != 0);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_phsB, (fases & 2) != 0);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_phsC, (fases & 4) != 0);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_t, ts);
    // Trip tripolar. Esta e a escrita que dispara o GOOSE (PTRC1.Tr.general esta no dsTrip)
    if (geral != geralAntes) {
        IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_general, geral);
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_t, ts);
    }
    IedServer_unlockDataModel(iedServer);
    pthread_mutex_unlock(&mtxProt);

    char f[4];
    textoFases(fases, f);
    if (geral && !geralAntes) {
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[PROTECAO] Sobrecorrente na fase %s (IA %.1f  IB %.1f  IC %.1f A; ajuste %.0f A).\n",
                  f, iFase[0], iFase[1], iFase[2], PTOC_PARTIDA);
        LOG_PRINT("           TRIP publicado por GOOSE.\n");
        LOG_PRINT("--------------------------------------------------\n");
    } else if (geral) {
        LOG_PRINT("[PROTECAO] Fases em sobrecorrente agora: %s.\n", f);
    } else if (medicaoValida) {
        LOG_PRINT("[PROTECAO] Corrente normalizada. Trip retirado, GOOSE publicado.\n");
    } else {
        LOG_PRINT("[PROTECAO] Sem medicao: protecao bloqueada, trip retirado.\n");
    }
}

// ----------------------------------------------------------------
// Chamada a cada mensagem de SV (4800 por segundo), na thread do receptor.
//
// Soma o quadrado de cada amostra; a cada 80 amostras (um ciclo) tira a
// raiz da media: e o valor eficaz (RMS) do ciclo. Repeticoes (mesmo
// smpCnt) sao ignoradas e saltos no smpCnt contam como amostras perdidas.
//
// Se faltar alguma amostra, ou se o SV tinha parado e voltou, o ciclo que
// estava pela metade e descartado. Sem isso, o primeiro "ciclo" misturaria
// amostras velhas com novas e poderia dar um valor errado (e um trip falso).
// ----------------------------------------------------------------
static double soma[11];
static int nSoma = 0;
static int ultimoSmpCnt = -1;
static int64_t ultimaAmostraMs = 0;

static void aoReceberSV(SVSubscriber sub, void* parameter, SVSubscriber_ASDU asdu) {
    const char* id = SVSubscriber_ASDU_getSvId(asdu);
    if (id == NULL || strcmp(id, SV_ID) != 0 || SVSubscriber_ASDU_getDataSize(asdu) < 64) {
        svOutros++;
        return;
    }

    int smpCnt = SVSubscriber_ASDU_getSmpCnt(asdu);
    if (smpCnt == ultimoSmpCnt) {
        svRepetidas++;
        return;
    }

    int64_t agora = agoraMs();
    bool svTinhaParado = (agora - ultimaAmostraMs > SV_TIMEOUT_MS);
    bool lacuna = svTinhaParado;
    if (!svTinhaParado && ultimoSmpCnt >= 0) {
        int esperado = (ultimoSmpCnt + 1) % AMOSTRAS_POR_SEG;
        if (smpCnt != esperado) {
            svPerdidas += (smpCnt - esperado + AMOSTRAS_POR_SEG) % AMOSTRAS_POR_SEG;
            lacuna = true;
        }
    }
    ultimoSmpCnt = smpCnt;
    ultimaAmostraMs = agora;

    if (lacuna) {                    // descarta o ciclo incompleto
        memset(soma, 0, sizeof(soma));
        nSoma = 0;
    }

    // 8 canais: valor (4 bytes) + qualidade (4 bytes) cada
    double x[8];
    for (int ch = 0; ch < 8; ch++)
        x[ch] = SVSubscriber_ASDU_getINT32(asdu, ch * 8) * ((ch < 4) ? ESCALA_I : ESCALA_V);

    for (int ch = 0; ch < 8; ch++)
        soma[ch] += x[ch] * x[ch];
    double vab = x[4] - x[5], vbc = x[5] - x[6], vca = x[6] - x[4];
    soma[8] += vab * vab;
    soma[9] += vbc * vbc;
    soma[10] += vca * vca;
    nSoma++;

    if (nSoma < AMOSTRAS_POR_CICLO)
        return;

    // Fechou um ciclo
    Medidas m;
    for (int k = 0; k < 4; k++) m.i[k] = sqrt(soma[k] / nSoma);
    for (int k = 0; k < 4; k++) m.v[k] = sqrt(soma[4 + k] / nSoma);
    for (int k = 0; k < 3; k++) m.vll[k] = sqrt(soma[8 + k] / nSoma);
    memset(soma, 0, sizeof(soma));
    nSoma = 0;

    pthread_mutex_lock(&mtxMed);
    ultimaMedida = m;
    ultimoCicloMs = agoraMs();
    svCiclos++;
    pthread_mutex_unlock(&mtxMed);

    avaliarProtecao(m.i, true, Hal_getTimeInMs());
}

// ----------------------------------------------------------------
// Supervisorio: MMXU1 (A em amperes, PhV e PPV em kV)
// ----------------------------------------------------------------
static void publicarMedicoes(const Medidas* m, bool valida, uint64_t ts) {
    DataAttribute* magA[4] = { IEDMODEL_MEDPROT_MMXU1_A_phsA_cVal_mag_f, IEDMODEL_MEDPROT_MMXU1_A_phsB_cVal_mag_f,
                               IEDMODEL_MEDPROT_MMXU1_A_phsC_cVal_mag_f, IEDMODEL_MEDPROT_MMXU1_A_neut_cVal_mag_f };
    DataAttribute* qA[4]   = { IEDMODEL_MEDPROT_MMXU1_A_phsA_q, IEDMODEL_MEDPROT_MMXU1_A_phsB_q,
                               IEDMODEL_MEDPROT_MMXU1_A_phsC_q, IEDMODEL_MEDPROT_MMXU1_A_neut_q };
    DataAttribute* tA[4]   = { IEDMODEL_MEDPROT_MMXU1_A_phsA_t, IEDMODEL_MEDPROT_MMXU1_A_phsB_t,
                               IEDMODEL_MEDPROT_MMXU1_A_phsC_t, IEDMODEL_MEDPROT_MMXU1_A_neut_t };
    DataAttribute* magV[4] = { IEDMODEL_MEDPROT_MMXU1_PhV_phsA_cVal_mag_f, IEDMODEL_MEDPROT_MMXU1_PhV_phsB_cVal_mag_f,
                               IEDMODEL_MEDPROT_MMXU1_PhV_phsC_cVal_mag_f, IEDMODEL_MEDPROT_MMXU1_PhV_neut_cVal_mag_f };
    DataAttribute* qV[4]   = { IEDMODEL_MEDPROT_MMXU1_PhV_phsA_q, IEDMODEL_MEDPROT_MMXU1_PhV_phsB_q,
                               IEDMODEL_MEDPROT_MMXU1_PhV_phsC_q, IEDMODEL_MEDPROT_MMXU1_PhV_neut_q };
    DataAttribute* tV[4]   = { IEDMODEL_MEDPROT_MMXU1_PhV_phsA_t, IEDMODEL_MEDPROT_MMXU1_PhV_phsB_t,
                               IEDMODEL_MEDPROT_MMXU1_PhV_phsC_t, IEDMODEL_MEDPROT_MMXU1_PhV_neut_t };
    DataAttribute* magL[3] = { IEDMODEL_MEDPROT_MMXU1_PPV_phsAB_cVal_mag_f, IEDMODEL_MEDPROT_MMXU1_PPV_phsBC_cVal_mag_f,
                               IEDMODEL_MEDPROT_MMXU1_PPV_phsCA_cVal_mag_f };
    DataAttribute* qL[3]   = { IEDMODEL_MEDPROT_MMXU1_PPV_phsAB_q, IEDMODEL_MEDPROT_MMXU1_PPV_phsBC_q,
                               IEDMODEL_MEDPROT_MMXU1_PPV_phsCA_q };
    DataAttribute* tL[3]   = { IEDMODEL_MEDPROT_MMXU1_PPV_phsAB_t, IEDMODEL_MEDPROT_MMXU1_PPV_phsBC_t,
                               IEDMODEL_MEDPROT_MMXU1_PPV_phsCA_t };

    // Sem SV: o ultimo valor fica, mas marcado como invalido
    Quality q = valida ? QUALITY_VALIDITY_GOOD : (QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE);

    IedServer_lockDataModel(iedServer);
    for (int k = 0; k < 4; k++) {
        if (valida) IedServer_updateFloatAttributeValue(iedServer, magA[k], (float) m->i[k]);
        IedServer_updateQuality(iedServer, qA[k], q);
        IedServer_updateUTCTimeAttributeValue(iedServer, tA[k], ts);
        if (valida) IedServer_updateFloatAttributeValue(iedServer, magV[k], (float) (m->v[k] / 1000.0));
        IedServer_updateQuality(iedServer, qV[k], q);
        IedServer_updateUTCTimeAttributeValue(iedServer, tV[k], ts);
    }
    for (int k = 0; k < 3; k++) {
        if (valida) IedServer_updateFloatAttributeValue(iedServer, magL[k], (float) (m->vll[k] / 1000.0));
        IedServer_updateQuality(iedServer, qL[k], q);
        IedServer_updateUTCTimeAttributeValue(iedServer, tL[k], ts);
    }
    IedServer_unlockDataModel(iedServer);
}

// ----------------------------------------------------------------
// Displays
// ----------------------------------------------------------------
static void lcdLinha(int lcd, int linha, const char* texto) {
    char buf[17];
    snprintf(buf, sizeof(buf), "%-16.16s", texto);   // completa ou corta em 16 letras
    lcdPosition(lcd, 0, linha);
    lcdPuts(lcd, buf);
}

static int ate999(double x) {
    long r = lround(x);
    if (r < 0) r = 0;
    if (r > 999) r = 999;
    return (int) r;
}

static void atualizarDisplays(const Medidas* m, bool svOk, int fases) {
    char l[40];

    if (lcd1 >= 0) {
        if (!svOk) {
            lcdLinha(lcd1, 0, "SEM SINAL DA MU");
        } else if (fases) {
            char f[4];
            textoFases(fases, f);
            snprintf(l, sizeof(l), "TRIP %-3s ->GOOSE", f);
            lcdLinha(lcd1, 0, l);
        } else {
            lcdLinha(lcd1, 0, "CORRENTE (A)");
        }
        if (svOk) snprintf(l, sizeof(l), "A%3d B%3d C%3d", ate999(m->i[0]), ate999(m->i[1]), ate999(m->i[2]));
        else      snprintf(l, sizeof(l), "A--- B--- C---");
        lcdLinha(lcd1, 1, l);
    }

    if (lcd2 >= 0) {
        lcdLinha(lcd2, 0, "TENSAO FASE (kV)");
        if (svOk) snprintf(l, sizeof(l), "A%3d B%3d C%3d", ate999(m->v[0] / 1000.0),
                           ate999(m->v[1] / 1000.0), ate999(m->v[2] / 1000.0));
        else      snprintf(l, sizeof(l), "A--- B--- C---");
        lcdLinha(lcd2, 1, l);
    }
}

// ----------------------------------------------------------------
// Thread dos displays e do supervisorio. Tambem vigia o SV: se a merging
// unit parar de mandar amostras, a medicao fica invalida e a protecao e
// bloqueada.
// ----------------------------------------------------------------
void* display_thread(void* arg) {
    bool svOkAntes = false;
    int fasesAntes = -1;
    int64_t ultimoMmxu = 0, ultimoLcd = 0, ultimoLog = 0;
    uint32_t perdidasAntes = 0;

    while (running) {
        Medidas m;
        pthread_mutex_lock(&mtxMed);
        m = ultimaMedida;
        int64_t tCiclo = ultimoCicloMs;
        uint32_t perdidas = svPerdidas;
        pthread_mutex_unlock(&mtxMed);

        int64_t agora = agoraMs();
        bool svOk = (tCiclo > 0) && (agora - tCiclo < SV_TIMEOUT_MS);

        if (svOk != svOkAntes) {
            if (svOk) {
                LOG_PRINT("[SV] Recebendo a merging unit (%s).\n", SV_ID);
            } else if (tCiclo > 0) {
                LOG_PRINT("[SV] Sem sinal da merging unit! Medicao invalida e protecao bloqueada.\n");
                double zero[3] = {0, 0, 0};
                avaliarProtecao(zero, false, Hal_getTimeInMs());
            }
        }

        int fases = fasesAtuadas;
        bool mudou = (svOk != svOkAntes) || (fases != fasesAntes);

        if (mudou || agora - ultimoMmxu >= 1000) {
            publicarMedicoes(&m, svOk, Hal_getTimeInMs());
            ultimoMmxu = agora;
        }
        if (mudou || agora - ultimoLcd >= 500) {
            atualizarDisplays(&m, svOk, fases);
            ultimoLcd = agora;
        }
        if (agora - ultimoLog >= 5000) {
            if (svOk)
                LOG_PRINT("[MEDICAO] IA %.1f IB %.1f IC %.1f IN %.1f A | VA %.1f VB %.1f VC %.1f kV | SV perdidas: %u\n",
                          m.i[0], m.i[1], m.i[2], m.i[3], m.v[0] / 1000, m.v[1] / 1000, m.v[2] / 1000,
                          (unsigned) (perdidas - perdidasAntes));
            perdidasAntes = perdidas;
            ultimoLog = agora;
        }

        svOkAntes = svOk;
        fasesAntes = fases;
        Thread_sleep(50);
    }
    return NULL;
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    if (!travarInstancia("empelas_prot")) {
        LOG_PRINT("ERRO: o empelas_prot ja esta rodando nesta Pi. Feche o outro (Ctrl+C no terminal dele)\n"
                  "      ou procure com:  ps aux | grep empelas_prot\n");
        exit(1);
    }

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "ERRO: Falha ao inicializar o wiringPi! Rode como root (sudo).\n");
        exit(1);
    }

    // Inicializa os dois displays (modo 4 bits)
    lcd1 = lcdInit(2, 16, 4, LCD1_RS, LCD1_E, LCD1_D4, LCD1_D5, LCD1_D6, LCD1_D7, 0, 0, 0, 0);
    lcd2 = lcdInit(2, 16, 4, LCD2_RS, LCD2_E, LCD2_D4, LCD2_D5, LCD2_D6, LCD2_D7, 0, 0, 0, 0);
    if (lcd1 >= 0) { lcdClear(lcd1); lcdLinha(lcd1, 0, "EmpElas PROT"); lcdLinha(lcd1, 1, "Aguardando MU"); }
    if (lcd2 >= 0) { lcdClear(lcd2); lcdLinha(lcd2, 0, "TENSAO FASE (kV)"); lcdLinha(lcd2, 1, "A--- B--- C---"); }

    // Silencia os printf's padrao da biblioteca (LOG_PRINT usa stderr e continua aparecendo)
    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    // GOOSE sai pelo cabo
    IedServer_setGooseInterfaceId(iedServer, INTERFACE_GOOSE);
    IedServer_start(iedServer, tcpPort);
    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    // Habilita a publicacao de todos os blocos GOOSE do modelo (gcbTrip)
    IedServer_enableGoosePublishing(iedServer);

    // Assinatura do SV da merging unit
    SVReceiver svReceiver = SVReceiver_create();
    SVReceiver_setInterfaceId(svReceiver, INTERFACE_SV);
    SVSubscriber svSub = SVSubscriber_create(SV_DSTMAC, SV_APPID);
    SVSubscriber_setListener(svSub, aoReceberSV, NULL);
    SVReceiver_addSubscriber(svReceiver, svSub);
    SVReceiver_start(svReceiver);
    aceitarGrupoSV(INTERFACE_SV, SV_DSTMAC);

    LOG_PRINT("\n--- EmpElas_PROT : MEDICAO (SV da merging unit) E PROTECAO ---\n");
    LOG_PRINT("[STATUS] LCD1 (correntes) %s | LCD2 (tensoes) %s\n", (lcd1 >= 0) ? "OK" : "FALHOU", (lcd2 >= 0) ? "OK" : "FALHOU");
    LOG_PRINT("[STATUS] Rodando na porta %d.\n", tcpPort);
    if (SVReceiver_isRunning(svReceiver))
        LOG_PRINT("[SV]     Assinando %s em %s (APPID 0x%04X). Aguardando a merging unit...\n", SV_ID, INTERFACE_SV, SV_APPID);
    else
        LOG_PRINT("[SV]     ERRO: receptor de SV nao iniciou. Confira se %s existe e se rodou com sudo.\n", INTERFACE_SV);
    LOG_PRINT("[GOOSE]  Publicando gcbTrip em %s (APPID 0x1001).\n", INTERFACE_GOOSE);
    LOG_PRINT("[PROTECAO] Sobrecorrente de fase, sem atraso, partida em %.0f A. Trip tripolar.\n", PTOC_PARTIDA);

    running = 1;
    Thread displayThread = Thread_create((ThreadExecutionFunction) display_thread, NULL, false);
    Thread_start(displayThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    SVReceiver_stop(svReceiver);
    SVReceiver_destroy(svReceiver);
    if (sockGrupoSV >= 0) close(sockGrupoSV);
    Thread_destroy(displayThread);
    IedServer_disableGoosePublishing(iedServer);
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    if (dev_null != -1) close(dev_null);
    return 0;
}
