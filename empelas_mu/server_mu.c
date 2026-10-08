/*
 * EmPowerElas - Maquete de Subestacao Digital
 * Merging unit (Raspberry Pi 3): EmpElas_MU
 *
 * Faz o papel do TC e do TP digitais da linha. Gera as formas de onda de
 * corrente e tensao das tres fases e publica as amostras por Sampled Values
 * (IEC 61850-9-2), no formato do perfil 9-2LE:
 *   4 correntes (IA, IB, IC, IN) + 4 tensoes (VA, VB, VC, VN),
 *   80 amostras por ciclo de 60 Hz = 4800 mensagens por segundo.
 *
 * A FALTA: "UMA ARVORE CAIU NA LINHA"
 * A arvore encosta na fase A, o que e uma falta fase-terra. Durante a falta,
 * a corrente da fase A sobe, a tensao da fase A cai e aparece corrente no
 * neutro. As fases B e C continuam normais.
 *   - botao fisico: cada aperto alterna (arvore cai / arvore retirada);
 *   - supervisorio: FLTGGIO1.SPCSO1 (1 derruba a arvore, 0 retira).
 * Um LED ao lado do botao fica aceso enquanto a arvore estiver na linha.
 *
 * Esta Pi nao decide nada: so "mede" a linha e publica. Quem ve a falta e
 * atua e o IED de protecao (EmpElas_PROT), que assina este SV.
 *
 * Compilar e rodar nesta Pi:
 *   make modelo    (so quando o .icd mudar)
 *   make           (sem botao ligado ainda? use: make SEM_BOTAO=1)
 *   sudo ./empelas_mu
 */

#define _GNU_SOURCE
#include "iec61850_server.h"
#include "hal_thread.h"
#include "sv_publisher.h"
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
#include <sched.h>
#include <sys/mman.h>
#ifndef SEM_BOTAO
#include <wiringPi.h>
#endif

#include "static_model.h"

// ======================= REDE (SV) ===========================
// Interface por onde o SV sai. Precisa ser o CABO (roteador da maquete).
#ifndef INTERFACE_SV
#define INTERFACE_SV "eth0"
#endif
// Estes valores precisam ser iguais aos do .icd (bloco SMV) e aos do
// assinante (server_prot.c).
#define SV_APPID       0x4000
#define SV_VLAN_ID     0
#define SV_VLAN_PRIO   4
#define SV_ID          "EmpElas_MU01"
#define SV_CONFREV     1
static const uint8_t SV_DSTMAC[6] = {0x01, 0x0C, 0xCD, 0x04, 0x00, 0x01};

// ===================== AMOSTRAGEM ============================
#define FREQ_HZ             60
#define AMOSTRAS_POR_CICLO  80                              // 9-2LE
#define AMOSTRAS_POR_SEG    (FREQ_HZ * AMOSTRAS_POR_CICLO)  // 4800

// ============== SISTEMA ELETRICO SIMULADO ====================
#define V_LINHA_KV        500.0   // tensao entre fases (kV eficaz)
#define I_CARGA_A         100.0   // corrente normal em cada fase (A eficaz)
#define ANG_CARGA_GRAUS    25.0   // atraso da corrente normal (fator de potencia ~0,9)
#define I_FALTA_A         800.0   // corrente na fase A durante a falta (A eficaz)
#define ANG_FALTA_GRAUS    80.0   // na falta a corrente fica bem mais atrasada (linha indutiva)
#define V_FALTA_PU          0.30  // na falta, a tensao da fase A cai para 30%

// Escala do 9-2LE: corrente em mA, tensao em unidades de 10 mV
#define ESCALA_I  1000.0          // A -> mA
#define ESCALA_V   100.0          // V -> 10 mV

