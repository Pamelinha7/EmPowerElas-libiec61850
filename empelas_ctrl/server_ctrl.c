/*
 * EmPowerElas - Maquete de Subestacao Digital
 * IED de controle de vao (Raspberry Pi 2)
 *
 * LEDs dos disjuntores (XCBR1-3), servo da chave seccionadora (XSWI1)
 * e fita enderecavel WS2811 representando o caminho da fibra optica.
 *
 * A fita (12V, ~50 pixels) acende progressivamente a qualquer comando
 * vindo do SCADA, com um atraso apos a atuacao - o sinal correndo pela
 * fibra depois da acao.
 *
 * Fita: dado no GPIO21 (fisico 40, PCM) via level shifter 3.3->5V.
 * Servo no PWM de hardware (GPIO18). PCM e PWM sao perifericos
 * separados, entao nao ha conflito.
 *
 * Compilar e rodar nesta Pi:
 *   make
 *   sudo ./empelas_ctrl
 */

#include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringSerial.h>
#include <string.h>
#include <wiringPi.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ws2811.h"          // biblioteca rpi_ws281x (link: libws2811.a)

// ================= SERVO (chave seccionadora XSWI1) ===========
#define SERVO_PIN     1     // wiringPi 1 = BCM18 = Físico 12 (PWM de hardware)
#define PWM_DIVISOR   192
#define PWM_RANGE     2000
#define TICK_FECHADO  100
#define TICK_ABERTO   200

// ================= LEDs DOS DISJUNTORES (XCBR) ===============
#define LED_D1_VERDE  0   // wPi 0 = Físico 11
#define LED_D1_VERM   2   // wPi 2 = Físico 13
#define LED_D2_VERDE  3   // wPi 3 = Físico 15
#define LED_D2_VERM   4   // wPi 4 = Físico 16
#define LED_D3_VERDE  5   // wPi 5 = Físico 18
#define LED_D3_VERM   6   // wPi 6 = Físico 22

// ================= FITA WS2811 (rastro da fibra) ============
#define FITA_GPIO       21        // GPIO21 = Físico 40 (PCM)
#define FITA_DMA        10        // canal de DMA da rpi_ws281x
#define FITA_COUNT      50        // ~50 pixels (150 LEDs / 3 por chip). Ajuste se precisar.
#define FITA_FREQ       WS2811_TARGET_FREQ  // 800kHz
#define FITA_BRILHO     128       // 0-255 (metade p/ reduzir corrente)
#define FITA_COR        0x0000FF00 // cor "energizado" no formato 0x00RRGGBB (aqui: verde)
#define FITA_DELAY_MS   800       // atraso entre o comando e o inicio do rastro
#define FITA_PASSO_MS   100        // tempo por LED (50 * 100ms = ~5s p/ preencher)

// ==============================================================

#include "static_model.h"

static int running = 0;
static IedServer iedServer = NULL;
static int activeConnections = 0;
static volatile int rastroPendente = 0;   // sinaliza que um comando pediu o rastro

// Estrutura da fita: gpionum 21 faz a lib usar PCM automaticamente.
static ws2811_t fita = {
    .freq = FITA_FREQ,
    .dmanum = FITA_DMA,
    .channel = {
        [0] = {
            .gpionum = FITA_GPIO,
            .invert = 0,
            .count = FITA_COUNT,
            .strip_type = WS2811_STRIP_RGB,  // WS2811 costuma ser RGB; troque p/ GRB se a cor sair trocada
            .brightness = FITA_BRILHO,
        },
        [1] = { .gpionum = 0, .invert = 0, .count = 0, .brightness = 0 },
    },
};

void sigint_handler(int signalId) { running = 0; }

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

// Apaga toda a fita
static void fitaApaga(void) {
    for (int i = 0; i < FITA_COUNT; i++) fita.channel[0].leds[i] = 0;
    ws2811_render(&fita);
}

static void moverServo(int tickAlvo) {
    pwmWrite(SERVO_PIN, tickAlvo);
    delay(500);
    pwmWrite(SERVO_PIN, 0);
}

static void setLedsDisjuntor(int pinVerde, int pinVerm, bool fechado) {
    digitalWrite(pinVerde, fechado ? HIGH : LOW);
    digitalWrite(pinVerm,  fechado ? LOW  : HIGH);
}

