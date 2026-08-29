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
 * Compilar e rodar nesta Pi:
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

// ============================================================

#include "static_model.h"

static int running = 0;
static IedServer iedServer = NULL;
static int lcd1 = -1;   // handle do display 1 (TC)
static int lcd2 = -1;   // handle do display 2 (TP)

void sigint_handler(int signalId) { running = 0; }

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

// Thread dos displays: simula TC e TP, escreve um em cada LCD e atualiza o MMXU1.
void* display_thread(void* arg) {
    const float TC_BASE = 100.0f;  // corrente base (A)
    const float TP_BASE = 500.0f;  // tensao base (kV)
    char buf[17];

    while (running) {
        float tc = TC_BASE + ((rand() % 200) - 100) / 10.0f; // ~90.0 a 110.0 A
        float tp = TP_BASE + ((rand() % 100) - 50)  / 10.0f; // ~495.0 a 505.0 kV

        // --- Atualiza o modelo IEC 61850 (MMXU1) para o SCADA ---
        uint64_t ts = Hal_getTimeInMs();
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

        // --- LCD1: TC (corrente) ---
        if (lcd1 >= 0) {
            lcdPosition(lcd1, 0, 0);
            lcdPuts(lcd1, "CORRENTE (TC)   ");
            snprintf(buf, sizeof(buf), "   %6.1f A     ", tc);
            buf[16] = '\0';
            lcdPosition(lcd1, 0, 1);
            lcdPuts(lcd1, buf);
        }

        // --- LCD2: TP (tensao) ---
        if (lcd2 >= 0) {
            lcdPosition(lcd2, 0, 0);
            lcdPuts(lcd2, "TENSAO (TP)     ");
            snprintf(buf, sizeof(buf), "  %6.1f kV     ", tp);
            buf[16] = '\0';
            lcdPosition(lcd2, 0, 1);
            lcdPuts(lcd2, buf);
        }

        LOG_PRINT("[SIM] TC: %.1f A | TP: %.1f kV\n", tc, tp);
        Thread_sleep(1000);
    }
    return NULL;
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

    // ATENCAO: "lo" e a interface de loopback. Quando o GOOSE entre as duas
    // Pis for implementado, isto precisa virar a interface de rede real
    // (ex.: "eth0"), senao a mensagem nunca sai desta placa.
    IedServer_setGooseInterfaceId(iedServer, "lo");
    IedServer_start(iedServer, tcpPort);
    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    LOG_PRINT("\n--- EmpElas_PROT : MEDICAO (TC/TP simulados) ---\n");
    LOG_PRINT("[STATUS] LCD1 (TC) %s | LCD2 (TP) %s\n", (lcd1 >= 0) ? "OK" : "FALHOU", (lcd2 >= 0) ? "OK" : "FALHOU");
    LOG_PRINT("[STATUS] Rodando na porta %d. SCADA le TC/TP em MEDPROT/MMXU1 (Amp/Vol).\n", tcpPort);

    running = 1;
    Thread displayThread = Thread_create((ThreadExecutionFunction)display_thread, NULL, true);
    Thread_start(displayThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    close(dev_null);
    return 0;
}