// ================ BOTAO E LED (numeracao wiringPi) =============
// Botao: entre o pino fisico 11 e o GND (pino fisico 9). Sem resistor:
// o resistor de pull-up interno da Pi e ligado pelo programa.
#define BOTAO_PINO   0    // wPi 0 = BCM17 = Fisico 11
// LED: pino fisico 13 -> resistor de 330 ohm -> LED -> GND (pino fisico 14)
#define LED_PINO     2    // wPi 2 = BCM27 = Fisico 13
#define DEBOUNCE_MS  40   // tempo que o botao precisa ficar estavel

// ============================================================

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

#define ACAO_APLICAR   1
#define ACAO_RETIRAR   2
#define ACAO_ALTERNAR  3

static volatile int running = 0;
static IedServer iedServer = NULL;
static volatile int arvoreNaLinha = 0;      // 1 = falta aplicada
static pthread_mutex_t mtxFalta = PTHREAD_MUTEX_INITIALIZER;
#ifndef SEM_BOTAO
static int botaoOk = 0;
#endif

// Estatisticas do SV (escritas so pela thread do SV)
static volatile uint32_t svEnviadas = 0;
static volatile uint32_t svPuladas = 0;     // amostras puladas por atraso

static void sigint_handler(int signalId) { running = 0; }

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
// Muda o estado da falta. Chamada pelo botao e pelo supervisorio.
//
// travarModelo: a thread do botao trava o modelo antes de escrever. O
// tratador de comando do supervisorio nao trava, igual aos exemplos da
// libiec61850: dependendo da versao, a biblioteca ja chama esse tratador
// com o modelo travado, e travar de novo deixaria o programa parado.
// ----------------------------------------------------------------
static void mudarFalta(int acao, const char* origem, bool travarModelo) {
    pthread_mutex_lock(&mtxFalta);
    int anterior = arvoreNaLinha;
    int novo = (acao == ACAO_ALTERNAR) ? !anterior : (acao == ACAO_APLICAR);
    arvoreNaLinha = novo;
    pthread_mutex_unlock(&mtxFalta);

#ifndef SEM_BOTAO
    if (botaoOk) digitalWrite(LED_PINO, novo ? HIGH : LOW);
#endif

    if (travarModelo) IedServer_lockDataModel(iedServer);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1_stVal, novo);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1_t, Hal_getTimeInMs());
    if (travarModelo) IedServer_unlockDataModel(iedServer);

    if (novo == anterior) {
        LOG_PRINT("[FALTA] Nada mudou: a arvore %s (pedido de: %s)\n",
                  novo ? "ja estava na linha" : "ja tinha sido retirada", origem);
        return;
    }
    LOG_PRINT("==================================================\n");
    if (novo)
        LOG_PRINT("[FALTA] Uma arvore caiu na linha! Falta fase-terra na fase A.\n"
                  "        Corrente da fase A sobe para %.0f A. (origem: %s)\n", I_FALTA_A, origem);
    else
        LOG_PRINT("[FALTA] Arvore retirada. Linha normal de novo. (origem: %s)\n", origem);
    LOG_PRINT("==================================================\n");
}

// ----------------------------------------------------------------
// Comando do supervisorio em FLTGGIO1.SPCSO1: 1 derruba a arvore, 0 retira.
// ----------------------------------------------------------------
static CheckHandlerResult checkHandlerFalta(ControlAction action, void* parameter, MmsValue* ctlVal, bool test, bool interlockCheck) {
    return CONTROL_ACCEPTED;
}

static ControlHandlerResult controlHandlerFalta(ControlAction action, void* parameter, MmsValue* value, bool test) {
    if (MmsValue_getType(value) != MMS_BOOLEAN)
        return CONTROL_RESULT_FAILED;

    ClientConnection con = ControlAction_getClientConnection(action);
    char origem[80];
    snprintf(origem, sizeof(origem), "supervisorio %s", con ? ClientConnection_getPeerAddress(con) : "");

    mudarFalta(MmsValue_getBoolean(value) ? ACAO_APLICAR : ACAO_RETIRAR, origem, false);
    return CONTROL_RESULT_OK;
}

