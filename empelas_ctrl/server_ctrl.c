/*
 * EmPowerElas - Maquete de Subestacao Digital
 * IED de controle de vao (Raspberry Pi 2)
 *
 * LEDs dos disjuntores (XCBR1-3), tres servos das chaves seccionadoras
 * (XSWI1-3) e fita enderecavel WS2811 representando o caminho da fibra.
 *
 * FITA DA FIBRA OPTICA (WS2811, 12 V)
 * Representa a comunicacao, com tres comportamentos:
 *   - pulso lento ciano, continuo: o trafego de medicao, que nunca para;
 *   - rastro ambar: um comando chegando do SCADA (MMS);
 *   - rastro vermelho: o TRIP chegando por GOOSE do EmpElas_PROT.
 *
 * Dado no GPIO18 (fisico 12, PWM), DIRETO no GPIO (sem level shifter,
 * que a 800kHz atrasa o sinal e deixa a fita sempre acesa). Usa o PWM
 * da Pi, que ficou livre quando os servos foram para o PCA9685. O audio
 * analogico da Pi tambem usa o PWM, por isso precisa estar desligado.
 *
 * GOOSE DE TRIP
 * Este IED assina o GOOSE gcbTrip publicado pelo EmpElas_PROT. Quando
 * chega um trip novo, o disjuntor 1 abre e a fita mostra a mensagem.
 * Quando o trip e retirado, o disjuntor CONTINUA ABERTO: quem fecha e
 * o operador, pelo SCADA, como numa subestacao real.
 *
 * SERVOS: os tres servos sao comandados pelo modulo PCA9685 via I2C.
 * O PCA9685 gera o PWM em hardware proprio, entao os servos nao
 * disputam o PWM nem o temporizador da Pi - o que deixa o PWM da Pi
 * livre para a fita e elimina o tremor do PWM por software.
 *
 * O I2C precisa estar habilitado no sistema (raspi-config) e o modulo
 * deve aparecer no endereco 0x40 em 'sudo i2cdetect -y 1'.
 *
 * ALIMENTACAO: os servos sao alimentados pelo borne V+ do PCA9685, com
 * fonte externa de 5 V. Nunca pelo pino de 5 V da Pi - o pico de
 * corrente de partida derruba a placa. O terra da fonte precisa estar
 * ligado ao terra da Pi.
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
#include <wiringPiI2C.h>   // comunicacao com o PCA9685
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ws2811.h"          // biblioteca rpi_ws281x (link: libws2811.a)
#include "goose_receiver.h"  // recepcao de GOOSE (libiec61850)
#include "goose_subscriber.h"

// ====== SERVOS DAS CHAVES SECCIONADORAS (XSWI1-3) via PCA9685 =====
#define PCA_ADDR      0x40  // endereco I2C padrao do modulo
#define PCA_MODE1     0x00  // registrador de modo
#define PCA_PRESCALE  0xFE  // divisor de frequencia
#define PCA_LED0_ON_L 0x06  // primeiro registrador do canal 0

// Canal do PCA9685 onde cada servo esta ligado (0 a 15)
#define SERVO1_CH     0     // seccionadora 1
#define SERVO2_CH     1     // seccionadora 2
#define SERVO3_CH     2     // seccionadora 3

// O PCA9685 divide cada periodo em 4096 passos. A 50 Hz o periodo e de
// 20 ms, entao 1 passo = 20/4096 ms.
#define PCA_FREQ      50.0f
#define TICK_FECHADO  205   // ~1,0 ms
#define TICK_ABERTO   410   // ~2,0 ms
#define PCA_FULL_OFF  4096  // bit especial que desliga o canal por completo

// ================= LEDs DOS DISJUNTORES (XCBR) ===============
#define LED_D1_VERDE  0   // wPi 0 = Fisico 11
#define LED_D1_VERM   2   // wPi 2 = Fisico 13
#define LED_D2_VERDE  3   // wPi 3 = Fisico 15
#define LED_D2_VERM   4   // wPi 4 = Fisico 16
#define LED_D3_VERDE  5   // wPi 5 = Fisico 18
#define LED_D3_VERM   6   // wPi 6 = Fisico 22

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
// Os pedacos de fita sao encadeados em serie (saida de dados de um na
// entrada do outro), com TODAS as setas no mesmo sentido, entao para a
// Pi e uma corrente unica.
#define FITA_GPIO       18        // GPIO18 = Fisico 12 (PWM) - fita da fibra optica
#define FITA_DMA        10        // canal de DMA da rpi_ws281x
// ATENCAO: um "pixel" comanda TRES LEDs juntos. Conte os quadradinhos da
// fita, divida por 3 e ajuste este numero. Os tempos abaixo sao por VOLTA
// COMPLETA, entao a velocidade da animacao nao muda quando a fita cresce.
#define FITA_COUNT      19         // AJUSTE: total de pixels (quadradinhos / 3)
#define FITA_FREQ       WS2811_TARGET_FREQ  // 800kHz
#define FITA_BRILHO     128       // 0-255 (metade p/ reduzir corrente)

// Cores no formato 0x00RRGGBB
#define COR_MEDICAO     0x00003848  // ciano discreto - trafego continuo
#define COR_COMANDO     0x00FFB020  // ambar forte - comando do SCADA (MMS)
#define COR_TRIP        0x00FF0000  // vermelho - trip chegando por GOOSE

// Tempo de uma volta completa na fita, em ms
#define MED_VOLTA_MS    3000      // medicao: lenta, para nao competir com a atencao
#define CMD_VOLTA_MS    1000      // comando: rapida, e uma mensagem

// Comprimento da cauda de cada pulso, em pixels
#define MED_CAUDA       2       // com poucos pixels, cauda curta fica mais legivel
#define CMD_CAUDA       2

// Atraso entre o comando atuar e o rastro comecar.
// Zero porque, na realidade, a mensagem viaja ANTES do equipamento operar.
#define FITA_DELAY_MS   0

// ================= GOOSE DE TRIP (vindo do EmpElas_PROT) =========
// Estes valores precisam ser IGUAIS aos do empelas_prot.icd.
#define GOOSE_INTERFACE   "eth0"                                  // o CABO; GOOSE nao atravessa wi-fi
#define GOOSE_TRIP_REF    "EmpElas_PROTMEDPROT/LLN0$GO$gcbTrip"   // bloco GOOSE do IED de protecao
#define GOOSE_TRIP_APPID  0x1001                                  // APPID do .icd
// Endereco de destino (MAC-Address do .icd). Informar o endereco faz a
// placa de rede aceitar esse grupo; sem ele, a mensagem e descartada
// antes de chegar ao programa - foi o que aconteceu no primeiro teste.
static uint8_t GOOSE_TRIP_DSTMAC[6] = {0x01, 0x0c, 0xcd, 0x01, 0x00, 0x01};

// Qual disjuntor o trip abre. Para trocar, mude as quatro linhas juntas.
#define DJ_TRIP_NOME      "Disjuntor 1 (XCBR1)"
#define DJ_TRIP_VERDE     LED_D1_VERDE
#define DJ_TRIP_VERM      LED_D1_VERM
#define DJ_TRIP_STVAL     IEDMODEL_VAO_XCBR1_Pos_stVal
#define DJ_TRIP_T         IEDMODEL_VAO_XCBR1_Pos_t

// Tipos de rastro na fita (valor de rastroPendente)
#define RASTRO_COMANDO    1
#define RASTRO_TRIP       2

// ==============================================================

#include "static_model.h"

static int running = 0;
static IedServer iedServer = NULL;
static int activeConnections = 0;
static volatile int rastroPendente = 0;   // 0 = nada; RASTRO_COMANDO ou RASTRO_TRIP
static GooseReceiver gooseReceiver = NULL;
static int64_t ultimoStNum = -1;          // ultimo estado de GOOSE ja tratado
static int pcaFd = -1;                    // descritor I2C do PCA9685

// Estrutura da fita: gpionum 18 faz a lib usar o PWM automaticamente.
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

// Ajusta a frequencia de PWM do PCA9685. Exige colocar o chip em modo
// sleep para escrever o prescaler, e DEPOIS ACORDAR (SLEEP=0), senao o
// oscilador fica desligado e nao sai PWM nenhum - o servo nao mexe mesmo
// com o modulo detectado no I2C.
static void pcaSetFreq(int fd, float freq) {
    int prescale = (int)(25000000.0f / (4096.0f * freq) - 1.0f + 0.5f);
    int oldmode  = wiringPiI2CReadReg8(fd, PCA_MODE1);
    int sleepmode = (oldmode & 0x7F) | 0x10;                 // SLEEP=1 p/ escrever o prescale
    wiringPiI2CWriteReg8(fd, PCA_MODE1, sleepmode);
    wiringPiI2CWriteReg8(fd, PCA_PRESCALE, prescale);
    int wakemode = oldmode & ~0x10;                          // >>> GARANTE SLEEP=0 <<<
    wiringPiI2CWriteReg8(fd, PCA_MODE1, wakemode);           // acorda o oscilador
    delay(5);
    wiringPiI2CWriteReg8(fd, PCA_MODE1, wakemode | 0xA0);    // restart + auto-increment, SLEEP=0
}

// Escreve o pulso de um canal. Cada canal ocupa 4 registradores.
static void pcaSetPwm(int fd, int canal, int on, int off) {
    int reg = PCA_LED0_ON_L + 4 * canal;
    wiringPiI2CWriteReg8(fd, reg,     on  & 0xFF);
    wiringPiI2CWriteReg8(fd, reg + 1, on  >> 8);
    wiringPiI2CWriteReg8(fd, reg + 2, off & 0xFF);
    wiringPiI2CWriteReg8(fd, reg + 3, off >> 8);
}

// Move um servo e corta o pulso em seguida. Sem o corte, o servo fica
// tremendo e zumbindo enquanto estiver sob comando.
static void moverServo(int canal, bool fechar) {
    if (pcaFd < 0) return;
    pcaSetPwm(pcaFd, canal, 0, fechar ? TICK_FECHADO : TICK_ABERTO);
    delay(500);
    pcaSetPwm(pcaFd, canal, 0, PCA_FULL_OFF);
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
            int tipo = rastroPendente;
            rastroPendente = 0;
            uint32_t cor = (tipo == RASTRO_TRIP) ? COR_TRIP : COR_COMANDO;

            if (FITA_DELAY_MS > 0) Thread_sleep(FITA_DELAY_MS);

            // Rastro da mensagem: atravessa a fita uma vez, do inicio ao fim
            for (int i = 0; i < FITA_COUNT && running; i++) {
                fitaDesenhaPulso(i, cor, CMD_CAUDA);
                Thread_sleep(cmdPassoMs);
            }
            LOG_PRINT("[FITA] %s percorreu a fibra.\n",
                      (tipo == RASTRO_TRIP) ? "Trip por GOOSE" : "Comando do SCADA");

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

// ----------------------------------------------------------------
// Abre o disjuntor comandado pelo trip: LEDs e posicao no modelo.
// Roda na thread de recepcao do GOOSE, por isso trava o modelo antes
// de escrever nele.
// ----------------------------------------------------------------
static void abrirDisjuntorPorTrip(void) {
    setLedsDisjuntor(DJ_TRIP_VERDE, DJ_TRIP_VERM, false);

    // Mesma convencao dos comandos do SCADA neste projeto: 1 = aberto,
    // 2 = fechado (valor lido com MmsValue_getBitStringAsInteger).
    // Nao usar IedServer_updateDbposValue aqui: ela codifica os bits na
    // ordem inversa, e o SCADA passaria a ler "2" (fechado) apos o trip.
    MmsValue* posAberta = MmsValue_newBitString(2);
    MmsValue_setBitStringFromInteger(posAberta, 1);

    IedServer_lockDataModel(iedServer);
    IedServer_updateAttributeValue(iedServer, DJ_TRIP_STVAL, posAberta);
    IedServer_updateUTCTimeAttributeValue(iedServer, DJ_TRIP_T, Hal_getTimeInMs());
    IedServer_unlockDataModel(iedServer);

    MmsValue_delete(posAberta);
}

// ----------------------------------------------------------------
// Chamada a cada GOOSE de trip recebido.
//
// O GOOSE repete a mesma mensagem varias vezes de proposito (sqNum sobe,
// stNum fica igual). So o stNum novo indica mudanca de estado, entao so
// ele e tratado - as repeticoes sao ignoradas.
// ----------------------------------------------------------------
static void gooseTripListener(GooseSubscriber sub, void* parameter) {
    uint32_t stNum = GooseSubscriber_getStNum(sub);
    if ((int64_t) stNum == ultimoStNum) return;          // repeticao do mesmo estado

    bool primeira = (ultimoStNum < 0);
    ultimoStNum = stNum;

    MmsValue* valores = GooseSubscriber_getDataSetValues(sub);
    MmsValue* tr = valores ? MmsValue_getElement(valores, 0) : NULL;
    if (tr == NULL || MmsValue_getType(tr) != MMS_BOOLEAN) {
        LOG_PRINT("[GOOSE] Mensagem com formato inesperado (stNum=%u), ignorada.\n", stNum);
        return;
    }

    if (MmsValue_getBoolean(tr)) {
        rastroPendente = RASTRO_TRIP;                    // a fita mostra a mensagem
        abrirDisjuntorPorTrip();
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[GOOSE] TRIP recebido do EmpElas_PROT (stNum=%u)\n", stNum);
        LOG_PRINT("   >> Acao: %s ABERTO pela protecao\n", DJ_TRIP_NOME);
        LOG_PRINT("--------------------------------------------------\n");
    }
    else if (primeira) {
        LOG_PRINT("[GOOSE] Assinatura do trip ativa (stNum=%u, sem trip).\n", stNum);
    }
    else {
        LOG_PRINT("[GOOSE] Trip retirado (stNum=%u). %s continua aberto: fechar pelo SCADA.\n",
                  stNum, DJ_TRIP_NOME);
    }
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
            moverServo(SERVO1_CH, state);
            LOG_PRINT("   >> Acao: XSWI1 (Seccionadora 1) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI1_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XSWI2_Pos) {
            moverServo(SERVO2_CH, state);
            LOG_PRINT("   >> Acao: XSWI2 (Seccionadora 2) %s\n", state ? "FECHADA" : "ABERTA");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XSWI2_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XSWI2_Pos_stVal, value);
        }
        else if (parameter == IEDMODEL_VAO_XSWI3_Pos) {
            moverServo(SERVO3_CH, state);
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

        // Qualquer comando do SCADA dispara o rastro ambar na fita
        rastroPendente = RASTRO_COMANDO;

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

    // PCA9685 - controlador de PWM dos tres servos, via I2C
    pcaFd = wiringPiI2CSetup(PCA_ADDR);
    if (pcaFd < 0) {
        LOG_PRINT("[SERVO] ERRO: PCA9685 nao encontrado no endereco 0x%02X.\n", PCA_ADDR);
        LOG_PRINT("[SERVO] Habilite o I2C (raspi-config) e confira com 'sudo i2cdetect -y 1'.\n");
    } else {
        pcaSetFreq(pcaFd, PCA_FREQ);
        LOG_PRINT("[SERVO] PCA9685 ok em 0x%02X, %d Hz.\n", PCA_ADDR, (int)PCA_FREQ);
    }

    // Posicao inicial: todas as chaves fechadas, uma de cada vez para
    // nao somar corrente de partida
    moverServo(SERVO1_CH, true);
    moverServo(SERVO2_CH, true);
    moverServo(SERVO3_CH, true);

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
        LOG_PRINT("[FITA] Inicializada em GPIO%d (PWM), %d pixels.\n", FITA_GPIO, FITA_COUNT);
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
    // Interface de PUBLICACAO de GOOSE deste IED. Ele ainda nao publica nada,
    // entao pode ficar em "lo". A RECEPCAO do trip e configurada abaixo,
    // no GooseReceiver, e essa sim usa o cabo (GOOSE_INTERFACE).
    IedServer_setGooseInterfaceId(iedServer, "lo");
    IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        ws2811_fini(&fita);
        exit(-1);
    }

    // Assinatura do GOOSE de trip vindo do EmpElas_PROT
    gooseReceiver = GooseReceiver_create();
    GooseReceiver_setInterfaceId(gooseReceiver, GOOSE_INTERFACE);
    GooseSubscriber subTrip = GooseSubscriber_create(GOOSE_TRIP_REF, NULL);
    GooseSubscriber_setDstMac(subTrip, GOOSE_TRIP_DSTMAC);
    GooseSubscriber_setAppId(subTrip, GOOSE_TRIP_APPID);
    GooseSubscriber_setListener(subTrip, gooseTripListener, NULL);
    GooseReceiver_addSubscriber(gooseReceiver, subTrip);
    GooseReceiver_start(gooseReceiver);

    LOG_PRINT("\n--- EmpElas_CTRL : CONTROLE DE VAO (LEDs + servo + fita) ---\n");
    if (GooseReceiver_isRunning(gooseReceiver))
        LOG_PRINT("[GOOSE] Escutando o trip em %s (APPID 0x%04X). Abre: %s.\n",
                  GOOSE_INTERFACE, GOOSE_TRIP_APPID, DJ_TRIP_NOME);
    else
        LOG_PRINT("[GOOSE] ERRO: receptor nao iniciou. Confira se %s existe e se rodou com sudo.\n",
                  GOOSE_INTERFACE);
    LOG_PRINT("[STATUS] Servos: canais %d, %d e %d do PCA9685 | LEDs D1-D3 | Fita GPIO%d (%d px)\n", SERVO1_CH, SERVO2_CH, SERVO3_CH, FITA_GPIO, FITA_COUNT);
    LOG_PRINT("[STATUS] Rodando na porta %d. Aguardando comandos do SCADA...\n", tcpPort);

    running = 1;
    Thread fitaThread = Thread_create((ThreadExecutionFunction)fita_thread, NULL, true);
    Thread_start(fitaThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    if (gooseReceiver) {
        GooseReceiver_stop(gooseReceiver);
        GooseReceiver_destroy(gooseReceiver);   // destroi tambem o assinante
    }
    if (pcaFd >= 0) {
        pcaSetPwm(pcaFd, SERVO1_CH, 0, PCA_FULL_OFF);
        pcaSetPwm(pcaFd, SERVO2_CH, 0, PCA_FULL_OFF);
        pcaSetPwm(pcaFd, SERVO3_CH, 0, PCA_FULL_OFF);
    }
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