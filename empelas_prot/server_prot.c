/*
 * EmPowerElas - Maquete de Subestacao Digital
 * IED de medicao e protecao (Raspberry Pi 1)
 *
 * Dois LCD 1602 mostrando as grandezas dos transformadores de instrumento:
 *   LCD1 -> TC (corrente, A)
 *   LCD2 -> TP (tensao, kV)
 *
 * Os mesmos valores sao publicados no modelo IEC 61850 (MMXU1) para o
 * SCADA ler.
 *
 * PROTECAO E GOOSE
 * O supervisorio aplica uma falta escrevendo em GGIO1.SPCSO1. A corrente
 * simulada sobe acima do ajuste, a protecao de sobrecorrente (PTOC1) atua,
 * e o sinal de trip (PTRC1.Tr) e publicado por GOOSE para o IED de
 * controle de vao, que abre o disjuntor.
 *
 * A publicacao e automatica: o PTRC1.Tr.general faz parte do conjunto de
 * dados dsTrip, associado ao bloco gcbTrip no .icd. Toda vez que o valor
 * muda, a biblioteca envia o GOOSE e o repete em intervalos crescentes;
 * sem mudanca, reenvia a cada 1 s como sinal de vida.
 *
 * Compilar e rodar nesta Pi:
 *   java -jar genmodel.jar empelas_prot.icd   (sempre que o .icd mudar)
 *   make
 *   sudo ./empelas_prot
 */

#include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <lcd.h>            // biblioteca de LCD do wiringPi (link: -lwiringPiDev)
#include <time.h>

// ================= DISPLAY 1 (TC - corrente) =================
#define LCD1_RS  7   // wPi 7  = Físico 7
#define LCD1_E   11  // wPi 11 = Físico 26
#define LCD1_D4  12  // wPi 12 = Físico 19
#define LCD1_D5  13  // wPi 13 = Físico 21
#define LCD1_D6  14  // wPi 14 = Físico 23
#define LCD1_D7  26  // wPi 26 = Físico 32

// ================= DISPLAY 2 (TP - tensao) ==================
#define LCD2_RS  0   // wPi 0  = Físico 11
#define LCD2_E   6   // wPi 6  = Físico 22
#define LCD2_D4  2   // wPi 2  = Físico 13
#define LCD2_D5  3   // wPi 3  = Físico 15
#define LCD2_D6  22  // wPi 22 = Físico 31
#define LCD2_D7  27  // wPi 27 = Físico 36

// ================= GRANDEZAS E PROTECAO =====================
#define TC_BASE        100.0f   // corrente normal (A)
#define TP_BASE        500.0f   // tensao normal (kV)
#define TC_FALTA       800.0f   // corrente durante a falta simulada (A)
#define PTOC_PARTIDA   300.0f   // ajuste da sobrecorrente instantanea (A)

// A protecao e avaliada a cada 50 ms; os displays e as medicoes,
// a cada 1 s. Assim o trip nao espera o ciclo lento dos displays.
#define CICLO_MS        50
#define CICLOS_POR_SEG  (1000 / CICLO_MS)

// Interface de rede onde o GOOSE e publicado. Precisa ser o CABO:
// o GOOSE nao atravessa o wi-fi de forma confiavel.
#ifndef INTERFACE_GOOSE
#define INTERFACE_GOOSE "eth0"
#endif

// ============================================================

#include "static_model.h"

static int running = 0;
static IedServer iedServer = NULL;
static int lcd1 = -1;   // handle do display 1 (TC)
static int lcd2 = -1;   // handle do display 2 (TP)

static volatile int faltaAtiva = 0;   // escrita pelo supervisorio via GGIO1.SPCSO1
static bool tripAtivo = false;        // estado atual do trip publicado

void sigint_handler(int signalId) { running = 0; }

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