// ----------------------------------------------------------------
// Botao fisico. Le o pino a cada 10 ms. O pull-up deixa o pino em 1 com o
// botao solto; apertado, ele vai para 0. Cada aperto alterna a falta.
// ----------------------------------------------------------------
#ifndef SEM_BOTAO
static void* threadBotao(void* arg) {
    int estavel = HIGH;        // estado aceito (depois do debounce)
    int ultima = HIGH;         // ultima leitura
    int msIgual = 0;           // ha quanto tempo a leitura nao muda

    while (running) {
        int leitura = digitalRead(BOTAO_PINO);
        if (leitura == ultima) {
            if (msIgual < 10000) msIgual += 10;
        } else {
            ultima = leitura;
            msIgual = 0;
        }

        if (msIgual >= DEBOUNCE_MS && leitura != estavel) {
            estavel = leitura;
            if (estavel == LOW)            // acabou de ser apertado
                mudarFalta(ACAO_ALTERNAR, "botao fisico", true);
        }
        Thread_sleep(10);
    }
    return NULL;
}
#endif

// ----------------------------------------------------------------
// Publicacao do SV: uma mensagem a cada 1/4800 s (cerca de 208 us).
//
// O instante de cada amostra e calculado a partir do inicio (t0 + n/4800),
// e nao somando 208 us a cada volta, para nao acumular erro. Se o programa
// atrasar mais de 1 ciclo (por exemplo, a Pi ficou ocupada), ele pula para
// o instante atual; o assinante percebe isso como amostras perdidas.
// ----------------------------------------------------------------
typedef struct {
    SVPublisher pub;
    SVPublisher_ASDU asdu;
    int idxValor[8];
    int idxQual[8];
} PublicadorSV;

static int64_t tsParaNs(const struct timespec* t) {
    return (int64_t) t->tv_sec * 1000000000LL + t->tv_nsec;
}

static void nsParaTs(int64_t ns, struct timespec* t) {
    t->tv_sec = ns / 1000000000LL;
    t->tv_nsec = ns % 1000000000LL;
}