// Thread da fita: espera um comando (rastroPendente), da o delay e preenche LED a LED.
void* fita_thread(void* arg) {
    while (running) {
        if (rastroPendente) {
            rastroPendente = 0;

            // 1) DELAY: o comando ja atuou (servo/LED); a fita comeca depois
            Thread_sleep(FITA_DELAY_MS);

            // 2) Limpa e preenche progressivamente (o "rastro" correndo pela fibra)
            fitaApaga();
            for (int i = 0; i < FITA_COUNT && running; i++) {
                int fase = (i * 256 / FITA_COUNT);
uint8_t r = fase;
uint8_t g = 255 - fase;
uint8_t b = (fase * 2) % 256;
fita.channel[0].leds[i] = (r << 16) | (g << 8) | b;
                ws2811_render(&fita);
                Thread_sleep(FITA_PASSO_MS);
            }
            LOG_PRINT("[FITA] Rastro concluido (subestacao energizada).\n");
        }
        Thread_sleep(20);
    }
    return NULL;
}

static void connectionHandler(IedServer self, ClientConnection connection, bool connected, void* parameter) {
    const char* clientIP = ClientConnection_getPeerAddress(connection);
    if (connected) {
        activeConnections++;
        if (activeConnections == 1) {
            LOG_PRINT("\n[SISTEMA] >>> CLIENTE CONECTADO (%s) <<<\n", clientIP);
        }
    } else {
        if (activeConnections > 0) activeConnections--;
        if (activeConnections == 0) LOG_PRINT("\n[SISTEMA] Cliente Desconectado (%s)\n", clientIP);
    }
}

static CheckHandlerResult checkHandler(ControlAction action, void* parameter, MmsValue* ctlVal, bool test, bool interlockCheck) {
    if (parameter == IEDMODEL_VAO_XSWI1_Pos ||
        parameter == IEDMODEL_VAO_XCBR1_Pos ||
        parameter == IEDMODEL_VAO_XCBR2_Pos ||
        parameter == IEDMODEL_VAO_XCBR3_Pos)
        return CONTROL_ACCEPTED;
    return CONTROL_OBJECT_UNDEFINED;
}

