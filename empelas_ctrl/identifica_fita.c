/*
 * EmPowerElas - Maquete de Subestacao Digital
 * IED de controle de vao (Raspberry Pi 2)
 *
 * LEDs dos disjuntores (XCBR1-3), tres servos das chaves seccionadoras
 * (XSWI1-3) e fita enderecavel WS2811 representando o caminho da fibra.
 *
 * A fita (12V, ~50 pixels) acende progressivamente a qualquer comando
 * vindo do SCADA, com um atraso apos a atuacao - o sinal correndo pela
 * fibra depois da acao.
 *
 * Fita: dado no GPIO21 (fisico 40, PCM) via level shifter 3.3->5V.
 *
 * SERVOS: o Raspberry tem apenas dois canais de PWM de hardware, e os
 * pinos fisicos 33 e 35 compartilham o mesmo canal (PWM1) - portanto e
 * impossivel ter os tres servos em hardware. O servo 1 fica no PWM de
 * hardware (PWM0) e os outros dois usam PWM por software.
 *
 * Isso funciona porque moverServo corta o sinal apos o movimento: o
 * pulso so existe durante os 500 ms da manobra, e as chaves nao se
 * movem ao mesmo tempo. Fora esse intervalo nao ha PWM nenhum, entao
 * nao ha tremor.
 *
 * ALIMENTACAO: nao alimente os servos pelo pino de 5V da Pi. Use fonte
 * separada com o terra ligado ao da Pi, senao a placa reinicia sozinha
 * no pico de corrente de partida.
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
#include <softPwm.h>       // PWM por software (servos 2 e 3)
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ws2811.h"          // biblioteca rpi_ws281x (link: libws2811.a)

// ============ SERVOS DAS CHAVES SECCIONADORAS (XSWI1-3) =======
// Servo 1 - PWM de hardware
#define SERVO1_PIN    1     // wiringPi 1  = BCM18 = Físico 12 (PWM0)
#define PWM_DIVISOR   192   // 19,2 MHz / 192 = 100 kHz
#define PWM_RANGE     2000  // 100 kHz / 2000 = 50 Hz (periodo de 20 ms)
#define TICK_FECHADO  100   // 100/2000 * 20 ms = 1,0 ms
#define TICK_ABERTO   200   // 200/2000 * 20 ms = 2,0 ms

// Servos 2 e 3 - PWM por software
#define SERVO2_PIN    23    // wiringPi 23 = BCM13 = Físico 33
#define SERVO3_PIN    24    // wiringPi 24 = BCM19 = Físico 35
#define SOFT_RANGE    200   // 200 passos de 100 us = 20 ms (50 Hz)
#define SOFT_FECHADO  10    // 10 * 100 us = 1,0 ms
#define SOFT_ABERTO   20    // 20 * 100 us = 2,0 ms

// ================= LEDs DOS DISJUNTORES (XCBR) ===============
#define LED_D1_VERDE  0   // wPi 0 = Físico 11
#define LED_D1_VERM   2   // wPi 2 = Físico 13
#define LED_D2_VERDE  3   // wPi 3 = Físico 15
#define LED_D2_VERM   4   // wPi 4 = Físico 16
#define LED_D3_VERDE  5   // wPi 5 = Físico 18
#define LED_D3_VERM   6   // wPi 6 = Físico 22

// ================= FITA WS2811 (caminho da fibra) ============
// A fita representa a fibra optica e tem DOIS comportamentos:
//
//   MEDICAO  - pulso lento e discreto, rodando o tempo todo, sem parar.
//              Representa o fluxo continuo de grandezas do TC e do TP.
//              Numa subestacao real esse trafego nunca cessa, entao a
//              animacao tambem nao para e nao depende de comando nenhum.
//
//   COMANDO  - rastro rapido e vivo, disparado quando chega um comando
//              do SCADA. Representa a mensagem de manobra, que e
//              episodica. Ele interrompe o pulso de medicao, que
//              retoma de onde parou - assim como uma mensagem de
//              manobra tem prioridade sobre o trafego continuo.
//
// Os dois pedacos de fita sao encadeados em serie (saida de dados de um
// na entrada do outro), entao para a Pi e uma corrente unica.
#define FITA_GPIO       21        // GPIO21 = Físico 40 (PCM)
#define FITA_DMA        10        // canal de DMA da rpi_ws281x
// ATENCAO: um "pixel" comanda TRES LEDs juntos. O pedaco em teste tem
// 18 quadradinhos = 6 pixels. Quando a fita definitiva for montada e os
// dois pedacos emendados, conte os quadradinhos, divida por 3 e ajuste
// este numero. Os tempos abaixo sao por VOLTA COMPLETA, entao a
// velocidade da animacao nao muda quando a fita cresce.
#define FITA_COUNT      6         // AJUSTE: total de pixels (quadradinhos / 3)
#define FITA_FREQ       WS2811_TARGET_FREQ  // 800kHz
#define FITA_BRILHO     128       // 0-255 (metade p/ reduzir corrente)

// Cores no formato 0x00RRGGBB
#define COR_MEDICAO     0x00003848  // ciano discreto - trafego continuo
#define COR_COMANDO     0x00FFB020  // ambar forte - mensagem de manobra

// Tempo de uma volta completa na fita, em ms
#define MED_VOLTA_MS    3000      // medicao: lenta, para nao competir com a atencao
#define CMD_VOLTA_MS    1000      // comando: rapida, e uma mensagem

// Comprimento da cauda de cada pulso, em pixels
#define MED_CAUDA       2       // com poucos pixels, cauda curta fica mais legivel
#define CMD_CAUDA       2

// Atraso entre o comando atuar e o rastro comecar.
// Zero porque, na realidade, a mensagem viaja ANTES do equipamento operar.
#define FITA_DELAY_MS   0

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

// Escurece uma cor por um fator de 0 a 100 por cento.
static uint32_t corAtenuada(uint32_t cor, int pct) {
    uint8_t r = ((cor >> 16) & 0xFF) * pct / 100;
    uint8_t g = ((cor >>  8) & 0xFF) * pct / 100;
    uint8_t b = ( cor        & 0xFF) * pct / 100;
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// Desenha um pulso com cauda na posicao dada, apagando o resto da fita.
// A cauda vai ficando mais fraca atras da cabeca, dando sensacao de
// movimento em vez de um ponto piscando.
static void fitaDesenhaPulso(int pos, uint32_t cor, int cauda) {
    for (int i = 0; i < FITA_COUNT; i++) fita.channel[0].leds[i] = 0;

    for (int c = 0; c < cauda; c++) {
        int idx = pos - c;
        if (idx < 0) idx += FITA_COUNT;          // volta ao fim da fita
        if (idx < 0 || idx >= FITA_COUNT) continue;
        int intensidade = 100 - (c * 100 / (cauda + 1));
        fita.channel[0].leds[idx] = corAtenuada(cor, intensidade);
    }
    ws2811_render(&fita);
}

// Servo 1: PWM de hardware. O sinal e cortado apos o movimento para
// eliminar o tremor do servo parado sob comando.
static void moverServo1(bool fechar) {
    pwmWrite(SERVO1_PIN, fechar ? TICK_FECHADO : TICK_ABERTO);
    delay(500);
    pwmWrite(SERVO1_PIN, 0);
}

// Servos 2 e 3: PWM por software, mesmo principio.
static void moverServoSoft(int pino, bool fechar) {
    softPwmWrite(pino, fechar ? SOFT_FECHADO : SOFT_ABERTO);
    delay(500);
    softPwmWrite(pino, 0);
}

static void setLedsDisjuntor(int pinVerde, int pinVerm, bool fechado) {
    digitalWrite(pinVerde, fechado ? HIGH : LOW);
    digitalWrite(pinVerm,  fechado ? LOW  : HIGH);
}

// Thread da fita.
//
// Em repouso, roda o pulso lento de medicao indefinidamente. Quando um
// comando chega (rastroPendente), o pulso de medicao cede a vez: o rastro
// rapido atravessa a fita e, ao terminar, a medicao retoma de onde parou.
void* fita_thread(void* arg) {
    int posMedicao = 0;

    // Passo de cada animacao, derivado do tempo de volta e do tamanho da fita
    const int medPassoMs = (FITA_COUNT > 0) ? (MED_VOLTA_MS / FITA_COUNT) : 50;
    const int cmdPassoMs = (FITA_COUNT > 0) ? (CMD_VOLTA_MS / FITA_COUNT) : 20;

    while (running) {

        if (rastroPendente) {
            rastroPendente = 0;

            if (FITA_DELAY_MS > 0) Thread_sleep(FITA_DELAY_MS);

            // Rastro do comando: atravessa a fita uma vez, do inicio ao fim
            for (int i = 0; i < FITA_COUNT && running; i++) {
                fitaDesenhaPulso(i, COR_COMANDO, CMD_CAUDA);
                Thread_sleep(cmdPassoMs);
            }
            LOG_PRINT("[FITA] Mensagem de manobra percorreu a fibra.\n");

            // Volta ao pulso de medicao de onde ele estava
            continue;
        }

        // Repouso: pulso continuo de medicao
        fitaDesenhaPulso(posMedicao, COR_MEDICAO, MED_CAUDA);
        posMedicao = (posMedicao + 1) % FITA_COUNT;
        Thread_sleep(medPassoMs);
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
        parameter == IEDMODEL_VAO_XSWI2_Pos ||
        parameter == IEDMODEL_VAO_XSWI3_Pos ||
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
        parameter == IEDMODEL_VAO_XSWI2_Pos ||
        parameter == IEDMODEL_VAO_XSWI3_Pos ||
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
            moverServo1(state);
            LOG_PRINT("   >> Acao: XSWI1 (Seccionadora 1) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XSWI2_Pos) {
            moverServoSoft(SERVO2_PIN, state);
            LOG_PRINT("   >> Acao: XSWI2 (Seccionadora 2) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI2_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI2_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XSWI3_Pos) {
            moverServoSoft(SERVO3_PIN, state);
            LOG_PRINT("   >> Acao: XSWI3 (Seccionadora 3) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI3_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI3_Pos_stVal, value);
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
        else if (dataAttribute == IEDMODEL_VAO_XSWI2_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI2_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XSWI3_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI3_Pos, ctlModelVal);
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

    // ORDEM IMPORTA: o softPwmCreate cria threads que mexem no subsistema
    // de PWM, e pwmSetClock/pwmSetRange sao globais no wiringPi. Se o PWM
    // por software for iniciado DEPOIS da configuracao do PWM de hardware,
    // o servo 1 recebe pulso com periodo errado e nao se move.
    // Por isso os servos 2 e 3 sao criados primeiro.

    // Servos 2 e 3 - PWM por software
    if (softPwmCreate(SERVO2_PIN, 0, SOFT_RANGE) != 0)
        LOG_PRINT("[SERVO] softPwmCreate falhou no pino %d\n", SERVO2_PIN);
    if (softPwmCreate(SERVO3_PIN, 0, SOFT_RANGE) != 0)
        LOG_PRINT("[SERVO] softPwmCreate falhou no pino %d\n", SERVO3_PIN);

    // Servo 1 - PWM de hardware (configurado por ultimo)
    pinMode(SERVO1_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(PWM_DIVISOR);
    pwmSetRange(PWM_RANGE);

    // Posicao inicial: todas as chaves fechadas, uma de cada vez
    moverServo1(true);
    moverServoSoft(SERVO2_PIN, true);
    moverServoSoft(SERVO3_PIN, true);

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
        fitaApaga();
        LOG_PRINT("[FITA] Inicializada em GPIO%d (PCM), %d pixels.\n", FITA_GPIO, FITA_COUNT);
        LOG_PRINT("[FITA] Pulso de medicao continuo ativo.\n");
    }

    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI1_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI2_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI3_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, CONTROL_MODEL_DIRECT_NORMAL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XSWI1_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XSWI1_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XSWI1_Pos, checkHandler, IEDMODEL_VAO_XSWI1_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XSWI1_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XSWI2_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XSWI2_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XSWI2_Pos, checkHandler, IEDMODEL_VAO_XSWI2_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XSWI2_Pos_ctlModel, writeAccessHandler, NULL);

    IedServer_setControlHandler(iedServer, IEDMODEL_VAO_XSWI3_Pos, (ControlHandler) controlHandlerForBinaryOutput, IEDMODEL_VAO_XSWI3_Pos);
    IedServer_setPerformCheckHandler(iedServer, IEDMODEL_VAO_XSWI3_Pos, checkHandler, IEDMODEL_VAO_XSWI3_Pos);
    IedServer_handleWriteAccess(iedServer, IEDMODEL_VAO_XSWI3_Pos_ctlModel, writeAccessHandler, NULL);

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
    LOG_PRINT("[STATUS] Servos: P%d (hw), P%d e P%d (sw) | LEDs D1-D3 | Fita GPIO%d (%d px)\n", SERVO1_PIN, SERVO2_PIN, SERVO3_PIN, FITA_GPIO, FITA_COUNT);
    LOG_PRINT("[STATUS] Rodando na porta %d. Aguardando comandos do SCADA...\n", tcpPort);

    running = 1;
    Thread fitaThread = Thread_create((ThreadExecutionFunction)fita_thread, NULL, true);
    Thread_start(fitaThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    pwmWrite(SERVO1_PIN, 0);
    softPwmWrite(SERVO2_PIN, 0);
    softPwmWrite(SERVO3_PIN, 0);
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