static void* threadSV(void* arg) {
    PublicadorSV* sv = (PublicadorSV*) arg;

    // Prioridade de tempo real: ajuda a manter o ritmo de 4800 mensagens/s
    struct sched_param sp;
    memset(&sp, 0, sizeof(sp));
    sp.sched_priority = 80;
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp) != 0)
        LOG_PRINT("[SV] Aviso: sem prioridade de tempo real (rode com sudo). O SV sai, mas com mais variacao.\n");

    const double w = 2.0 * M_PI / AMOSTRAS_POR_CICLO;       // angulo entre duas amostras
    const double r2 = sqrt(2.0);
    const double vFase = V_LINHA_KV * 1000.0 / sqrt(3.0);    // tensao de fase eficaz (V)
    const double angCarga = ANG_CARGA_GRAUS * M_PI / 180.0;
    const double angFalta = ANG_FALTA_GRAUS * M_PI / 180.0;
    const double c120 = 2.0 * M_PI / 3.0;

    struct timespec agora;
    clock_gettime(CLOCK_MONOTONIC, &agora);
    const int64_t t0 = tsParaNs(&agora);
    uint64_t n = 0;                                          // numero da amostra desde o inicio

    while (running) {
        // Instante desta amostra (conta feita em duas partes para nunca estourar)
        int64_t alvo = t0 + (int64_t) (n / AMOSTRAS_POR_SEG) * 1000000000LL
                          + (int64_t) ((n % AMOSTRAS_POR_SEG) * 1000000000ULL / AMOSTRAS_POR_SEG);
        struct timespec tAlvo;
        nsParaTs(alvo, &tAlvo);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tAlvo, NULL);

        // Atrasou mais de 1 ciclo? Pula para o presente.
        clock_gettime(CLOCK_MONOTONIC, &agora);
        int64_t atraso = tsParaNs(&agora) - alvo;
        if (atraso > 1000000000LL / FREQ_HZ) {
            int64_t passou = tsParaNs(&agora) - t0;
            uint64_t nAgora = (uint64_t) (passou / 1000000000LL) * AMOSTRAS_POR_SEG
                            + (uint64_t) ((passou % 1000000000LL) * AMOSTRAS_POR_SEG / 1000000000LL);
            svPuladas += (uint32_t) (nAgora - n);
            n = nAgora;
        }

        // Formas de onda. A posicao dentro do ciclo vem de n % 80, assim o
        // angulo nao perde precisao com o tempo.
        double wt = w * (double) (n % AMOSTRAS_POR_CICLO);
        int falta = arvoreNaLinha;

        double va = r2 * vFase * (falta ? V_FALTA_PU : 1.0) * sin(wt);
        double vb = r2 * vFase * sin(wt - c120);
        double vc = r2 * vFase * sin(wt + c120);
        double vn = va + vb + vc;                            // tensao residual

        double ia = falta ? r2 * I_FALTA_A * sin(wt - angFalta)
                          : r2 * I_CARGA_A * sin(wt - angCarga);
        double ib = r2 * I_CARGA_A * sin(wt - c120 - angCarga);
        double ic = r2 * I_CARGA_A * sin(wt + c120 - angCarga);
        double in = ia + ib + ic;                            // corrente de neutro

        double valores[8] = { ia * ESCALA_I, ib * ESCALA_I, ic * ESCALA_I, in * ESCALA_I,
                              va * ESCALA_V, vb * ESCALA_V, vc * ESCALA_V, vn * ESCALA_V };

        for (int i = 0; i < 8; i++) {
            SVPublisher_ASDU_setINT32(sv->asdu, sv->idxValor[i], (int32_t) lround(valores[i]));
            SVPublisher_ASDU_setQuality(sv->asdu, sv->idxQual[i], QUALITY_VALIDITY_GOOD);
        }
        SVPublisher_ASDU_setSmpCnt(sv->asdu, (uint16_t) (n % AMOSTRAS_POR_SEG));
        SVPublisher_publish(sv->pub);

        svEnviadas++;
        n++;
    }
    return NULL;
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    if (!travarInstancia("empelas_mu")) {
        LOG_PRINT("ERRO: o empelas_mu ja esta rodando nesta Pi. Feche o outro (Ctrl+C no terminal dele)\n"
                  "      ou procure com:  ps aux | grep empelas_mu\n");
        exit(1);
    }

#ifndef SEM_BOTAO
    if (wiringPiSetup() == -1) {
        LOG_PRINT("[BOTAO] Aviso: wiringPi nao iniciou (rode com sudo). Seguindo sem botao fisico.\n");
    } else {
        pinMode(BOTAO_PINO, INPUT);
        pullUpDnControl(BOTAO_PINO, PUD_UP);
        pinMode(LED_PINO, OUTPUT);
        digitalWrite(LED_PINO, LOW);
        botaoOk = 1;
    }