// ----------------------------------------------------------------
// Protecao de sobrecorrente instantanea (funcao ANSI 50).
//
// So escreve no modelo quando o estado MUDA. Isso importa: cada escrita
// no PTRC1.Tr dispara um GOOSE novo, e publicar o mesmo valor a cada
// 50 ms inundaria a rede sem necessidade.
//
// O selo de tempo e o do instante da deteccao, recebido como parametro,
// e nao o do momento da publicacao.
// ----------------------------------------------------------------
static void avaliarProtecao(float corrente, uint64_t ts) {
    bool deveAtuar = (corrente > PTOC_PARTIDA);
    if (deveAtuar == tripAtivo) return;

    tripAtivo = deveAtuar;

    IedServer_lockDataModel(iedServer);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_general, deveAtuar);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Str_t, ts);
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_general, deveAtuar);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTOC1_Op_t, ts);
    // Esta e a escrita que dispara o GOOSE (PTRC1.Tr.general esta no dsTrip)
    IedServer_updateBooleanAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_general, deveAtuar);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_PTRC1_Tr_t, ts);
    IedServer_unlockDataModel(iedServer);

    if (deveAtuar)
        LOG_PRINT("[PROTECAO] Sobrecorrente: %.1f A > %.1f A. TRIP publicado por GOOSE.\n",
                  corrente, PTOC_PARTIDA);
    else
        LOG_PRINT("[PROTECAO] Corrente normalizada. Trip retirado, GOOSE publicado.\n");
}

static void publicarMedicoes(float tc, float tp, uint64_t ts) {
    uint16_t goodQuality = 0x0000;
    IedServer_lockDataModel(iedServer);
    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Amp_instMag_f, tc);
    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Amp_mag_f, tc);
    IedServer_updateQuality(iedServer, IEDMODEL_MEDPROT_MMXU1_Amp_q, goodQuality);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Amp_t, ts);
    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Vol_instMag_f, tp);
    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Vol_mag_f, tp);
    IedServer_updateQuality(iedServer, IEDMODEL_MEDPROT_MMXU1_Vol_q, goodQuality);
    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_MMXU1_Vol_t, ts);
    IedServer_unlockDataModel(iedServer);
}

static void atualizarDisplays(float tc, float tp) {
    char buf[17];

    // LCD1: corrente. Durante o trip, a primeira linha avisa o envio do GOOSE.
    if (lcd1 >= 0) {
        lcdPosition(lcd1, 0, 0);
        lcdPuts(lcd1, tripAtivo ? "TRIP-GOOSE ENV. " : "CORRENTE (TC)   ");
        snprintf(buf, sizeof(buf), "   %6.1f A     ", tc);
        buf[16] = '\0';
        lcdPosition(lcd1, 0, 1);
        lcdPuts(lcd1, buf);
    }

    // LCD2: tensao
    if (lcd2 >= 0) {
        lcdPosition(lcd2, 0, 0);
        lcdPuts(lcd2, "TENSAO (TP)     ");
        snprintf(buf, sizeof(buf), "  %6.1f kV     ", tp);
        buf[16] = '\0';
        lcdPosition(lcd2, 0, 1);
        lcdPuts(lcd2, buf);
    }
}

// Thread principal da medicao e da protecao.
void* display_thread(void* arg) {
    float tcNormal = TC_BASE;
    float tp = TP_BASE;
    int ciclo = 0;
    int faltaAnterior = -1;

    while (running) {
        int faltaAgora = faltaAtiva;
        bool novoSegundo = (ciclo % CICLOS_POR_SEG == 0);

        // Valores normais com pequena variacao, renovados a cada segundo
        if (novoSegundo) {
            tcNormal = TC_BASE + ((rand() % 200) - 100) / 10.0f;   // ~90 a 110 A
            tp       = TP_BASE + ((rand() % 100) - 50)  / 10.0f;   // ~495 a 505 kV
        }

        float tc = faltaAgora ? TC_FALTA : tcNormal;
        uint64_t ts = Hal_getTimeInMs();

        // A protecao roda em todo ciclo de 50 ms
        avaliarProtecao(tc, ts);

        // Medicoes e displays: a cada segundo, ou na hora em que a falta muda
        if (novoSegundo || faltaAgora != faltaAnterior) {
            publicarMedicoes(tc, tp, ts);
            atualizarDisplays(tc, tp);
            LOG_PRINT("[SIM] TC: %.1f A | TP: %.1f kV%s\n", tc, tp, faltaAgora ? "  <- FALTA" : "");
            faltaAnterior = faltaAgora;
        }

        ciclo++;
        Thread_sleep(CICLO_MS);
    }
    return NULL;
}

