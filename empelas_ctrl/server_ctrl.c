/*
 * EmPowerElas - Maquete de Subestacao Digital
 * Pi do servo (Raspberry Pi 2): EmpElas_CTRL
 *
 * Faz o papel dos equipamentos de patio "inteligentes": LEDs dos disjuntores
 * (XCBR1-3), tres servos das chaves seccionadoras (XSWI1-3) e a fita
 * enderecavel WS2811 representando o caminho da fibra.
 *
 * CONVERSA COM O IED DE CONTROLE (EmpElas_PROT, Pi das telinhas) POR GOOSE
 *   - publica gcbPos: a posicao dos 3 disjuntores e das 3 chaves. E assim
 *     que o intertravamento (CILO) do IED de controle sabe o que esta aberto;
 *   - assina gcbTrip: o trip da protecao, que abre o disjuntor 1;
 *   - assina gcbCmd: os comandos de abrir e fechar as chaves (CSWI.OpOpn e
 *     CSWI.OpCls). So chegam aqui comandos que o intertravamento ja liberou.
 *
 * As chaves NAO aceitam comando direto do supervisorio: o Pos delas fica em
 * status-only. Todo comando de chave passa pelo IED de controle, senao daria
 * para passar por cima do intertravamento. Os disjuntores continuam
 * aceitando comando do supervisorio (MMS), como antes.
 *
 * FITA DA FIBRA OPTICA (WS2811, 12 V)
 * Representa a comunicacao, com tres comportamentos:
 *   - pulso lento ciano, continuo: o trafego de medicao, que nunca para;
 *   - rastro ambar: um comando chegando (disjuntor pelo SCADA, chave por GOOSE);
 *   - rastro vermelho: o TRIP chegando por GOOSE do EmpElas_PROT.
 *
 * Fita atual: 5 m, 300 LEDs (60 por metro), 12 V. Cada chip WS2811 comanda
 * um grupo de 3 LEDs, entao sao 100 "pixels". Comprimento e ordem das
 * cores ficam em FITA_COUNT e FITA_TIPO; o programa testes/teste_fita
 * ajuda a descobrir os dois.
 *
 * Dado no GPIO18 (fisico 12, PWM), DIRETO no GPIO (o level shifter que
 * foi testado era lento para 800kHz e deixava a fita sempre acesa). Usa o PWM
 * da Pi, que ficou livre quando os servos foram para o PCA9685. O audio
 * analogico da Pi tambem usa o PWM, por isso precisa estar desligado.
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
#include <sys/file.h>
#include <pthread.h>
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
//              (do SCADA para um disjuntor, ou por GOOSE para uma chave).
//              Representa a mensagem de manobra, que e episodica. Ele
//              interrompe o pulso de medicao, que retoma de onde parou -
//              assim como uma mensagem de manobra tem prioridade sobre o
//              trafego continuo.
//
// Os pedacos de fita sao encadeados em serie (saida de dados de um na
// entrada do outro), com TODAS as setas no mesmo sentido, entao para a
// Pi e uma corrente unica.
#define FITA_GPIO       18        // GPIO18 = Fisico 12 (PWM) - fita da fibra optica
#define FITA_DMA        10        // canal de DMA da rpi_ws281x
// ATENCAO: na fita de 12 V, um "pixel" e um chip WS2811 que comanda TRES
// LEDs juntos (o grupo entre duas marcas de corte). Fita inteira de 5 m com
// 60 LEDs/m = 300 LEDs = 100 pixels. Se cortarem a fita, use o numero de
// LEDs do pedaco dividido por 3 (confira com testes/teste_fita, passo 2).
// Os tempos abaixo sao por VOLTA COMPLETA, entao a velocidade da animacao
// nao muda quando a fita cresce.
#define FITA_COUNT      100        // AJUSTE: total de pixels (LEDs / 3)

// Ordem das cores dentro de cada pixel. Muda de um fabricante para outro.
// Descubra com testes/teste_fita (passo 1) e troque se precisar por:
// WS2811_STRIP_RGB, _RBG, _GRB, _GBR, _BRG ou _BGR.
#define FITA_TIPO       WS2811_STRIP_RGB
#define FITA_FREQ       WS2811_TARGET_FREQ  // 800kHz
#define FITA_BRILHO     128       // 0-255 (metade p/ reduzir corrente)

// Cores no formato 0x00RRGGBB
#define COR_MEDICAO     0x00003848  // ciano discreto - trafego continuo
#define COR_COMANDO     0x00FFB020  // ambar forte - comando (SCADA ou GOOSE)
#define COR_TRIP        0x00FF0000  // vermelho - trip chegando por GOOSE

// Tempo de uma volta completa na fita, em ms
#define MED_VOLTA_MS    3000      // medicao: lenta, para nao competir com a atencao
#define CMD_VOLTA_MS    1000      // comando: rapida, e uma mensagem

// Comprimento da cauda de cada pulso, em pixels. Cresce junto com a fita:
// numa fita curta fica em 2; com 100 pixels, 8 na medicao e 12 no comando.
#define MED_CAUDA       ((FITA_COUNT / 12 > 2) ? FITA_COUNT / 12 : 2)
#define CMD_CAUDA       ((FITA_COUNT / 8 > 2) ? FITA_COUNT / 8 : 2)

// Atraso entre o comando atuar e o rastro comecar.
// Zero porque, na realidade, a mensagem viaja ANTES do equipamento operar.
#define FITA_DELAY_MS   0

// ================= GOOSE (sempre pelo CABO) ======================
// GOOSE nao atravessa wi-fi nem roteamento: vale so na rede da maquete.
#ifndef GOOSE_INTERFACE
#define GOOSE_INTERFACE   "eth0"
#endif

// Trip vindo do EmpElas_PROT. Valores IGUAIS aos do empelas_prot.icd.
#define GOOSE_TRIP_REF    "EmpElas_PROTMEDPROT/LLN0$GO$gcbTrip"   // bloco GOOSE do IED de protecao
#define GOOSE_TRIP_APPID  0x1001                                  // APPID do .icd
// Endereco de destino (MAC-Address do .icd). Informar o endereco faz a
// placa de rede aceitar esse grupo; sem ele, a mensagem e descartada
// antes de chegar ao programa - foi o que aconteceu no primeiro teste.
static uint8_t GOOSE_TRIP_DSTMAC[6] = {0x01, 0x0c, 0xcd, 0x01, 0x00, 0x01};

// Comandos das chaves vindos do IED de controle (EmpElas_PROT).
// O conjunto de dados (dsCmd) traz 6 valores, nesta ordem:
//   CSWI1.OpOpn, CSWI1.OpCls, CSWI2.OpOpn, CSWI2.OpCls, CSWI3.OpOpn, CSWI3.OpCls
// Cada um vira "verdadeiro" durante o comando. A chave mexe na SUBIDA
// (quando passa de falso para verdadeiro).
#define GOOSE_CMD_REF     "EmpElas_PROTMEDPROT/LLN0$GO$gcbCmd"
#define GOOSE_CMD_APPID   0x1003
static uint8_t GOOSE_CMD_DSTMAC[6] = {0x01, 0x0c, 0xcd, 0x01, 0x00, 0x03};

// O GOOSE de POSICOES publicado por esta Pi esta descrito no empelas_ctrl.icd:
// gcbPos, APPID 0x1002, MAC 01-0C-CD-01-00-02. Ordem do dsPos:
//   XCBR1, XCBR2, XCBR3, XSWI1, XSWI2, XSWI3 (Pos.stVal de cada um)

// Qual disjuntor o trip abre. Para trocar, mude as cinco linhas juntas.
#define DJ_TRIP_INDICE    0                       // 0 = disjuntor 1
#define DJ_TRIP_NOME      "Disjuntor 1 (XCBR1)"
#define DJ_TRIP_VERDE     LED_D1_VERDE
#define DJ_TRIP_VERM      LED_D1_VERM
#define DJ_TRIP_STVAL     IEDMODEL_VAO_XCBR1_Pos_stVal
#define DJ_TRIP_T         IEDMODEL_VAO_XCBR1_Pos_t

// Posicao de ponto duplo, no mesmo formato que o supervisorio le
// (MmsValue_getBitStringAsInteger): 0 = em movimento, 1 = aberto,
// 2 = fechado, 3 = invalido.
#define POS_INTERMEDIARIA 0
#define POS_ABERTA        1
#define POS_FECHADA       2

// Tipos de rastro na fita (valor de rastroPendente)
#define RASTRO_COMANDO    1
#define RASTRO_TRIP       2

// ==============================================================

#include "static_model.h"

static volatile int running = 0;
static IedServer iedServer = NULL;
static int activeConnections = 0;
static volatile int rastroPendente = 0;   // 0 = nada; RASTRO_COMANDO ou RASTRO_TRIP
static GooseReceiver gooseReceiver = NULL;
static int64_t ultimoStNum = -1;          // ultimo estado do GOOSE de trip ja tratado
static int64_t ultimoStNumCmd = -1;       // stNum do ultimo GOOSE de comandos (so para o log)
static bool cmdAnterior[6];               // valores do ultimo GOOSE de comandos
static int pcaFd = -1;                    // descritor I2C do PCA9685
static bool fitaOk = false;               // a fita so e usada se iniciou bem

// ----------------------------------------------------------------
// As tres chaves. O pedido de manobra e deixado aqui pelo GOOSE de
// comandos e executado pela thread do patio (o servo leva meio segundo,
// e o receptor de GOOSE nao pode ficar parado esse tempo todo).
// ----------------------------------------------------------------
typedef struct {
    const char*    nome;
    int            canal;      // canal do PCA9685
    DataAttribute* stVal;      // XSWIn.Pos.stVal
    DataAttribute* t;          // XSWIn.Pos.t
    DataAttribute* opCnt;      // XSWIn.OpCnt.stVal (contador de manobras)
    DataAttribute* opCntT;
} Chave;

static Chave chaves[3] = {
    { "Seccionadora 1 (XSWI1)", SERVO1_CH, IEDMODEL_VAO_XSWI1_Pos_stVal, IEDMODEL_VAO_XSWI1_Pos_t,
      IEDMODEL_VAO_XSWI1_OpCnt_stVal, IEDMODEL_VAO_XSWI1_OpCnt_t },
    { "Seccionadora 2 (XSWI2)", SERVO2_CH, IEDMODEL_VAO_XSWI2_Pos_stVal, IEDMODEL_VAO_XSWI2_Pos_t,
      IEDMODEL_VAO_XSWI2_OpCnt_stVal, IEDMODEL_VAO_XSWI2_OpCnt_t },
    { "Seccionadora 3 (XSWI3)", SERVO3_CH, IEDMODEL_VAO_XSWI3_Pos_stVal, IEDMODEL_VAO_XSWI3_Pos_t,
      IEDMODEL_VAO_XSWI3_OpCnt_stVal, IEDMODEL_VAO_XSWI3_OpCnt_t },
};

static pthread_mutex_t mtxPedidos = PTHREAD_MUTEX_INITIALIZER;
static int pedidoChave[3];                // 0 = nada; POS_ABERTA ou POS_FECHADA
static int manobras[3];                   // contador de manobras de cada chave

// Posicao dos disjuntores. O trip (thread do GOOSE) e o SCADA (thread do
// servidor) mexem no mesmo disjuntor: este mutex faz LED e posicao mudarem
// sempre juntos, sem um passar no meio do outro.
static pthread_mutex_t mtxDj = PTHREAD_MUTEX_INITIALIZER;
static int posDisjuntor[3] = {POS_ABERTA, POS_ABERTA, POS_ABERTA};

// Estrutura da fita: gpionum 18 faz a lib usar o PWM automaticamente.
static ws2811_t fita = {
    .freq = FITA_FREQ,
    .dmanum = FITA_DMA,
    .channel = {
        [0] = {
            .gpionum = FITA_GPIO,
            .invert = 0,
            .count = FITA_COUNT,
            .strip_type = FITA_TIPO,         // ordem das cores: ajuste la em cima
            .brightness = FITA_BRILHO,
        },
        [1] = { .gpionum = 0, .invert = 0, .count = 0, .brightness = 0 },
    },
};

void sigint_handler(int signalId) { running = 0; }

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

// ----------------------------------------------------------------
// Garante que so existe uma copia deste programa rodando na Pi. Duas
// copias publicariam o GOOSE de posicoes repetido (e a segunda nem
// consegue usar a porta 102). A trava some sozinha quando o programa
// fecha, mesmo se ele cair.
// ----------------------------------------------------------------
static int travarInstancia(const char* nome) {
    char caminho[96];
    snprintf(caminho, sizeof(caminho), "/tmp/%s.lock", nome);
    int fd = open(caminho, O_CREAT | O_RDWR, 0666);
    if (fd < 0) return 1;                         // sem trava, segue assim mesmo
    if (flock(fd, LOCK_EX | LOCK_NB) != 0) return 0;
    return 1;                                     // o arquivo fica aberto ate o fim
}

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
//   circular = true:  a cauda que passa do comeco aparece no fim (a medicao
//                     fica dando voltas);
//   circular = false: o que passa das pontas some (o rastro de um comando
//                     entra por uma ponta e sai pela outra).
static void fitaDesenhaPulso(int pos, uint32_t cor, int cauda, bool circular) {
    for (int i = 0; i < FITA_COUNT; i++) fita.channel[0].leds[i] = 0;

    for (int c = 0; c < cauda; c++) {
        int idx = pos - c;
        if (circular && idx < 0) idx += FITA_COUNT;   // volta ao fim da fita
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

// ----------------------------------------------------------------
// Escreve uma posicao (0 a 3) e o selo de tempo no modelo. Se essa
// posicao esta no dsPos, a escrita dispara o GOOSE de posicoes.
//
// Mesma convencao dos comandos do SCADA neste projeto: 1 = aberto,
// 2 = fechado (valor lido com MmsValue_getBitStringAsInteger).
// Nao usar IedServer_updateDbposValue aqui: ela codifica os bits na
// ordem inversa, e o SCADA passaria a ler "2" (fechado) para aberto.
// ----------------------------------------------------------------
static void escreverPosicao(DataAttribute* stVal, DataAttribute* t, int pos) {
    MmsValue* v = MmsValue_newBitString(2);
    MmsValue_setBitStringFromInteger(v, pos);

    IedServer_lockDataModel(iedServer);
    IedServer_updateAttributeValue(iedServer, stVal, v);
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());
    IedServer_unlockDataModel(iedServer);

    MmsValue_delete(v);
}

// Mesma coisa, sem travar o modelo: usada nos disjuntores, que ja estao
// protegidos pelo mtxDj. (A funcao de atualizar o valor ja se protege
// sozinha por dentro.)
static void escreverPosicaoDj(DataAttribute* stVal, DataAttribute* t, int pos) {
    MmsValue* v = MmsValue_newBitString(2);
    MmsValue_setBitStringFromInteger(v, pos);
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());
    IedServer_updateAttributeValue(iedServer, stVal, v);
    MmsValue_delete(v);
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

            // Rastro da mensagem: atravessa a fita uma vez, do inicio ao fim,
            // ate a cauda inteira sair pela outra ponta
            for (int i = 0; i < FITA_COUNT + CMD_CAUDA - 1 && running; i++) {
                fitaDesenhaPulso(i, cor, CMD_CAUDA, false);
                Thread_sleep(cmdPassoMs);
            }
            LOG_PRINT("[FITA] %s percorreu a fibra.\n",
                      (tipo == RASTRO_TRIP) ? "Trip por GOOSE" : "Comando");

            // Volta ao pulso de medicao de onde ele estava
            continue;
        }

        // Repouso: pulso continuo de medicao
        fitaDesenhaPulso(posMedicao, COR_MEDICAO, MED_CAUDA, true);
        posMedicao = (posMedicao + 1) % FITA_COUNT;
        Thread_sleep(medPassoMs);
    }
    return NULL;
}

// ----------------------------------------------------------------
// Thread do patio: executa as manobras das chaves pedidas por GOOSE.
//
// Durante o movimento a chave fica na posicao intermediaria (0), como
// uma chave real em transito, e isso tambem sai no GOOSE de posicoes.
// Quando o servo termina, a posicao final e publicada: e ela que
// confirma a manobra para o IED de controle.
// ----------------------------------------------------------------
void* patio_thread(void* arg) {
    while (running) {
        for (int n = 0; n < 3; n++) {
            pthread_mutex_lock(&mtxPedidos);
            int alvo = pedidoChave[n];
            pedidoChave[n] = 0;
            pthread_mutex_unlock(&mtxPedidos);

            if (alvo == 0) continue;
            bool fechar = (alvo == POS_FECHADA);

            // Ultima conferencia, aqui no patio: entre o IED de controle
            // liberar e o servo mexer pode passar ate ~1 s (se outras chaves
            // estiverem na fila). Se o disjuntor do vao fechou nesse tempo,
            // a chave nao mexe. O IED de controle vai avisar "sem resposta".
            pthread_mutex_lock(&mtxDj);
            int dj = posDisjuntor[n];
            pthread_mutex_unlock(&mtxDj);
            if (dj != POS_ABERTA) {
                LOG_PRINT("[CHAVE] %s NAO mexeu: o disjuntor %d fechou antes da manobra.\n",
                          chaves[n].nome, n + 1);
                LOG_PRINT("--------------------------------------------------\n");
                continue;
            }

            rastroPendente = RASTRO_COMANDO;                   // a fita mostra a mensagem
            escreverPosicao(chaves[n].stVal, chaves[n].t, POS_INTERMEDIARIA);
            LOG_PRINT("[CHAVE] %s %s...\n", chaves[n].nome, fechar ? "fechando" : "abrindo");

            moverServo(chaves[n].canal, fechar);               // leva ~0,5 s

            escreverPosicao(chaves[n].stVal, chaves[n].t, alvo);
            manobras[n]++;
            IedServer_lockDataModel(iedServer);
            IedServer_updateInt32AttributeValue(iedServer, chaves[n].opCnt, manobras[n]);
            IedServer_updateUTCTimeAttributeValue(iedServer, chaves[n].opCntT, Hal_getTimeInMs());
            IedServer_unlockDataModel(iedServer);

            LOG_PRINT("[CHAVE] %s %s. Posicao publicada por GOOSE (gcbPos).\n",
                      chaves[n].nome, fechar ? "FECHADA" : "ABERTA");
            LOG_PRINT("--------------------------------------------------\n");
        }
        Thread_sleep(10);
    }
    return NULL;
}

// ----------------------------------------------------------------
// Abre o disjuntor comandado pelo trip: LEDs e posicao no modelo.
// A posicao nova sai no GOOSE de posicoes, e o IED de controle fica
// sabendo que o disjuntor abriu (o que libera as chaves desse vao).
// ----------------------------------------------------------------
static void abrirDisjuntorPorTrip(void) {
    pthread_mutex_lock(&mtxDj);
    setLedsDisjuntor(DJ_TRIP_VERDE, DJ_TRIP_VERM, false);
    posDisjuntor[DJ_TRIP_INDICE] = POS_ABERTA;
    escreverPosicaoDj(DJ_TRIP_STVAL, DJ_TRIP_T, POS_ABERTA);
    pthread_mutex_unlock(&mtxDj);
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

// ----------------------------------------------------------------
// Chamada a cada GOOSE de comandos das chaves recebido (inclusive as
// repeticoes).
//
// Cada chave tem dois sinais: abrir (OpOpn) e fechar (OpCls). O IED de
// controle deixa o sinal em "verdadeiro" enquanto espera a chave chegar
// na posicao pedida, e depois volta para "falso". A chave mexe so na
// SUBIDA do sinal (falso -> verdadeiro). As repeticoes trazem os mesmos
// valores e a volta para "falso" nao e subida, entao nenhuma delas faz
// a chave mexer de novo.
//
// A primeira mensagem depois que este programa abre so serve de
// referencia: um comando que ja estava no ar antes disso nao e executado.
// ----------------------------------------------------------------
static bool cmdReferencia = false;        // ja chegou a primeira mensagem?

static void gooseCmdListener(GooseSubscriber sub, void* parameter) {
    uint32_t stNum = GooseSubscriber_getStNum(sub);
    MmsValue* valores = GooseSubscriber_getDataSetValues(sub);
    bool agora[6];
    for (int k = 0; k < 6; k++) {
        MmsValue* v = valores ? MmsValue_getElement(valores, k) : NULL;
        if (v == NULL || MmsValue_getType(v) != MMS_BOOLEAN) {
            if ((int64_t) stNum != ultimoStNumCmd)
                LOG_PRINT("[GOOSE] Comando com formato inesperado (stNum=%u), ignorado.\n", stNum);
            ultimoStNumCmd = stNum;
            return;
        }
        agora[k] = MmsValue_getBoolean(v);
    }
    ultimoStNumCmd = stNum;

    if (!cmdReferencia) {
        cmdReferencia = true;
        memcpy(cmdAnterior, agora, sizeof(agora));
        LOG_PRINT("[GOOSE] Assinatura dos comandos das chaves ativa (stNum=%u).\n", stNum);
        return;
    }

    for (int n = 0; n < 3; n++) {
        bool abrir  = agora[2 * n]     && !cmdAnterior[2 * n];
        bool fechar = agora[2 * n + 1] && !cmdAnterior[2 * n + 1];
        if (!abrir && !fechar) continue;

        if (abrir && fechar) {
            LOG_PRINT("[GOOSE] CSWI%d pediu abrir e fechar ao mesmo tempo (stNum=%u). Ignorado.\n", n + 1, stNum);
            continue;
        }
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[GOOSE] Comando do IED de controle (stNum=%u): %s a %s\n",
                  stNum, abrir ? "ABRIR" : "FECHAR", chaves[n].nome);
        pthread_mutex_lock(&mtxPedidos);
        pedidoChave[n] = abrir ? POS_ABERTA : POS_FECHADA;
        pthread_mutex_unlock(&mtxPedidos);
    }
    memcpy(cmdAnterior, agora, sizeof(agora));
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

// So os disjuntores aceitam comando do supervisorio. As chaves ficam em
// status-only e nem chegam aqui.
static CheckHandlerResult checkHandler(ControlAction action, void* parameter, MmsValue* ctlVal, bool test, bool interlockCheck) {
    if (parameter == IEDMODEL_VAO_XCBR1_Pos ||
        parameter == IEDMODEL_VAO_XCBR2_Pos ||
        parameter == IEDMODEL_VAO_XCBR3_Pos)
        return CONTROL_ACCEPTED;
    return CONTROL_OBJECT_UNDEFINED;
}

static ControlHandlerResult controlHandlerForBinaryOutput(ControlAction action, void* parameter, MmsValue* value, bool test) {
    uint64_t timestamp = Hal_getTimeInMs();
    ClientConnection clientCon = ControlAction_getClientConnection(action);
    const char* clientIP = (clientCon) ? ClientConnection_getPeerAddress(clientCon) : "Desconhecido";

    if (parameter == IEDMODEL_VAO_XCBR1_Pos ||
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

        // A posicao gravada e sempre um ponto duplo valido (1 ou 2),
        // qualquer que seja o formato em que o comando chegou.
        MmsValue* pos = MmsValue_newBitString(2);
        MmsValue_setBitStringFromInteger(pos, state ? POS_FECHADA : POS_ABERTA);

        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[COMANDO] Recebido de: %s\n", clientIP);

        pthread_mutex_lock(&mtxDj);
        if (parameter == IEDMODEL_VAO_XCBR1_Pos) {
            setLedsDisjuntor(LED_D1_VERDE, LED_D1_VERM, state);
            posDisjuntor[0] = state ? POS_FECHADA : POS_ABERTA;
            LOG_PRINT("   >> Acao: XCBR1 (Disjuntor 1) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR1_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR1_Pos_stVal, pos);
        }
        else if (parameter == IEDMODEL_VAO_XCBR2_Pos) {
            setLedsDisjuntor(LED_D2_VERDE, LED_D2_VERM, state);
            posDisjuntor[1] = state ? POS_FECHADA : POS_ABERTA;
            LOG_PRINT("   >> Acao: XCBR2 (Disjuntor 2) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR2_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR2_Pos_stVal, pos);
        }
        else if (parameter == IEDMODEL_VAO_XCBR3_Pos) {
            setLedsDisjuntor(LED_D3_VERDE, LED_D3_VERM, state);
            posDisjuntor[2] = state ? POS_FECHADA : POS_ABERTA;
            LOG_PRINT("   >> Acao: XCBR3 (Disjuntor 3) %s\n", state ? "FECHADO" : "ABERTO");
            IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_VAO_XCBR3_Pos_t, timestamp);
            IedServer_updateAttributeValue(iedServer, IEDMODEL_VAO_XCBR3_Pos_stVal, pos);
        }
        pthread_mutex_unlock(&mtxDj);
        MmsValue_delete(pos);
        LOG_PRINT("   >> Posicao publicada por GOOSE (gcbPos).\n");

        // Qualquer comando do SCADA dispara o rastro ambar na fita
        rastroPendente = RASTRO_COMANDO;

        LOG_PRINT("--------------------------------------------------\n");
    } else {
        return CONTROL_RESULT_FAILED;
    }
    return CONTROL_RESULT_OK;
}

// O supervisorio pode trocar o modelo de controle dos DISJUNTORES.
// O das chaves nao tem este tratamento: fica em status-only.
static MmsDataAccessError writeAccessHandler(DataAttribute* dataAttribute, MmsValue* value, ClientConnection connection, void* parameter) {
    ControlModel ctlModelVal = (ControlModel) MmsValue_toInt32(value);
    if ((ctlModelVal == CONTROL_MODEL_STATUS_ONLY) || (ctlModelVal == CONTROL_MODEL_DIRECT_NORMAL)) {
        if (dataAttribute == IEDMODEL_VAO_XCBR1_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XCBR2_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, ctlModelVal);
        else if (dataAttribute == IEDMODEL_VAO_XCBR3_Pos_ctlModel) IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, ctlModelVal);
        return DATA_ACCESS_ERROR_SUCCESS;
    }
    return DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
}

// Posicao inicial no modelo, antes de o servidor abrir. Assim o primeiro
// GOOSE de posicoes ja diz a verdade (sem isso, tudo comecaria em 0,
// "em movimento", e o intertravamento bloquearia as chaves).
static void posicaoInicial(DataAttribute* stVal, DataAttribute* t, int pos) {
    MmsValue* v = MmsValue_newBitString(2);
    MmsValue_setBitStringFromInteger(v, pos);
    IedServer_updateAttributeValue(iedServer, stVal, v);
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());
    MmsValue_delete(v);
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    if (!travarInstancia("empelas_ctrl")) {
        LOG_PRINT("ERRO: o empelas_ctrl ja esta rodando nesta Pi. Feche o outro (Ctrl+C no terminal dele)\n"
                  "      ou procure com:  ps aux | grep empelas_ctrl\n");
        exit(1);
    }

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
        fitaOk = true;
        fitaApaga();
        LOG_PRINT("[FITA] Inicializada em GPIO%d (PWM), %d pixels.\n", FITA_GPIO, FITA_COUNT);
        LOG_PRINT("[FITA] Pulso de medicao continuo ativo.\n");
    }

    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    int tcpPort = 102;
    if (argc > 1) tcpPort = atoi(argv[1]);

    // O modelo comeca igual a maquete: chaves fechadas, disjuntores abertos
    posicaoInicial(IEDMODEL_VAO_XSWI1_Pos_stVal, IEDMODEL_VAO_XSWI1_Pos_t, POS_FECHADA);
    posicaoInicial(IEDMODEL_VAO_XSWI2_Pos_stVal, IEDMODEL_VAO_XSWI2_Pos_t, POS_FECHADA);
    posicaoInicial(IEDMODEL_VAO_XSWI3_Pos_stVal, IEDMODEL_VAO_XSWI3_Pos_t, POS_FECHADA);
    posicaoInicial(IEDMODEL_VAO_XCBR1_Pos_stVal, IEDMODEL_VAO_XCBR1_Pos_t, POS_ABERTA);
    posicaoInicial(IEDMODEL_VAO_XCBR2_Pos_stVal, IEDMODEL_VAO_XCBR2_Pos_t, POS_ABERTA);
    posicaoInicial(IEDMODEL_VAO_XCBR3_Pos_stVal, IEDMODEL_VAO_XCBR3_Pos_t, POS_ABERTA);

    // Chaves: so mostram a posicao. O comando vem por GOOSE do IED de controle.
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI1_Pos, CONTROL_MODEL_STATUS_ONLY);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI2_Pos, CONTROL_MODEL_STATUS_ONLY);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XSWI3_Pos, CONTROL_MODEL_STATUS_ONLY);

    // Disjuntores: comando direto do supervisorio, como antes
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, CONTROL_MODEL_DIRECT_NORMAL);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, CONTROL_MODEL_DIRECT_NORMAL);

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

    // Agora este IED tambem PUBLICA GOOSE (as posicoes), entao a
    // publicacao sai pelo cabo, como a recepcao.
    IedServer_setGooseInterfaceId(iedServer, GOOSE_INTERFACE);
    IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        if (fitaOk) ws2811_fini(&fita);
        exit(-1);
    }

    // Habilita a publicacao do GOOSE de posicoes (gcbPos)
    IedServer_enableGoosePublishing(iedServer);

    // Assinaturas: trip e comandos das chaves, os dois vindos do EmpElas_PROT
    gooseReceiver = GooseReceiver_create();
    GooseReceiver_setInterfaceId(gooseReceiver, GOOSE_INTERFACE);

    GooseSubscriber subTrip = GooseSubscriber_create(GOOSE_TRIP_REF, NULL);
    GooseSubscriber_setDstMac(subTrip, GOOSE_TRIP_DSTMAC);
    GooseSubscriber_setAppId(subTrip, GOOSE_TRIP_APPID);
    GooseSubscriber_setListener(subTrip, gooseTripListener, NULL);
    GooseReceiver_addSubscriber(gooseReceiver, subTrip);

    GooseSubscriber subCmd = GooseSubscriber_create(GOOSE_CMD_REF, NULL);
    GooseSubscriber_setDstMac(subCmd, GOOSE_CMD_DSTMAC);
    GooseSubscriber_setAppId(subCmd, GOOSE_CMD_APPID);
    GooseSubscriber_setListener(subCmd, gooseCmdListener, NULL);
    GooseReceiver_addSubscriber(gooseReceiver, subCmd);

    GooseReceiver_start(gooseReceiver);

    LOG_PRINT("\n--- EmpElas_CTRL : PATIO (disjuntores, chaves e fita) ---\n");
    LOG_PRINT("[GOOSE] Publicando gcbPos em %s (APPID 0x1002): posicao dos 3 disjuntores e das 3 chaves.\n",
              GOOSE_INTERFACE);
    if (GooseReceiver_isRunning(gooseReceiver)) {
        LOG_PRINT("[GOOSE] Escutando o trip em %s (APPID 0x%04X). Abre: %s.\n",
                  GOOSE_INTERFACE, GOOSE_TRIP_APPID, DJ_TRIP_NOME);
        LOG_PRINT("[GOOSE] Escutando os comandos das chaves em %s (APPID 0x%04X).\n",
                  GOOSE_INTERFACE, GOOSE_CMD_APPID);
    }
    else
        LOG_PRINT("[GOOSE] ERRO: receptor nao iniciou. Confira se %s existe e se rodou com sudo.\n",
                  GOOSE_INTERFACE);
    LOG_PRINT("[STATUS] Servos: canais %d, %d e %d do PCA9685 | LEDs D1-D3 | Fita GPIO%d (%d px)\n", SERVO1_CH, SERVO2_CH, SERVO3_CH, FITA_GPIO, FITA_COUNT);
    LOG_PRINT("[STATUS] Chaves fechadas, disjuntores abertos. Chaves so por GOOSE; disjuntores pelo SCADA.\n");
    LOG_PRINT("[STATUS] Rodando na porta %d.\n", tcpPort);

    running = 1;
    if (fitaOk) {
        Thread fitaThread = Thread_create((ThreadExecutionFunction)fita_thread, NULL, true);
        Thread_start(fitaThread);
    }
    Thread patioThread = Thread_create((ThreadExecutionFunction)patio_thread, NULL, false);
    Thread_start(patioThread);

    while (running) {
        Thread_sleep(100);
    }

    LOG_PRINT("\n[SISTEMA] Encerrando...\n");
    if (gooseReceiver) {
        GooseReceiver_stop(gooseReceiver);
        GooseReceiver_destroy(gooseReceiver);   // destroi tambem os assinantes
    }
    Thread_destroy(patioThread);                // espera a manobra em curso terminar
    IedServer_disableGoosePublishing(iedServer);
    if (pcaFd >= 0) {
        pcaSetPwm(pcaFd, SERVO1_CH, 0, PCA_FULL_OFF);
        pcaSetPwm(pcaFd, SERVO2_CH, 0, PCA_FULL_OFF);
        pcaSetPwm(pcaFd, SERVO3_CH, 0, PCA_FULL_OFF);
    }
    digitalWrite(LED_D1_VERDE, LOW); digitalWrite(LED_D1_VERM, LOW);
    digitalWrite(LED_D2_VERDE, LOW); digitalWrite(LED_D2_VERM, LOW);
    digitalWrite(LED_D3_VERDE, LOW); digitalWrite(LED_D3_VERM, LOW);
    Thread_sleep(300);                          // a fita termina o quadro em curso
    if (fitaOk) {
        fitaApaga();
        ws2811_fini(&fita);
    }

    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    if (dev_null != -1) close(dev_null);
    return 0;
}
