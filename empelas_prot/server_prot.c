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
 *   (o LCD2 mostra os avisos das chaves por alguns segundos)
 *
 * Supervisorio (MMXU1, formato da norma): A (correntes), PhV (tensoes de
 * fase) e PPV (tensoes entre fases). Atualizado a cada segundo e na hora em
 * que a protecao muda de estado.
 *
 * Nao existe mais botao de falta aqui: a falta acontece na "linha", que e a
 * merging unit. Este IED so mede e decide, como um rele real.
 *
 * IED DE CONTROLE DAS CHAVES (CSWI1-3 e CILO1-3)
 * O operador manda abrir ou fechar a chave N no CSWIn (supervisorio, MMS).
 * Antes de aceitar, o CILOn confere o intertravamento: a chave N so abre ou
 * fecha com o disjuntor N ABERTO (a seccionadora nao foi feita para cortar
 * corrente). Liberado, o comando sai por GOOSE (gcbCmd: CSWIn.OpOpn ou
 * CSWIn.OpCls) para a Pi do servo. A Pi do servo publica de volta, tambem
 * por GOOSE (gcbPos), a posicao dos disjuntores e das chaves: e dai que o
 * intertravamento sabe o que esta aberto, e e assim que o comando e
 * confirmado. Sem esse GOOSE, as posicoes ficam desconhecidas e todas as
 * chaves ficam bloqueadas.
 *
 * Avisos das chaves aparecem por alguns segundos no LCD2 (no lugar das
 * tensoes): CH1 BLOQUEADA / ABRA O DJ1 ANTES, CH1 ABRINDO..., CH1 ABERTA.
 *
 * Compilar e rodar nesta Pi:
 *   make modelo   (sempre que o .icd mudar)
 *   make
 *   sudo ./empelas_prot
 */

#define _GNU_SOURCE        // F_SETPIPE_SZ (tamanho do cano do som)
#include "iec61850_server.h"
#include "hal_thread.h"
#include "sv_subscriber.h"
#include "goose_receiver.h"
#include "goose_subscriber.h"
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/timex.h>     // adjtimex: o relogio esta sincronizado?
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/wait.h>      // waitpid: fim do aplay do som
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

// ================= CHAVES (CSWI + CILO) =====================
// Posicoes vindas da Pi do servo. Valores IGUAIS aos do empelas_ctrl.icd.
// O dsPos traz, nesta ordem: XCBR1, XCBR2, XCBR3, XSWI1, XSWI2, XSWI3.
#define GOOSE_POS_REF       "EmpElas_CTRLVAO/LLN0$GO$gcbPos"
#define GOOSE_POS_APPID     0x1002
static uint8_t GOOSE_POS_DSTMAC[6] = {0x01, 0x0C, 0xCD, 0x01, 0x00, 0x02};

// O GOOSE de posicoes se repete a cada 1 s mesmo sem mudanca. Se passar
// disto sem nenhuma mensagem, as posicoes ficam desconhecidas e todas as
// chaves ficam bloqueadas (cabo solto ou Pi do servo desligada).
#define POS_TIMEOUT_MS      3000
// Tempo que a chave tem para chegar na posicao pedida
#define CMD_TIMEOUT_MS      3000
// Quanto tempo um aviso das chaves fica no LCD2
#define AVISO_MS            4000

// Posicao de ponto duplo, no mesmo formato da Pi do servo e do supervisorio
// (MmsValue_getBitStringAsInteger)
#define POS_INTERMEDIARIA   0       // em movimento
#define POS_ABERTA          1
#define POS_FECHADA         2
#define POS_INVALIDA        3

// Motivos de bloqueio do intertravamento
#define LIBERADA            0
#define BLOQ_SEM_POSICOES   1       // sem GOOSE da Pi do servo
#define BLOQ_DJ_FECHADO     2       // disjuntor do vao fechado
#define BLOQ_DJ_INDEFINIDO  3       // disjuntor em movimento ou invalido

// ============================================================

#include "static_model.h"

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

static volatile int running = 0;
static IedServer iedServer = NULL;
static int lcd1 = -1;   // handle do display 1 (correntes)
static int lcd2 = -1;   // handle do display 2 (tensoes)

void sigint_handler(int signalId) { running = 0; }

// ----------------------------------------------------------------
// Relogio. O chrony acerta as tres Pis pelo cabo (a Pi das telinhas e o
// relogio da maquete) e avisa o sistema quando o relogio esta sincronizado.
// Os horarios (t) que este IED publica saem marcados conforme esse estado:
// sincronizado ou "relogio nao sincronizado". Confere a cada 5 s.
// ----------------------------------------------------------------
static void atualizarRelogio(void) {
    static int antes = -1;
    struct timex tx;
    memset(&tx, 0, sizeof(tx));                  // modes = 0: so consulta
    int sinc = (adjtimex(&tx) != TIME_ERROR);
    IedServer_setTimeQuality(iedServer, true, false, !sinc, 10);
    if (sinc != antes) {
        if (sinc) LOG_PRINT("[RELOGIO] Relogio sincronizado (chrony): horarios marcados como sincronizados.\n");
        else      LOG_PRINT("[RELOGIO] Relogio SEM sincronismo: horarios marcados como nao sincronizados.\n");
        antes = sinc;
    }
}

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