static ControlHandlerResult controlHandlerForBinaryOutput(ControlAction action, void* parameter, MmsValue* value, bool test) {
    uint64_t timestamp = Hal_getTimeInMs();
    int ctlNum = ControlAction_getCtlNum(action);
    ClientConnection clientCon = ControlAction_getClientConnection(action);
    const char* clientIP = (clientCon) ? ClientConnection_getPeerAddress(clientCon) : "Desconhecido";

    if (parameter == IEDMODEL_VAO_XSWI1_Pos ||
        parameter == IEDMODEL_VAO_XCBR1_Pos ||
        parameter == IEDMODEL_VAO_XCBR2_Pos ||
        parameter == IEDMODEL_VAO_XCBR3_Pos)
    {
        bool state = false;
        MmsValue* ctlVal = value;
        if (MmsValue_getType(value) == MMS_STRUCTURE) ctlVal = MmsValue_getElement(value, 0);

        if (ctlVal != NULL) {
            if (MmsValue_getType(ctlVal) == MMS_BIT_STRING) {
                int val = MmsValue_getBitStringAsInteger(ctlVal);
                state = (val == 2);
            } else if (MmsValue_getType(ctlVal) == MMS_BOOLEAN) {
                state = MmsValue_getBoolean(ctlVal);
            } else if (MmsValue_getType(ctlVal) == MMS_INTEGER) {
                state = (MmsValue_toInt32(ctlVal) > 0);
            }
        }

        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[COMANDO] Recebido de: %s\n", clientIP);

        if (parameter == IEDMODEL_VAO_XSWI1_Pos) {
            moverServo(state ? TICK_FECHADO : TICK_ABERTO);
            LOG_PRINT("   >> Acao: XSWI1 (Seccionadora/Servo) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XCBR1_Pos) {
            setLedsDisjuntor(LED_D1_VERDE, LED_D1_VERM, state);
            LOG_PRINT("   >> Acao: XCBR1 (Disjuntor 1) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR1_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR1_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XCBR2_Pos) {
            setLedsDisjuntor(LED_D2_VERDE, LED_D2_VERM, state);
            LOG_PRINT("   >> Acao: XCBR2 (Disjuntor 2) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR2_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR2_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XCBR3_Pos) {
            setLedsDisjuntor(LED_D3_VERDE, LED_D3_VERM, state);
            LOG_PRINT("   >> Acao: XCBR3 (Disjuntor 3) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR3_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR3_Pos_stVal, value);
        }

        // Qualquer comando dispara o rastro da fita (a thread aplica o delay)
        rastroPendente = 1;

        LOG_PRINT("--------------------------------------------------\n");
    } else {
        return CONTROL_RESULT_FAILED;
    }
    return CONTROL_RESULT_OK;
}

static MmsDataAccessError writeAccessHandler(DataAttribute* dataAttribute, MmsValue* value, ClientConnection connection, void* parameter) {
    ControlModel ctlModelVal = (ControlModel) MmsValue_toInt32(value);
    if ((ctlModelVal == CONTROL_MODEL_STATUS_ONLY) || (ctlModelVal == CONTROL_MODEL_DIRECT_NORMAL)) {
        if (dataAttribute == IEDMODEL_VAO_XSWI1_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI1_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XCBR1_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XCBR2_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XCBR3_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, ctlModelVal);
        return DATA_ACCESS_ERROR_SUCCESS;
    }
    return DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "ERRO: wiringPi falhou. Rode como root (sudo).\n");
        exit(1);
    }

    // Servo
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(PWM_DIVISOR);
    pwmSetRange(PWM_RANGE);
    pwmWrite(SERVO_PIN, TICK_FECHADO);
    delay(500);
    pwmWrite(SERVO_PIN, 0);

    // LEDs (todos ABERTOS no boot = vermelho aceso)
    pinMode(LED_D1_VERDE, OUTPUT); pinMode(LED_D1_VERM, OUTPUT);
    pinMode(LED_D2_VERDE, OUTPUT); pinMode(LED_D2_VERM, OUTPUT);
    pinMode(LED_D3_VERDE, OUTPUT); pinMode(LED_D3_VERM, OUTPUT);
    setLedsDisjuntor(LED_D1_VERDE, LED_D1_VERM, false);
    setLedsDisjuntor(LED_D2_VERDE, LED_D2_VERM, false);
    setLedsDisjuntor(LED_D3_VERDE, LED_D3_VERM, false);

    // Fita WS2811
    ws2811_return_t ret = ws2811_init(&fita);
    if (ret != WS2811_SUCCESS) {
        LOG_PRINT("[FITA] ws2811_init FALHOU: %s\n", ws2811_get_return_t_str(ret));
    } else {
        fitaApaga();  // comeca apagada
        LOG_PRINT("[FITA] Inicializada em GPIO%d (PCM), %d pixels.\n", FITA_GPIO, FITA_COUNT);
    }

    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI1_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, CONTROL_MODEL_DIRECT_NORMAL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XSWI1_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XSWI1_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XSWI1_Pos, checkHandler, IEDMODEL_VAO_XSWI1_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XSWI1_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XCBR1_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XCBR1_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XCBR1_Pos, checkHandler, IEDMODEL_VAO_XCBR1_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XCBR1_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XCBR2_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XCBR2_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XCBR2_Pos, checkHandler, IEDMODEL_VAO_XCBR2_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XCBR2_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XCBR3_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XCBR3_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XCBR3_Pos, checkHandler, IEDMODEL_VAO_XCBR3_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XCBR3_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setConnectionIndicationHandler(iedServer, (IedConnectionIndicationHandler) connectionHandler, NULL);
    // ATENCAO: "lo" e a interface de loopback. Quando o GOOSE de trip vindo
    // do EmpElas_PROT for implementado, isto precisa virar a interface de rede
    // real (ex.: "eth0"), senao a mensagem nunca chega nesta placa.
    IedServer_setGooseInterfaceId(iedServer, "lo");
    IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        ws2811_fini(&fita);
        exit(-1);
    }

    LOG_PRINT("\n--- EmpElas_CTRL : CONTROLE DE VAO (LEDs + servo + fita) ---\n");
    LOG_PRINT("[STATUS] Servo:P%d | LEDs D1-D3 | Fita GPIO%d (%d px)\n", SERVO_PIN, FITA_GPIO, FITA_COUNT);
    LOG_PRINT("[STATUS] Rodando na porta %d. Aguardando comandos do SCADA...\n", tcpPort);

    running = 1;
    Thread fitaThread = Thread_create((ThreadExecutionFunction)fita_thread, NULL, true);
    Thread_start(fitaThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    pwmWrite(SERVO_PIN, 0);
    digitalWrite(LED_D1_VERDE, LOW); digitalWrite(LED_D1_VERM, LOW);
    digitalWrite(LED_D2_VERDE, LOW); digitalWrite(LED_D2_VERM, LOW);
    digitalWrite(LED_D3_VERDE, LOW); digitalWrite(LED_D3_VERM, LOW);
    fitaApaga();
    ws2811_fini(&fita);
    Thread_sleep(300);

    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    close(dev_null);
    return 0;
}