// ----------------------------------------------------------------
// Botao "aplicar falta" do supervisorio: GGIO1.SPCSO1
//   true  -> aplica a falta (corrente sobe para TC_FALTA)
//   false -> retira a falta
// ----------------------------------------------------------------
static CheckHandlerResult checkHandlerFalta(ControlAction action, void* parameter, MmsValue* ctlVal, bool test, bool interlockCheck) {
    return CONTROL_ACCEPTED;
}

static ControlHandlerResult controlHandlerFalta(ControlAction action, void* parameter, MmsValue* value, bool test) {
    if (MmsValue_getType(value) != MMS_BOOLEAN)
        return CONTROL_RESULT_FAILED;

    bool aplicar = MmsValue_getBoolean(value);
    faltaAtiva = aplicar ? 1 : 0;

    IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_MEDPROT_GGIO1_SPCSO1_t, Hal_getTimeInMs());
    IedServer_updateAttributeValue(iedServer, IEDMODEL_MEDPROT_GGIO1_SPCSO1_stVal, value);

    ClientConnection con = ControlAction_getClientConnection(action);
    LOG_PRINT("--------------------------------------------------\n");
    LOG_PRINT("[COMANDO] %s a falta (origem: %s)\n", aplicar ? "APLICAR" : "RETIRAR",
              con ? ClientConnection_getPeerAddress(con) : "desconhecida");
    LOG_PRINT("--------------------------------------------------\n");

    return CONTROL_RESULT_OK;
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "ERRO: Falha ao inicializar o wiringPi! Rode como root (sudo).\n");
        exit(1);
    }

    // Inicializa os dois displays (modo 4 bits)
    srand((unsigned) time(NULL));
    lcd1 = lcdInit(2, 16, 4, LCD1_RS, LCD1_E, LCD1_D4, LCD1_D5, LCD1_D6, LCD1_D7, 0, 0, 0, 0);
    lcd2 = lcdInit(2, 16, 4, LCD2_RS, LCD2_E, LCD2_D4, LCD2_D5, LCD2_D6, LCD2_D7, 0, 0, 0, 0);
    if (lcd1 >= 0) { lcdClear(lcd1); lcdPosition(lcd1, 0, 0); lcdPuts(lcd1, "Display 1 - TC"); }
    if (lcd2 >= 0) { lcdClear(lcd2); lcdPosition(lcd2, 0, 0); lcdPuts(lcd2, "Display 2 - TP"); }

    // Silencia os printf's padrao da biblioteca (LOG_PRINT usa stderr e continua aparecendo)
    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    // Botao de falta do supervisorio
    IedServer_updateCtlModel(iedServer, IEDMODEL_MEDPROT_GGIO1_SPCSO1, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_MEDPROT_GGIO1_SPCSO1, checkHandlerFalta, NULL);
    IedServer_setControlHandler(iedServer, IEDMODEL_MEDPROT_GGIO1_SPCSO1, (ControlHandler) controlHandlerFalta, NULL);

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

    LOG_PRINT("\n--- EmpElas_PROT : MEDICAO E PROTECAO ---\n");
    LOG_PRINT("[STATUS] LCD1 (TC) %s | LCD2 (TP) %s\n", (lcd1 >= 0) ? "OK" : "FALHOU", (lcd2 >= 0) ? "OK" : "FALHOU");
    LOG_PRINT("[STATUS] Rodando na porta %d.\n", tcpPort);
    LOG_PRINT("[GOOSE]  Publicando gcbTrip em %s (APPID 0x1001).\n", INTERFACE_GOOSE);
    LOG_PRINT("[PROTECAO] Sobrecorrente instantanea, partida em %.0f A.\n", PTOC_PARTIDA);

    running = 1;
    Thread displayThread = Thread_create((ThreadExecutionFunction)display_thread, NULL, true);
    Thread_start(displayThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    IedServer_disableGoosePublishing(iedServer);
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    close(dev_null);
    return 0;
}