// Grava um booleano no modelo. semAviso = true: grava direto, sem disparar
// relatorio nem GOOSE (usado quando outro atributo do mesmo dado vai avisar).
static void escreverBool(DataAttribute* da, bool valor, bool semAviso) {
    if (semAviso) MmsValue_setBoolean(da->mmsValue, valor);
    else          IedServer_updateBooleanAttributeValue(iedServer, da, valor);
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
    // Horarios primeiro. O relatorio de eventos copia o dado inteiro (valor,
    // qualidade e horario) quando o valor muda, entao o horario ja precisa
    // estar certo nessa hora.
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_t, ts);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_t, ts);
    if (geral != geralAntes)
        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_t, ts);

    // Partida (Str) e operacao (Op): sem atraso, mudam juntas. Quando o
    // "general" tambem muda, as fases sao gravadas sem avisar o relatorio:
    // quem avisa e o general, uma vez so, com as fases ja certas.
    bool soGeral = (geral != geralAntes);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Str_phsA, (fases & 1) != 0, soGeral);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Str_phsB, (fases & 2) != 0, soGeral);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Str_phsC, (fases & 4) != 0, soGeral);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_general, geral);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Op_phsA, (fases & 1) != 0, soGeral);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Op_phsB, (fases & 2) != 0, soGeral);
    escreverBool(IEDMODEL_MEDPROT_PTOC1_Op_phsC, (fases & 4) != 0, soGeral);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_general, geral);
    // Trip tripolar. Esta e a escrita que dispara o GOOSE (PTRC1.Tr.general esta no dsTrip)
    if (geral != geralAntes)
        IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_general, geral);
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

// ================================================================
// CHAVES: comando (CSWI1-3) e intertravamento (CILO1-3)
// ================================================================

// Estado vindo do patio e comandos em andamento
static pthread_mutex_t mtxChaves = PTHREAD_MUTEX_INITIALIZER;
static int posDj[3] = {POS_INVALIDA, POS_INVALIDA, POS_INVALIDA};   // disjuntores 1, 2 e 3
static int posCh[3] = {POS_INVALIDA, POS_INVALIDA, POS_INVALIDA};   // chaves 1, 2 e 3
static int64_t ultimoPosMs = 0;     // ultimo GOOSE de posicoes (relogio monotonico)
static int pedido[3];               // aceito pelo operador, ainda nao publicado (0, POS_ABERTA, POS_FECHADA)
static int emCurso[3];              // publicado no GOOSE, esperando a chave chegar la

// Numero da chave (0, 1, 2) como a letra '1', '2', '3' para o LCD
#define DIGITO(n) ((char) ('1' + (n)))

// Aviso temporario no LCD2
static pthread_mutex_t mtxAviso = PTHREAD_MUTEX_INITIALIZER;
static char avisoL1[17], avisoL2[17];
static int64_t avisoAteMs = 0;
static volatile uint32_t avisoSeq = 0;

static void avisoLcd(const char* l1, const char* l2) {
    pthread_mutex_lock(&mtxAviso);
    snprintf(avisoL1, sizeof(avisoL1), "%s", l1);
    snprintf(avisoL2, sizeof(avisoL2), "%s", l2);
    avisoAteMs = agoraMs() + AVISO_MS;
    avisoSeq++;
    pthread_mutex_unlock(&mtxAviso);
}

// "aberta" para chave, "aberto" para disjuntor
static const char* textoPos(int p, bool chave) {
    switch (p) {
    case POS_ABERTA:        return chave ? "aberta" : "aberto";
    case POS_FECHADA:       return chave ? "fechada" : "fechado";
    case POS_INTERMEDIARIA: return "em movimento";
    default:                return chave ? "invalida" : "invalido";
    }
}

// As posicoes valem enquanto o GOOSE da Pi do servo continuar chegando.
// Chamar com mtxChaves travado.
static bool posicoesOk(int64_t agora) {
    return ultimoPosMs > 0 && (agora - ultimoPosMs) < POS_TIMEOUT_MS;
}

// A regra do intertravamento (CILO): a chave N so abre ou fecha com o
// disjuntor N aberto. Sem saber a posicao do disjuntor, nao arrisca.
static int intertravamento(bool posOk, int dj) {
    if (!posOk) return BLOQ_SEM_POSICOES;
    if (dj == POS_FECHADA) return BLOQ_DJ_FECHADO;
    if (dj != POS_ABERTA) return BLOQ_DJ_INDEFINIDO;
    return LIBERADA;
}

// Explica um bloqueio: uma frase para o terminal e 16 letras para o LCD
static void textoBloqueio(int motivo, int n, char* frase, size_t nFrase, char* lcd, size_t nLcd) {
    switch (motivo) {
    case BLOQ_SEM_POSICOES:
        snprintf(frase, nFrase, "nao chegam as posicoes da Pi do servo (GOOSE gcbPos)");
        snprintf(lcd, nLcd, "SEM POSICOES");
        break;
    case BLOQ_DJ_FECHADO:
        snprintf(frase, nFrase, "o disjuntor %d esta fechado. Abra o disjuntor %d antes", n + 1, n + 1);
        snprintf(lcd, nLcd, "ABRA O DJ%c ANTES", DIGITO(n));
        break;
    default:
        snprintf(frase, nFrase, "o disjuntor %d esta em posicao indefinida", n + 1);
        snprintf(lcd, nLcd, "DJ%c INDEFINIDO", DIGITO(n));
        break;
    }
}

// Valor do comando: 1 = abrir, 2 = fechar (igual aos botoes do Elipse)
static int alvoDoComando(MmsValue* v) {
    if (v != NULL && MmsValue_getType(v) == MMS_STRUCTURE) v = MmsValue_getElement(v, 0);
    if (v == NULL) return -1;
    switch (MmsValue_getType(v)) {
    case MMS_BIT_STRING: return MmsValue_getBitStringAsInteger(v);
    case MMS_BOOLEAN:    return MmsValue_getBoolean(v) ? POS_FECHADA : POS_ABERTA;
    case MMS_INTEGER:
    case MMS_UNSIGNED:   return MmsValue_toInt32(v);
    default:             return -1;
    }
}