#endif

    // Evita que o programa seja jogado para a memoria de troca (atrasaria o SV)
    mlockall(MCL_CURRENT | MCL_FUTURE);

    // Silencia os printf's padrao da biblioteca (LOG_PRINT usa stderr)
    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    // Comando do supervisorio: FLTGGIO1.SPCSO1
    IedServer_updateCtlModel(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1, checkHandlerFalta, NULL);
    IedServer_setControlHandler(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1, (ControlHandler) controlHandlerFalta, NULL);

    IedServer_start(iedServer, tcpPort);
    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor! (porta %d ocupada ou falta sudo)\n", tcpPort);
        IedServer_destroy(iedServer);
        exit(-1);
    }

    // Estado inicial: linha normal
    IedServer_lockDataModel(iedServer);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1_stVal, false);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MU01_FLTGGIO1_SPCSO1_t, Hal_getTimeInMs());
    IedServer_unlockDataModel(iedServer);

    // Publicador de SV
    PublicadorSV sv;
    CommParameters par;
    par.vlanPriority = SV_VLAN_PRIO;
    par.vlanId = SV_VLAN_ID;
    par.appId = SV_APPID;
    memcpy(par.dstAddress, SV_DSTMAC, 6);

    sv.pub = SVPublisher_create(&par, INTERFACE_SV);
    if (sv.pub == NULL) {
        LOG_PRINT("[SV] ERRO: nao consegui abrir a interface %s. Confira o cabo/nome da interface e rode com sudo.\n", INTERFACE_SV);
        IedServer_stop(iedServer);
        IedServer_destroy(iedServer);
        exit(-1);
    }
    // svID e confRev vao em toda mensagem. O nome do conjunto de dados nao
    // vai (o 9-2LE nao usa), por isso o NULL.
    sv.asdu = SVPublisher_addASDU(sv.pub, SV_ID, NULL, SV_CONFREV);
    for (int i = 0; i < 8; i++) {
        sv.idxValor[i] = SVPublisher_ASDU_addINT32(sv.asdu);
        sv.idxQual[i] = SVPublisher_ASDU_addQuality(sv.asdu);
    }
    SVPublisher_setupComplete(sv.pub);
    // Relogio da MU nao e sincronizado com nada (sem GPS/PTP): smpSynch = 0.
    // Esta funcao so pode ser chamada depois do setupComplete.
    SVPublisher_ASDU_setSmpSynch(sv.asdu, IEC61850_SV_SMPSYNC_NOT_SYNCHRONIZED);

    LOG_PRINT("\n--- EmpElas_MU : MERGING UNIT (TC e TP digitais da linha) ---\n");
    LOG_PRINT("[SV]     Publicando em %s: svID %s, APPID 0x%04X, %d amostras/ciclo (%d por segundo).\n",
              INTERFACE_SV, SV_ID, SV_APPID, AMOSTRAS_POR_CICLO, AMOSTRAS_POR_SEG);
    LOG_PRINT("[LINHA]  Normal: %.0f kV entre fases, %.0f A por fase. Falta: fase A com %.0f A.\n",
              V_LINHA_KV, I_CARGA_A, I_FALTA_A);
#ifndef SEM_BOTAO
    if (botaoOk)
        LOG_PRINT("[BOTAO]  Botao no pino fisico 11 (e GND). LED no pino fisico 13. Cada aperto alterna a falta.\n");
#else
    LOG_PRINT("[BOTAO]  Compilado sem botao fisico (SEM_BOTAO). Falta so pelo supervisorio.\n");
#endif
    LOG_PRINT("[STATUS] Servidor na porta %d. Supervisorio: FLTGGIO1.SPCSO1 (1 = arvore cai, 0 = retira).\n", tcpPort);

    running = 1;

    pthread_t tSV;
    int svThreadOk = (pthread_create(&tSV, NULL, threadSV, &sv) == 0);
    if (!svThreadOk) {
        LOG_PRINT("[SV] ERRO: nao consegui criar a thread do SV.\n");
        running = 0;
    }

#ifndef SEM_BOTAO
    Thread tBotao = NULL;
    if (botaoOk) {
        tBotao = Thread_create((ThreadExecutionFunction) threadBotao, NULL, false);
        Thread_start(tBotao);
    }
#endif

    // Laco principal: mostra um resumo a cada 10 s
    uint32_t enviadasAntes = 0;
    int segundos = 0;
    while (running) {
        Thread_sleep(1000);
        if (++segundos % 10 == 0) {
            uint32_t total = svEnviadas;
            LOG_PRINT("[SV] %u mensagens/s | puladas por atraso: %u | arvore na linha: %s\n",
                      (unsigned) ((total - enviadasAntes) / 10), (unsigned) svPuladas,
                      arvoreNaLinha ? "SIM" : "nao");
            enviadasAntes = total;
        }
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    if (svThreadOk) pthread_join(tSV, NULL);
#ifndef SEM_BOTAO
    if (tBotao) Thread_destroy(tBotao);
    if (botaoOk) digitalWrite(LED_PINO, LOW);
#endif
    SVPublisher_destroy(sv.pub);
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    if (dev_null != -1) close(dev_null);
    return 0;
}