// ----------------------------------------------------------------
// GOOSE de posicoes da Pi do servo (gcbPos). Chamada a cada mensagem,
// inclusive as repeticoes: cada uma renova o "estou vivo" das posicoes.
// ----------------------------------------------------------------
// Diagnostico (sudo DEBUG_GOOSE=1 ./empelas_prot): conta o que chega no
// receptor de GOOSE deste programa e mostra a cada 5 s.
static volatile uint32_t diagPosChamadas = 0, diagOutras = 0;

static void gooseObservador(GooseSubscriber sub, void* parameter) {
    uint32_t n = ++diagOutras;
    if (n <= 5) {
        uint8_t mac[6];
        GooseSubscriber_getDstMac(sub, mac);
        LOG_PRINT("[GOOSE-DIAG] chegou outra mensagem: %s | APPID 0x%04X | destino %02X-%02X-%02X-%02X-%02X-%02X\n",
                  GooseSubscriber_getGoCbRef(sub), (unsigned) GooseSubscriber_getAppId(sub),
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }
}

static void goosePosListener(GooseSubscriber sub, void* parameter) {
    static uint32_t stNumAvisado = 0;
    diagPosChamadas++;
    uint32_t stNum = GooseSubscriber_getStNum(sub);
    MmsValue* valores = GooseSubscriber_getDataSetValues(sub);
    int p[6];
    for (int k = 0; k < 6; k++) {
        MmsValue* v = valores ? MmsValue_getElement(valores, k) : NULL;
        if (v == NULL || MmsValue_getType(v) != MMS_BIT_STRING) {
            if (stNum != stNumAvisado)
                LOG_PRINT("[GOOSE] Posicoes com formato inesperado (stNum=%u), ignoradas. Os dois .icd estao na mesma versao?\n", stNum);
            stNumAvisado = stNum;
            return;
        }
        p[k] = MmsValue_getBitStringAsInteger(v);
    }

    pthread_mutex_lock(&mtxChaves);
    bool mudou = (ultimoPosMs == 0) || memcmp(posDj, p, sizeof(posDj)) != 0
                                    || memcmp(posCh, p + 3, sizeof(posCh)) != 0;
    memcpy(posDj, p, sizeof(posDj));
    memcpy(posCh, p + 3, sizeof(posCh));
    ultimoPosMs = agoraMs();
    pthread_mutex_unlock(&mtxChaves);

    if (mudou)
        LOG_PRINT("[GOOSE] Patio (stNum=%u): DJ1 %s, DJ2 %s, DJ3 %s | CH1 %s, CH2 %s, CH3 %s\n", stNum,
                  textoPos(p[0], false), textoPos(p[1], false), textoPos(p[2], false),
                  textoPos(p[3], true), textoPos(p[4], true), textoPos(p[5], true));
}

// ----------------------------------------------------------------
// Antes de aceitar um comando de chave (CSWIn.Pos), confere:
//   1. se a chave ja nao esta manobrando;
//   2. o intertravamento (CILOn): disjuntor N aberto;
//   3. se a chave ja nao esta na posicao pedida.
// Recusado, o supervisorio recebe o erro e o motivo (addCause), o terminal
// explica e o LCD2 mostra o aviso.
// ----------------------------------------------------------------
static CheckHandlerResult checkChave(ControlAction action, void* parameter, MmsValue* ctlVal, bool test, bool interlockCheck) {
    int n = (int) (intptr_t) parameter;
    int alvo = alvoDoComando(ctlVal);
    if (alvo != POS_ABERTA && alvo != POS_FECHADA) {
        LOG_PRINT("[CHAVE] Comando da chave %d com valor %d: use 1 (abrir) ou 2 (fechar).\n", n + 1, alvo);
        return CONTROL_VALUE_INVALID;
    }
    const char* acao = (alvo == POS_ABERTA) ? "ABRIR" : "FECHAR";
    char l1[17], l2[17];

    pthread_mutex_lock(&mtxChaves);
    bool posOk = posicoesOk(agoraMs());
    int dj = posDj[n], ch = posCh[n];
    bool ocupada = pedido[n] || emCurso[n] || (posOk && ch == POS_INTERMEDIARIA);
    pthread_mutex_unlock(&mtxChaves);

    if (ocupada) {
        LOG_PRINT("[CHAVE] Pedido de %s a chave %d recusado: ela ainda esta manobrando.\n", acao, n + 1);
        ControlAction_setAddCause(action, ADD_CAUSE_COMMAND_ALREADY_IN_EXECUTION);
        return CONTROL_TEMPORARILY_UNAVAILABLE;
    }

    int motivo = intertravamento(posOk, dj);
    if (motivo != LIBERADA) {
        char frase[120];
        textoBloqueio(motivo, n, frase, sizeof(frase), l2, sizeof(l2));
        snprintf(l1, sizeof(l1), "CH%c BLOQUEADA", DIGITO(n));
        avisoLcd(l1, l2);
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[INTERTRAVAMENTO] Pedido de %s a chave %d RECUSADO: %s.\n", acao, n + 1, frase);
        LOG_PRINT("--------------------------------------------------\n");
        ControlAction_setAddCause(action, ADD_CAUSE_BLOCKED_BY_INTERLOCKING);
        return CONTROL_OBJECT_ACCESS_DENIED;
    }

    if (ch == alvo) {
        snprintf(l1, sizeof(l1), "CH%c JA %s", DIGITO(n), (alvo == POS_ABERTA) ? "ABERTA" : "FECHADA");
        avisoLcd(l1, "NADA A FAZER");
        LOG_PRINT("[CHAVE] Pedido de %s a chave %d: ela ja esta %s. Nada a fazer.\n", acao, n + 1, textoPos(ch, true));
        ControlAction_setAddCause(action, ADD_CAUSE_POSITION_REACHED);
        return CONTROL_OBJECT_ACCESS_DENIED;
    }

    return CONTROL_ACCEPTED;
}

// Comando aceito: deixa o pedido para a thread das chaves publicar no GOOSE.
static ControlHandlerResult operarChave(ControlAction action, void* parameter, MmsValue* value, bool test) {
    int n = (int) (intptr_t) parameter;
    int alvo = alvoDoComando(value);
    if (alvo != POS_ABERTA && alvo != POS_FECHADA) return CONTROL_RESULT_FAILED;

    ClientConnection con = ControlAction_getClientConnection(action);
    const char* ip = con ? ClientConnection_getPeerAddress(con) : "desconhecido";

    pthread_mutex_lock(&mtxChaves);
    pedido[n] = alvo;
    pthread_mutex_unlock(&mtxChaves);

    char l1[17];
    snprintf(l1, sizeof(l1), "CH%c %s...", DIGITO(n), (alvo == POS_ABERTA) ? "ABRINDO" : "FECHANDO");
    avisoLcd(l1, "GOOSE -> PATIO");
    LOG_PRINT("--------------------------------------------------\n");
    LOG_PRINT("[CHAVE] Operador (%s) pediu %s a chave %d. Intertravamento: liberado (disjuntor %d aberto).\n",
              ip, (alvo == POS_ABERTA) ? "ABRIR" : "FECHAR", n + 1, n + 1);
    return CONTROL_RESULT_OK;
}

// ----------------------------------------------------------------
// Thread das chaves (a cada 20 ms):
//   - mantem o CILOn (EnaOpn/EnaCls) e o CSWIn.Pos em dia com o patio;
//   - publica o comando aceito: liga CSWIn.OpOpn ou OpCls, e o GOOSE sai;
//   - espera a chave chegar na posicao pedida e desliga o sinal. Se ela
//     nao chegar em CMD_TIMEOUT_MS, desliga do mesmo jeito e avisa.
// ----------------------------------------------------------------
static DataAttribute* const enaOpn[3]  = { IEDMODEL_MEDPROT_CILO1_EnaOpn_stVal, IEDMODEL_MEDPROT_CILO2_EnaOpn_stVal, IEDMODEL_MEDPROT_CILO3_EnaOpn_stVal };
static DataAttribute* const enaOpnT[3] = { IEDMODEL_MEDPROT_CILO1_EnaOpn_t, IEDMODEL_MEDPROT_CILO2_EnaOpn_t, IEDMODEL_MEDPROT_CILO3_EnaOpn_t };
static DataAttribute* const enaCls[3]  = { IEDMODEL_MEDPROT_CILO1_EnaCls_stVal, IEDMODEL_MEDPROT_CILO2_EnaCls_stVal, IEDMODEL_MEDPROT_CILO3_EnaCls_stVal };
static DataAttribute* const enaClsT[3] = { IEDMODEL_MEDPROT_CILO1_EnaCls_t, IEDMODEL_MEDPROT_CILO2_EnaCls_t, IEDMODEL_MEDPROT_CILO3_EnaCls_t };
static DataAttribute* const cswiPos[3]  = { IEDMODEL_MEDPROT_CSWI1_Pos_stVal, IEDMODEL_MEDPROT_CSWI2_Pos_stVal, IEDMODEL_MEDPROT_CSWI3_Pos_stVal };
static DataAttribute* const cswiPosQ[3] = { IEDMODEL_MEDPROT_CSWI1_Pos_q, IEDMODEL_MEDPROT_CSWI2_Pos_q, IEDMODEL_MEDPROT_CSWI3_Pos_q };
static DataAttribute* const cswiPosT[3] = { IEDMODEL_MEDPROT_CSWI1_Pos_t, IEDMODEL_MEDPROT_CSWI2_Pos_t, IEDMODEL_MEDPROT_CSWI3_Pos_t };
static DataAttribute* const opOpn[3]  = { IEDMODEL_MEDPROT_CSWI1_OpOpn_general, IEDMODEL_MEDPROT_CSWI2_OpOpn_general, IEDMODEL_MEDPROT_CSWI3_OpOpn_general };
static DataAttribute* const opOpnT[3] = { IEDMODEL_MEDPROT_CSWI1_OpOpn_t, IEDMODEL_MEDPROT_CSWI2_OpOpn_t, IEDMODEL_MEDPROT_CSWI3_OpOpn_t };
static DataAttribute* const opCls[3]  = { IEDMODEL_MEDPROT_CSWI1_OpCls_general, IEDMODEL_MEDPROT_CSWI2_OpCls_general, IEDMODEL_MEDPROT_CSWI3_OpCls_general };
static DataAttribute* const opClsT[3] = { IEDMODEL_MEDPROT_CSWI1_OpCls_t, IEDMODEL_MEDPROT_CSWI2_OpCls_t, IEDMODEL_MEDPROT_CSWI3_OpCls_t };

// Escreve uma posicao de ponto duplo (mesma convencao da Pi do servo)
static void escreverDbpos(DataAttribute* da, int pos) {
    MmsValue* v = MmsValue_newBitString(2);
    MmsValue_setBitStringFromInteger(v, pos);
    IedServer_updateAttributeValue(iedServer, da, v);
    MmsValue_delete(v);
}

void* chaves_thread(void* arg) {
    int motivoAntes[3] = {-1, -1, -1};      // ultimo estado publicado no CILO
    int posPublicada[3] = {-1, -1, -1};     // ultimo valor publicado no CSWI.Pos (-2 = invalido)
    int posOkAntes = -1;
    int64_t inicio[3] = {0, 0, 0};
    int alvoCmd[3] = {0, 0, 0};             // comando publicado (0 = nenhum)

    while (running) {
        int64_t agora = agoraMs();
        int dj[3], ch[3], novo[3];

        pthread_mutex_lock(&mtxChaves);
        bool posOk = posicoesOk(agora);
        memcpy(dj, posDj, sizeof(dj));
        memcpy(ch, posCh, sizeof(ch));
        for (int n = 0; n < 3; n++) {
            novo[n] = pedido[n];
            if (novo[n]) {
                emCurso[n] = novo[n];
                pedido[n] = 0;
            }
        }
        pthread_mutex_unlock(&mtxChaves);

        // O GOOSE de posicoes chegou ou sumiu
        if ((int) posOk != posOkAntes) {
            if (posOk)
                LOG_PRINT("[GOOSE] Recebendo as posicoes da Pi do servo (gcbPos). Intertravamento ativo.\n");
            else if (posOkAntes == 1) {
                LOG_PRINT("[GOOSE] Sem as posicoes da Pi do servo ha %d s! Todas as chaves bloqueadas.\n", POS_TIMEOUT_MS / 1000);
                avisoLcd("SEM POSICOES", "CHAVES BLOQ.");
            }
            posOkAntes = posOk;
        }

        int motivo[3];
        bool escrever = false;              // so trava o modelo se tiver algo novo
        for (int n = 0; n < 3; n++) {
            motivo[n] = intertravamento(posOk, dj[n]);

            // Confere de novo na hora de publicar: o disjuntor pode ter
            // fechado entre o operador pedir e este instante.
            if (novo[n] && motivo[n] != LIBERADA) {
                char frase[120], l1[17], l2[17];
                textoBloqueio(motivo[n], n, frase, sizeof(frase), l2, sizeof(l2));
                snprintf(l1, sizeof(l1), "CH%c BLOQUEADA", DIGITO(n));
                avisoLcd(l1, l2);
                LOG_PRINT("[INTERTRAVAMENTO] Comando da chave %d cancelado antes de sair: %s.\n", n + 1, frase);
                LOG_PRINT("--------------------------------------------------\n");
                novo[n] = 0;
                pthread_mutex_lock(&mtxChaves);
                emCurso[n] = 0;
                pthread_mutex_unlock(&mtxChaves);
            }

            int p = posOk ? ch[n] : -2;
            if (motivo[n] != motivoAntes[n] || p != posPublicada[n] || novo[n]) escrever = true;
        }
        uint64_t ts = Hal_getTimeInMs();

        if (escrever) IedServer_lockDataModel(iedServer);
        for (int n = 0; n < 3 && escrever; n++) {
            // CILO: liberado ou nao
            if (motivo[n] != motivoAntes[n]) {
                bool ena = (motivo[n] == LIBERADA);
                IedServer_updateUTCTimeAttributeValue(iedServer, enaOpnT[n], ts);   // horario antes do valor
                IedServer_updateBooleanAttributeValue(iedServer, enaOpn[n], ena);
                IedServer_updateUTCTimeAttributeValue(iedServer, enaClsT[n], ts);
                IedServer_updateBooleanAttributeValue(iedServer, enaCls[n], ena);
            }

            // CSWI.Pos: espelho da chave real, invalido sem GOOSE
            int p = posOk ? ch[n] : -2;
            if (p != posPublicada[n]) {
                IedServer_updateUTCTimeAttributeValue(iedServer, cswiPosT[n], ts);   // horario antes do valor
                if (posOk) {
                    escreverDbpos(cswiPos[n], ch[n]);
                    IedServer_updateQuality(iedServer, cswiPosQ[n], QUALITY_VALIDITY_GOOD);
                } else {
                    IedServer_updateQuality(iedServer, cswiPosQ[n], QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE);
                }
                posPublicada[n] = p;
            }

            // Comando novo: liga o sinal (OpOpn ou OpCls). E isto que dispara o GOOSE.
            if (novo[n]) {
                DataAttribute* sinal  = (novo[n] == POS_ABERTA) ? opOpn[n]  : opCls[n];
                DataAttribute* sinalT = (novo[n] == POS_ABERTA) ? opOpnT[n] : opClsT[n];
                IedServer_updateUTCTimeAttributeValue(iedServer, sinalT, ts);
                IedServer_updateBooleanAttributeValue(iedServer, sinal, true);
                inicio[n] = agora;
                alvoCmd[n] = novo[n];
            }
        }
        if (escrever) IedServer_unlockDataModel(iedServer);

        for (int n = 0; n < 3; n++) {
            if (novo[n])
                LOG_PRINT("[GOOSE] Comando %s da chave %d publicado (gcbCmd: CSWI%d.%s).\n",
                          (novo[n] == POS_ABERTA) ? "ABRIR" : "FECHAR", n + 1, n + 1,
                          (novo[n] == POS_ABERTA) ? "OpOpn" : "OpCls");

            if (motivo[n] != motivoAntes[n]) {
                if (motivoAntes[n] >= 0) {       // nao repete no inicio
                    char frase[120], lcd[17];
                    if (motivo[n] == LIBERADA)
                        LOG_PRINT("[INTERTRAVAMENTO] Chave %d liberada (disjuntor %d aberto).\n", n + 1, n + 1);
                    else {
                        textoBloqueio(motivo[n], n, frase, sizeof(frase), lcd, sizeof(lcd));
                        LOG_PRINT("[INTERTRAVAMENTO] Chave %d bloqueada: %s.\n", n + 1, frase);
                    }
                }
                motivoAntes[n] = motivo[n];
            }

            // Comando em curso: a chave chegou? Passou do tempo?
            if (alvoCmd[n] && !novo[n]) {
                bool chegou = posOk && (ch[n] == alvoCmd[n]);
                bool estourou = (agora - inicio[n]) > CMD_TIMEOUT_MS;
                if (chegou || estourou) {
                    DataAttribute* sinal  = (alvoCmd[n] == POS_ABERTA) ? opOpn[n]  : opCls[n];
                    DataAttribute* sinalT = (alvoCmd[n] == POS_ABERTA) ? opOpnT[n] : opClsT[n];
                    IedServer_lockDataModel(iedServer);
                    IedServer_updateBooleanAttributeValue(iedServer, sinal, false);
                    IedServer_updateUTCTimeAttributeValue(iedServer, sinalT, Hal_getTimeInMs());
                    IedServer_unlockDataModel(iedServer);

                    char l1[17];
                    const char* final = (alvoCmd[n] == POS_ABERTA) ? "ABERTA" : "FECHADA";
                    if (chegou) {
                        snprintf(l1, sizeof(l1), "CH%c %s", DIGITO(n), final);
                        avisoLcd(l1, "CONFIRMADO");
                        LOG_PRINT("[CHAVE] Chave %d %s: confirmado pelo GOOSE da Pi do servo em %lld ms.\n",
                                  n + 1, final, (long long) (agora - inicio[n]));
                    } else {
                        snprintf(l1, sizeof(l1), "CH%c SEM RESPOSTA", DIGITO(n));
                        avisoLcd(l1, "VEJA A PI SERVO");
                        LOG_PRINT("[CHAVE] Chave %d nao chegou a ficar %s em %d s. Veja o terminal da Pi do servo.\n",
                                  n + 1, textoPos(alvoCmd[n], true), CMD_TIMEOUT_MS / 1000);
                    }
                    LOG_PRINT("--------------------------------------------------\n");

                    alvoCmd[n] = 0;
                    pthread_mutex_lock(&mtxChaves);
                    emCurso[n] = 0;
                    pthread_mutex_unlock(&mtxChaves);
                }
            }
        }

        Thread_sleep(20);
    }
    return NULL;
}

// ----------------------------------------------------------------
// Som do transformador (amplificador PAM8403 + alto-falante, na saida de
// audio P2 desta Pi).
//
// Um transformador zumbe enquanto esta energizado. Aqui ele e alimentado
// pelos tres vaos: fica energizado enquanto pelo menos um vao tiver o
// disjuntor E a chave fechados (posicoes que chegam pelo GOOSE da Pi do
// servo). O trip abre o disjuntor e o zumbido para na hora.
//
// O som e o arquivo SOM_ARQUIVO (WAV PCM de 16 bits, na pasta do programa),
// tocado em repeticao pelo aplay. Sem o arquivo ou sem o aplay, o programa
// segue normalmente, so sem som.
// ----------------------------------------------------------------
#define SOM_ARQUIVO   "zumbido.wav"
#define SOM_VOLUME    1.0          // 0.0 a 1.0 (multiplica as amostras)

static int16_t* somDados = NULL;   // amostras (todos os canais intercalados)
static size_t somTotal = 0;        // quantidade de amostras
static unsigned somTaxa = 0, somCanais = 0;
static pid_t somPid = -1;
static int somFd = -1;

static uint32_t le32(const uint8_t* b) { return b[0] | (b[1] << 8) | (b[2] << 16) | ((uint32_t) b[3] << 24); }
static uint16_t le16(const uint8_t* b) { return (uint16_t) (b[0] | (b[1] << 8)); }

// Le um WAV PCM 16 bits inteiro para a memoria
static bool carregarWav(const char* nome) {
    FILE* f = fopen(nome, "rb");
    if (f == NULL) return false;
    uint8_t h[12];
    bool ok = false, temFmt = false;
    if (fread(h, 1, 12, f) == 12 && memcmp(h, "RIFF", 4) == 0 && memcmp(h + 8, "WAVE", 4) == 0) {
        uint8_t c[8];
        while (fread(c, 1, 8, f) == 8) {
            uint32_t tam = le32(c + 4);
            if (memcmp(c, "fmt ", 4) == 0 && tam >= 16) {
                uint8_t fm[16];
                if (fread(fm, 1, 16, f) != 16) break;
                if (le16(fm) != 1 || le16(fm + 14) != 16) break;   // so PCM de 16 bits
                somCanais = le16(fm + 2);
                somTaxa = le32(fm + 4);
                temFmt = true;
                fseek(f, (long) (tam - 16 + (tam & 1)), SEEK_CUR);
            } else if (memcmp(c, "data", 4) == 0 && temFmt) {
                somDados = malloc(tam);
                if (somDados && fread(somDados, 1, tam, f) == tam) {
                    somTotal = tam / 2;
                    ok = (somTotal >= somCanais && somCanais > 0);
                }
                break;
            } else {
                fseek(f, (long) (tam + (tam & 1)), SEEK_CUR);
            }
        }
    }
    fclose(f);
    if (ok && SOM_VOLUME < 1.0)
        for (size_t i = 0; i < somTotal; i++) somDados[i] = (int16_t) (somDados[i] * SOM_VOLUME);
    return ok;
}

// Abre o aplay recebendo as amostras por um cano (pipe)
static bool somLigar(void) {
    int p[2];
    if (pipe(p) != 0) return false;
#ifdef F_SETPIPE_SZ
    fcntl(p[1], F_SETPIPE_SZ, 4096);   // cano curto: o som para logo quando o disjuntor abre
#endif
    char taxa[16], canais[8];
    snprintf(taxa, sizeof(taxa), "%u", somTaxa);
    snprintf(canais, sizeof(canais), "%u", somCanais);
    pid_t pid = fork();
    if (pid < 0) { close(p[0]); close(p[1]); return false; }
    if (pid == 0) {
        dup2(p[0], STDIN_FILENO);
        close(p[0]); close(p[1]);
        int nulo = open("/dev/null", O_WRONLY);
        if (nulo >= 0) { dup2(nulo, STDERR_FILENO); close(nulo); }
        execlp("aplay", "aplay", "-q", "-t", "raw", "-f", "S16_LE", "-r", taxa, "-c", canais,
               "-B", "100000", (char*) NULL);
        _exit(127);
    }
    close(p[0]);
    somPid = pid;
    somFd = p[1];
    return true;
}

static void somDesligar(void) {
    if (somPid > 0) {
        kill(somPid, SIGTERM);
        waitpid(somPid, NULL, 0);
    }
    if (somFd >= 0) close(somFd);
    somPid = -1;
    somFd = -1;
}

static bool transformadorEnergizado(void) {
    bool energizado = false;
    pthread_mutex_lock(&mtxChaves);
    if (posicoesOk(agoraMs()))
        for (int n = 0; n < 3; n++)
            if (posDj[n] == POS_FECHADA && posCh[n] == POS_FECHADA) energizado = true;
    pthread_mutex_unlock(&mtxChaves);
    return energizado;
}

void* som_thread(void* arg) {
    if (!carregarWav(SOM_ARQUIVO)) {
        LOG_PRINT("[SOM]    Sem o arquivo %s (WAV PCM 16 bits na pasta do programa): sem zumbido.\n", SOM_ARQUIVO);
        return NULL;
    }
    LOG_PRINT("[SOM]    Zumbido do transformador: %s (%.1f s, %u Hz). Toca com o transformador energizado.\n",
              SOM_ARQUIVO, (double) somTotal / somCanais / somTaxa, somTaxa);

    const size_t bloco = (somTaxa / 20) * somCanais;   // 50 ms de som por escrita
    size_t pos = 0;
    bool tocando = false;
    int falhas = 0;

    while (running) {
        bool energizado = transformadorEnergizado();
        if (energizado && !tocando) {
            if (somLigar()) {
                tocando = true;
                LOG_PRINT("[SOM] Transformador energizado: zumbido ligado.\n");
            }
        } else if (!energizado && tocando) {
            somDesligar();
            tocando = false;
            LOG_PRINT("[SOM] Transformador desenergizado: zumbido desligado.\n");
        }

        if (!tocando) {
            Thread_sleep(50);
            continue;
        }

        // Escreve o proximo pedaco, voltando ao inicio do arquivo quando acaba.
        // A escrita espera o aplay tocar, entao este laco anda no ritmo do som.
        size_t n = bloco;
        if (pos + n > somTotal) n = somTotal - pos;
        ssize_t w = write(somFd, somDados + pos, n * sizeof(int16_t));
        if (w <= 0) {
            somDesligar();
            tocando = false;
            if (++falhas <= 3)
                LOG_PRINT("[SOM] O aplay parou (saida de audio ocupada ou desligada?). Tentando de novo em 2 s.\n");
            Thread_sleep(2000);
            continue;
        }
        falhas = 0;
        pos = (pos + (size_t) w / sizeof(int16_t)) % somTotal;
        pos -= pos % somCanais;
    }
    somDesligar();
    return NULL;
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

// aviso != NULL: o LCD2 mostra o aviso das chaves no lugar das tensoes
static void atualizarDisplays(const Medidas* m, bool svOk, int fases, const char aviso[2][17]) {
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

    if (lcd2 >= 0 && aviso != NULL) {
        lcdLinha(lcd2, 0, aviso[0]);
        lcdLinha(lcd2, 1, aviso[1]);
    } else if (lcd2 >= 0) {
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
    uint32_t avisoSeqAntes = 0;
    bool avisoAntes = false;

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

        // Aviso das chaves no LCD2 (fica AVISO_MS na tela)
        char aviso[2][17];
        pthread_mutex_lock(&mtxAviso);
        bool avisoAtivo = (agora < avisoAteMs);
        uint32_t seq = avisoSeq;
        memcpy(aviso[0], avisoL1, sizeof(aviso[0]));
        memcpy(aviso[1], avisoL2, sizeof(aviso[1]));
        pthread_mutex_unlock(&mtxAviso);

        bool mudou = (svOk != svOkAntes) || (fases != fasesAntes);
        bool mudouLcd = mudou || (avisoAtivo != avisoAntes) || (seq != avisoSeqAntes);

        if (mudou || agora - ultimoMmxu >= 1000) {
            publicarMedicoes(&m, svOk, Hal_getTimeInMs());
            ultimoMmxu = agora;
        }
        if (mudouLcd || agora - ultimoLcd >= 500) {
            atualizarDisplays(&m, svOk, fases, avisoAtivo ? (const char (*)[17]) aviso : NULL);
            ultimoLcd = agora;
        }
        if (agora - ultimoLog >= 5000) {
            if (svOk)
                LOG_PRINT("[MEDICAO] IA %.1f IB %.1f IC %.1f IN %.1f A | VA %.1f VB %.1f VC %.1f kV | SV perdidas: %u\n",
                          m.i[0], m.i[1], m.i[2], m.i[3], m.v[0] / 1000, m.v[1] / 1000, m.v[2] / 1000,
                          (unsigned) (perdidas - perdidasAntes));
            perdidasAntes = perdidas;
            ultimoLog = agora;
            if (getenv("DEBUG_GOOSE"))
                LOG_PRINT("[GOOSE-DIAG] recebidas pelo assinante gcbPos: %u | outras: %u\n",
                          (unsigned) diagPosChamadas, (unsigned) diagOutras);
        }

        svOkAntes = svOk;
        fasesAntes = fases;
        avisoAntes = avisoAtivo;
        avisoSeqAntes = seq;
        Thread_sleep(50);
    }
    return NULL;
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    signal(SIGPIPE, SIG_IGN);   // o aplay do som pode fechar; nao derruba o programa

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
    atualizarRelogio();                         // antes de qualquer horario ser escrito
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    // Chaves: o operador comanda no CSWIn.Pos (1 = abrir, 2 = fechar), como
    // fazia antes direto na Pi do servo. O intertravamento roda no check.
    DataObject* cswi[3] = { IEDMODEL_MEDPROT_CSWI1_Pos, IEDMODEL_MEDPROT_CSWI2_Pos, IEDMODEL_MEDPROT_CSWI3_Pos };
    for (int n = 0; n < 3; n++) {
        IedServer_updateCtlModel(iedServer, cswi[n], CONTROL_MODEL_DIRECT_NORMAL);
        IedServer_setPerformCheckHandler(iedServer, cswi[n], checkChave, (void*) (intptr_t) n);
        IedServer_setControlHandler(iedServer, cswi[n], (ControlHandler) operarChave, (void*) (intptr_t) n);
        // Ate chegar o primeiro GOOSE de posicoes, a posicao e desconhecida
        IedServer_updateQuality(iedServer, cswiPosQ[n], QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE);
    }

    // GOOSE sai pelo cabo
    IedServer_setGooseInterfaceId(iedServer, INTERFACE_GOOSE);
    IedServer_start(iedServer, tcpPort);
    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    // Habilita a publicacao de todos os blocos GOOSE do modelo (gcbTrip e gcbCmd)
    IedServer_enableGoosePublishing(iedServer);

    // Assinatura das posicoes da Pi do servo (gcbPos)
    GooseReceiver gooseReceiver = GooseReceiver_create();
    GooseReceiver_setInterfaceId(gooseReceiver, INTERFACE_GOOSE);
    GooseSubscriber subPos = GooseSubscriber_create(GOOSE_POS_REF, NULL);
    GooseSubscriber_setDstMac(subPos, GOOSE_POS_DSTMAC);
    GooseSubscriber_setAppId(subPos, GOOSE_POS_APPID);
    GooseSubscriber_setListener(subPos, goosePosListener, NULL);
    GooseReceiver_addSubscriber(gooseReceiver, subPos);
    bool diagGoose = (getenv("DEBUG_GOOSE") != NULL);
    if (diagGoose) {
        // Depois do subPos na lista: so pega o que o subPos NAO reconheceu
        GooseSubscriber obs = GooseSubscriber_create("", NULL);
        GooseSubscriber_setObserver(obs);
        GooseSubscriber_setListener(obs, gooseObservador, NULL);
        GooseReceiver_addSubscriber(gooseReceiver, obs);
    }
    GooseReceiver_start(gooseReceiver);

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
    LOG_PRINT("[GOOSE]  Publicando gcbCmd em %s (APPID 0x1003): comandos das chaves.\n", INTERFACE_GOOSE);
    if (GooseReceiver_isRunning(gooseReceiver))
        LOG_PRINT("[GOOSE]  Assinando gcbPos em %s (APPID 0x%04X): posicoes da Pi do servo. Aguardando...\n",
                  INTERFACE_GOOSE, GOOSE_POS_APPID);
    else
        LOG_PRINT("[GOOSE]  ERRO: receptor de GOOSE nao iniciou. Confira se %s existe e se rodou com sudo.\n", INTERFACE_GOOSE);
    LOG_PRINT("[CHAVES] CSWI1-3 com intertravamento (CILO1-3): chave N so manobra com o disjuntor N aberto.\n");

    running = 1;
    Thread displayThread = Thread_create((ThreadExecutionFunction) display_thread, NULL, false);
    Thread_start(displayThread);
    Thread chavesThread = Thread_create((ThreadExecutionFunction) chaves_thread, NULL, false);
    Thread_start(chavesThread);
    Thread somThread = Thread_create((ThreadExecutionFunction) som_thread, NULL, false);
    Thread_start(somThread);

    int ciclos = 0;
    while (running) {
        Thread_sleep(100);
        if (++ciclos % 50 == 0) atualizarRelogio();     // a cada 5 s
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    SVReceiver_stop(svReceiver);
    SVReceiver_destroy(svReceiver);
    if (sockGrupoSV >= 0) close(sockGrupoSV);
    GooseReceiver_stop(gooseReceiver);
    GooseReceiver_destroy(gooseReceiver);
    Thread_destroy(displayThread);
    Thread_destroy(chavesThread);
    Thread_destroy(somThread);                  // desliga o zumbido
    IedServer_disableGoosePublishing(iedServer);
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    if (dev_null != -1) close(dev_null);
    return 0;
}
