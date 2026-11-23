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
 *   - assina gcbCmd: os comandos de abrir e fechar as chaves (CSWI1-3) e os
 *     disjuntores (CSWI4-6), OpOpn e OpCls. So chegam aqui comandos que o
 *     intertravamento ja liberou.
 *
 * Nem as chaves nem os disjuntores aceitam comando direto do supervisorio:
 * o Pos de todos fica em status-only. Todo comando passa pelo IED de
 * controle (CSWI), como pede a norma, senao daria para passar por cima do
 * intertravamento. So o trip da protecao chega direto no disjuntor 1.
 *
 * Posicoes (Dbpos) no formato da norma, escritas com IedServer_updateDbposValue:
 * 01 = aberto (off), 10 = fechado (on), 00 = em movimento.
 *
 * FITA DA FIBRA OPTICA (WS2811, 12 V)
 * Mostra a comunicacao do mesmo jeito que o simulador:
 *   - a fita inteira fica roxa, bem fraquinha (a fibra);
 *   - bolinhas brancas e fortes andam o tempo todo: o SV, as medidas da MU,
 *     que nunca param;
 *   - bolinhas amarelas: GOOSE (comandos das chaves e dos disjuntores e o
 *     trip retirado, vindos do EmpElas_PROT, e as repeticoes do GOOSE de
 *     tempos em tempos);
 *   - onda vermelha que toma a fita: o TRIP.
 *
 * Mais duas fitas (pinos fisicos 33 e 19) representam os cabos de COBRE e
 * mostram em laranja as medidas (do TC/TP para a MU) e os comandos (da MU
 * para o equipamento); ver FITAS 2 E 3.
 *
 * Fita atual: 5 m, 300 LEDs (60 por metro), 12 V. Cada chip WS2811 comanda
 * um grupo de 3 LEDs, entao sao 100 "pixels". Comprimento e ordem das
 * cores ficam em FITA_COUNT e FITA_TIPO; o programa testes/teste_fita
 * ajuda a descobrir os dois.
 *
 * Dado no GPIO12 (fisico 32, PWM), DIRETO no GPIO (o level shifter que
 * foi testado era lento para 800kHz e deixava a fita sempre acesa). Os
 * pinos fisicos 40 (PCM) e 12 (GPIO18) ja foram usados antes e deram
 * problema. O GPIO12 usa o mesmo PWM da Pi, que ficou livre quando os servos
 * foram para o PCA9685, e tem GND do lado (fisicos 30 e 34). O audio
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
#include <sys/timex.h>     // adjtimex: o relogio esta sincronizado?
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

// Movimento suave das chaves: o pulso muda aos poucos, um quadro do PWM
// (20 ms) por vez, em vez de pular direto para a posicao final. A chave
// comeca devagar, acelera no meio e freia no fim.
// AJUSTE: SERVO_TEMPO_MS e o tempo de cada manobra. O movimento inteiro
// (SERVO_TEMPO_MS + SERVO_FIRME_MS) precisa ficar abaixo do CMD_TIMEOUT_MS
// da Pi das telinhas (3 s), senao ela desiste de esperar a confirmacao.
#define SERVO_TEMPO_ABRIR_MS   1500   // duracao para ABRIR a chave
#define SERVO_TEMPO_FECHAR_MS  1500   // duracao para FECHAR a chave (AJUSTE aqui)
#define SERVO_PASSO_MS     20   // um quadro do PWM de 50 Hz
#define SERVO_FIRME_MS    200   // segura na posicao final antes de cortar o pulso
#if (SERVO_TEMPO_ABRIR_MS + SERVO_FIRME_MS) > 2500 || (SERVO_TEMPO_FECHAR_MS + SERVO_FIRME_MS) > 2500
#warning "Manobra das chaves muito lenta: a Pi das telinhas espera no maximo 3 s (CMD_TIMEOUT_MS)"
#endif

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
//              (por GOOSE, para um disjuntor ou uma chave).
//              Representa a mensagem de manobra, que e episodica. Ele
//              interrompe o pulso de medicao, que retoma de onde parou -
//              assim como uma mensagem de manobra tem prioridade sobre o
//              trafego continuo.
//
// Esta e a fita do pino fisico 32. As fitas 2 e 3 (cobre, laranja) ficam
// mais abaixo. Se um pedaco for emendado em outro (saida de dados de um na
// entrada do outro, setas no mesmo sentido), para a Pi vira uma fita so.
#define FITA_GPIO       12        // GPIO12 = Fisico 32 (PWM) - fita da fibra optica
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
#define FITA_TIPO       WS2811_STRIP_BRG
#define FITA_FREQ       WS2811_TARGET_FREQ  // 800kHz
#define FITA_BRILHO     128       // 0-255 (metade p/ reduzir corrente)

// Cores no formato 0x00RRGGBB, as mesmas do simulador (gemeo/simulador).
#define COR_FIBRA       0x008000FF  // roxo - a fibra (fundo, sempre aceso, bem fraco)
#define COR_SV          0x00FFFFFF  // branco - SV (contrasta com o roxo fraco do fundo)
#define COR_GOOSE       0x00FF8C00  // amarelo - GOOSE (no simulador #ffc531; aqui com menos verde, senao a fita mostra verde-limao)
#define COR_MMS         0x002BFF5C  // verde - MMS (sem uso hoje: o MMS nao passa pelo patio)
#define COR_TRIP        0x00FF0000  // vermelho - trip

// AJUSTES DA ANIMACAO
#define FUNDO_PCT          12     // brilho do roxo de fundo (0 a 100). Fraco para o SV se destacar
#define SV_VOLTA_MS        20000  // tempo de uma bolinha de SV atravessar a fita (maior = mais devagar)
#define SV_ESPACO          15     // distancia entre duas bolinhas de SV, em pixels
#define SV_PCT             100    // brilho das bolinhas de SV (as mensagens ficam em 100%)
#define SV_CAUDA           1      // SV: bolinha pequena, 1 pixel + 1 de cauda
#define MSG_VOLTA_MS       4000   // tempo de uma bolinha de GOOSE ou MMS atravessar a fita
#define MSG_RAJADA         3      // bolinhas por mensagem nova (comando, trip retirado...)
#define MSG_INTERVALO_MS   400    // espaco de tempo entre as bolinhas de uma rajada
#define MSG_TAMANHO        2      // GOOSE/MMS: bolinha maior, 2 pixels acesos...
#define MSG_CAUDA          3      // ...e 3 de cauda
#define SV_VOLTA_APOS_MS   800    // enquanto passa uma rajada o SV some; depois volta aos poucos
#define GOOSE_REPETE_MS    6000   // repeticoes do GOOSE: no maximo 1 bolinha amarela a cada 6 s
#define TRIP_ONDA_MS       500    // tempo da onda vermelha atravessar a fita
#define TRIP_FICA_MS       2000   // tempo que a fita fica toda vermelha
#define TRIP_SOME_MS       600    // tempo para voltar ao roxo
#define FITA_QUADRO_MS     20     // um quadro a cada 20 ms (50 por segundo)

// ================= FITAS 2 E 3 (cabos de cobre, laranja) ==================
// Mais dois pedacos de fita, cada um no seu pino, mostrando a MESMA coisa:
// laranja fraco de fundo, bolinhas das medidas andando para a MU e uma rajada
// para o equipamento quando um disjuntor ou chave opera (comando ou trip).
//
//   Fita 2: GPIO13 = Fisico 33. Segundo canal do PWM, junto com a fibra
//           (a lib manda os dois canais na mesma transmissao).
//   Fita 3: GPIO10 = Fisico 19. Sai pelo SPI, porque a Pi so tem dois
//           canais de PWM. Precisa do SPI ligado e de core_freq=250 no
//           /boot/config.txt (na Pi 3, sem isso o SPI erra o tempo do sinal).
//
// Para desligar uma delas, ponha o COUNT em 0.
#define FITA2_GPIO      13        // GPIO13 = Fisico 33 (PWM, canal 1)
#define FITA2_COUNT     100       // AJUSTE: pixels da fita 2 (teste_fita 100 33)
#define FITA2_TIPO      WS2811_STRIP_BRG
#define FITA3_GPIO      10        // GPIO10 = Fisico 19 (SPI)
#define FITA3_COUNT     100       // AJUSTE: pixels da fita 3 (teste_fita 100 19)
#define FITA3_TIPO      WS2811_STRIP_BRG
#define COR_FITAS23     0x00FF4A10  // cobre (laranja) - fitas dos pinos 33 e 19
// Intensidade do cobre, de 0 a 100 (%). Com a fita toda acesa ela puxa bem
// mais corrente que o rastro antigo: se a fonte de 12 V esquentar ou a cor
// mudar no fim da fita, diminua aqui (por exemplo, 50).
#define COBRE_PCT       100
// Cobre com movimento, como no gemeo:
//  - medidas: bolinhas laranja o tempo todo, do TC/TP para a MU;
//  - comando: quando um disjuntor ou chave opera, uma rajada vai da MU para
//    o equipamento e as medidas saem da frente enquanto ela passa.
#define COBRE_FUNDO_PCT    20     // brilho do laranja de fundo (0 a 100)
#define COBRE_MED_VOLTA_MS 20000  // tempo de uma bolinha de medida atravessar a fita
#define COBRE_MED_ESPACO   15     // distancia entre as bolinhas de medida, em pixels
// Sentido das MEDIDAS na fita (os comandos vao sempre ao contrario):
//  -1 = andam para o comeco da fita (onde entra o fio de dados, o DIN)
//   1 = andam para o fim da fita
// Se as medidas estiverem andando para LONGE da MU, troque o sinal.
#define COBRE2_SENTIDO_MED  -1    // fita 2 (pino 33)
#define COBRE3_SENTIDO_MED  -1    // fita 3 (pino 19)

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

// Qual disjuntor o trip abre. Para trocar, mude as seis linhas juntas.
#define DJ_TRIP_INDICE    0                       // 0 = disjuntor 1
#define DJ_TRIP_NOME      "Disjuntor 1 (XCBR1)"
#define DJ_TRIP_VERDE     LED_D1_VERDE
#define DJ_TRIP_VERM      LED_D1_VERM
#define DJ_TRIP_STVAL     IEDMODEL_VAO_XCBR1_Pos_stVal
#define DJ_TRIP_T         IEDMODEL_VAO_XCBR1_Pos_t
#define DJ_TRIP_OBJ       IEDMODEL_VAO_XCBR1_Pos

// Depois do trip, a chave 1 abre sozinha para isolar o trecho da falta.
// NAO e o convencional: numa subestacao de verdade quem abre a seccionadora
// e o operador, depois que o disjuntor ja cortou a corrente. Aqui e
// automatico para a demonstracao ficar completa so com o botao da falta.
// Para voltar ao jeito convencional, troque 1 por 0.
#define CHAVE_AUTO_NA_FALTA   1
#define CHAVE_AUTO_ATRASO_MS  2000    // espera depois do DJ1 abrir (para dar tempo de ver)

// Posicao de ponto duplo (Dbpos), com os mesmos numeros da biblioteca:
// 0 = em movimento, 1 = aberto (DBPOS_OFF), 2 = fechado (DBPOS_ON),
// 3 = invalido. Na rede vai no formato da norma (01 = aberto, 10 = fechado).
#define POS_INTERMEDIARIA 0
#define POS_ABERTA        1
#define POS_FECHADA       2

// ==============================================================

#include "static_model.h"

static volatile int running = 0;
static IedServer iedServer = NULL;
static int activeConnections = 0;
static GooseReceiver gooseReceiver = NULL;
static int64_t ultimoStNum = -1;          // ultimo estado do GOOSE de trip ja tratado
// Trip ainda ativo (a falta continua na linha). Enquanto isso, o disjuntor
// do trip nao fecha: fecharia sobre a falta. Numa subestacao real, quem faz
// esse bloqueio e o rele de bloqueio (86) ou o proprio trip mantido.
static volatile bool tripAtivo = false;
static int64_t ultimoStNumCmd = -1;       // stNum do ultimo GOOSE de comandos (so para o log)
#define N_CMD 12                          // 6 equipamentos x (abrir, fechar)
static bool cmdAnterior[N_CMD];           // valores do ultimo GOOSE de comandos
static int pcaFd = -1;                    // descritor I2C do PCA9685
static bool fitaOk = false;               // a fita so e usada se iniciou bem
static bool fita3Ok = false;              // fita 3 (SPI), idem

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
static int posChave[3] = {POS_FECHADA, POS_FECHADA, POS_FECHADA};   // posicao atual de cada chave
static volatile uint64_t chaveAutoEm = 0; // quando abrir a chave 1 sozinha (0 = nada marcado)

// Posicao dos disjuntores. O trip e os comandos (GOOSE) e a thread do patio
// mexem nos disjuntores: este mutex faz LED e posicao mudarem sempre
// juntos, sem um passar no meio do outro.
static pthread_mutex_t mtxDj = PTHREAD_MUTEX_INITIALIZER;
static int posDisjuntor[3] = {POS_ABERTA, POS_ABERTA, POS_ABERTA};

// Estrutura da fita: gpionum 12 faz a lib usar o PWM automaticamente.
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
        [1] = {                              // fita 2 (cobre), PWM canal 1
            .gpionum = FITA2_COUNT > 0 ? FITA2_GPIO : 0,
            .invert = 0,
            .count = FITA2_COUNT,
            .strip_type = FITA2_TIPO,
            .brightness = FITA_BRILHO,
        },
    },
};

// Fita 3 (cobre): gpionum 10 faz a lib usar o SPI. Nao usa DMA.
static ws2811_t fita3 = {
    .freq = FITA_FREQ,
    .dmanum = FITA_DMA,
    .channel = {
        [0] = {
            .gpionum = FITA3_GPIO,
            .invert = 0,
            .count = FITA3_COUNT,
            .strip_type = FITA3_TIPO,
            .brightness = FITA_BRILHO,
        },
        [1] = { .gpionum = 0, .invert = 0, .count = 0, .brightness = 0 },
    },
};

void sigint_handler(int signalId) { running = 0; }

#define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

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

// Apaga as tres fitas
static void fitaApaga(void) {
    if (fitaOk) {
        for (int i = 0; i < FITA_COUNT; i++) fita.channel[0].leds[i] = 0;
        for (int i = 0; i < FITA2_COUNT; i++) fita.channel[1].leds[i] = 0;
        ws2811_render(&fita);
    }
    if (fita3Ok) {
        for (int i = 0; i < FITA3_COUNT; i++) fita3.channel[0].leds[i] = 0;
        ws2811_render(&fita3);
    }
}

// Escurece uma cor por um fator de 0 a 100 por cento.
static uint32_t corAtenuada(uint32_t cor, int pct) {
    uint8_t r = ((cor >> 16) & 0xFF) * pct / 100;
    uint8_t g = ((cor >>  8) & 0xFF) * pct / 100;
    uint8_t b = ( cor        & 0xFF) * pct / 100;
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// Mistura duas cores: pct = quanto da cor nova entra (0 a 100).
static uint32_t corMistura(uint32_t base, uint32_t nova, int pct) {
    if (pct <= 0) return base;
    if (pct >= 100) return nova;
    uint32_t r = (((base >> 16) & 0xFF) * (100 - pct) + ((nova >> 16) & 0xFF) * pct) / 100;
    uint32_t g = (((base >>  8) & 0xFF) * (100 - pct) + ((nova >>  8) & 0xFF) * pct) / 100;
    uint32_t b = (( base        & 0xFF) * (100 - pct) + ( nova        & 0xFF) * pct) / 100;
    return (r << 16) | (g << 8) | b;
}

// Pinta a fita inteira de uma cor so (fundo da fibra, cobre parado).
static void corInteira(ws2811_led_t* leds, int n, uint32_t cor) {
    for (int i = 0; i < n; i++) leds[i] = cor;
}

// Uma bolinha: 'tamanho' pixels fortes na frente e uma cauda que vai
// sumindo no fundo. pct = brilho da bolinha (0 a 100).
// sentido = +1: anda para o fim da fita (do IED para a MU), cauda atras;
// sentido = -1: anda para o comeco da fita (da MU para o IED).
static void desenhaBolinha(ws2811_led_t* leds, int n, int cabeca, uint32_t cor,
                           int tamanho, int cauda, int pct, int sentido) {
    for (int c = 0; c < tamanho + cauda; c++) {
        int i = cabeca - sentido * c;
        if (i < 0 || i >= n) continue;
        int k = (c < tamanho) ? 100 : 100 - (c - tamanho + 1) * 100 / (cauda + 1);
        leds[i] = corMistura(leds[i], cor, k * pct / 100);
    }
}

// ----------------------------------------------------------------
// Mensagens na fibra. As threads do GOOSE e do servidor so pedem as
// bolinhas aqui; quem desenha e a thread da fita.
// ----------------------------------------------------------------
#define MAX_BOLINHAS 32
// discreta = bolinha avulsa (repeticao do GOOSE): nao esconde o SV
typedef struct { uint64_t inicio; uint32_t cor; bool viva; bool discreta; } Bolinha;
static Bolinha bolinhas[MAX_BOLINHAS];
static uint64_t tripInicio = 0;            // 0 = sem onda de trip
static uint64_t ultimaRepeticao = 0;       // ultima bolinha de repeticao do GOOSE
static pthread_mutex_t mtxFita = PTHREAD_MUTEX_INITIALIZER;

// Solta 'quantas' bolinhas de uma cor, uma atras da outra
static void fitaSolta(uint32_t cor, int quantas, bool discreta) {
    uint64_t agora = Hal_getTimeInMs();
    pthread_mutex_lock(&mtxFita);
    for (int q = 0; q < quantas; q++) {
        for (int i = 0; i < MAX_BOLINHAS; i++) {
            if (!bolinhas[i].viva) {
                bolinhas[i].viva = true;
                bolinhas[i].cor = cor;
                bolinhas[i].inicio = agora + (uint64_t) q * MSG_INTERVALO_MS;
                bolinhas[i].discreta = discreta;
                break;
            }
        }
    }
    pthread_mutex_unlock(&mtxFita);
}

// Mensagem de verdade (comando, trip retirado...): o SV sai da frente
static void fitaMensagem(uint32_t cor, int quantas) { fitaSolta(cor, quantas, false); }

// Repeticao do GOOSE (o "continuo aqui"): uma bolinha amarela avulsa, sem exagero
static void fitaRepeticaoGoose(void) {
    uint64_t agora = Hal_getTimeInMs();
    if (agora - ultimaRepeticao < GOOSE_REPETE_MS) return;
    ultimaRepeticao = agora;
    fitaSolta(COR_GOOSE, 1, true);
}

// Um disjuntor ou chave vai operar: rajada no cobre, da MU para o equipamento
static uint64_t cobreCmdInicio = 0;
static void fitaCobreComando(void) {
    pthread_mutex_lock(&mtxFita);
    cobreCmdInicio = Hal_getTimeInMs();
    pthread_mutex_unlock(&mtxFita);
}

static void fitaTrip(void) {
    pthread_mutex_lock(&mtxFita);
    tripInicio = Hal_getTimeInMs();
    pthread_mutex_unlock(&mtxFita);
}

// Monta o quadro da fibra para o instante 'agora'
static void fitaQuadroFibra(ws2811_led_t* leds, int n, uint64_t agora) {
    static uint64_t ultimaRajada = 0;      // ultimo quadro com rajada na fita
    corInteira(leds, n, corAtenuada(COR_FIBRA, FUNDO_PCT));

    // Copia as bolinhas vivas (GOOSE e MMS) e ve se tem rajada passando
    struct { int pos; uint32_t cor; } vis[MAX_BOLINHAS];
    int nv = 0;
    pthread_mutex_lock(&mtxFita);
    for (int i = 0; i < MAX_BOLINHAS; i++) {
        if (!bolinhas[i].viva) continue;
        if (!bolinhas[i].discreta) ultimaRajada = agora;   // inclui as que ainda vao entrar
        if (agora < bolinhas[i].inicio) continue;
        int pos = (int) ((agora - bolinhas[i].inicio) * (uint64_t) n / MSG_VOLTA_MS);
        if (pos - (MSG_TAMANHO + MSG_CAUDA) >= n) { bolinhas[i].viva = false; continue; }
        vis[nv].pos = pos; vis[nv].cor = bolinhas[i].cor; nv++;
    }
    uint64_t tr = tripInicio;
    pthread_mutex_unlock(&mtxFita);

    // SV: trem de bolinhas pequenas e mais fracas que nunca para. Enquanto
    // passa uma rajada (comando), ele sai da frente para nao misturar as cores.
    int svPct = SV_PCT;
    if (ultimaRajada != 0) {
        uint64_t desde = agora - ultimaRajada;
        svPct = (desde >= SV_VOLTA_APOS_MS) ? SV_PCT : (int) (SV_PCT * desde / SV_VOLTA_APOS_MS);
    }
    if (svPct > 0) {
        int desloc = (int) ((agora * (uint64_t) n / SV_VOLTA_MS) % SV_ESPACO);
        // O SV sai da MU e vai para o IED (PROT): anda no sentido contrario das
        // mensagens, por isso a posicao e espelhada (n - 1 - cab).
        for (int cab = desloc; cab < n + SV_CAUDA + 1; cab += SV_ESPACO)
            desenhaBolinha(leds, n, n - 1 - cab, COR_SV, 1, SV_CAUDA, svPct, -1);
    }

    // GOOSE e MMS por cima, maiores e mais fortes
    for (int k = 0; k < nv; k++)
        desenhaBolinha(leds, n, vis[k].pos, vis[k].cor, MSG_TAMANHO, MSG_CAUDA, 100, 1);

    // Trip: onda vermelha, fica um tempo e volta ao roxo
    if (tr == 0 || agora < tr) return;
    uint64_t t = agora - tr;
    if (t < TRIP_ONDA_MS) {
        int frente = (int) (t * (uint64_t) n / TRIP_ONDA_MS);
        for (int i = 0; i <= frente && i < n; i++) leds[i] = COR_TRIP;
    } else if (t < TRIP_ONDA_MS + TRIP_FICA_MS) {
        corInteira(leds, n, COR_TRIP);
    } else if (t < TRIP_ONDA_MS + TRIP_FICA_MS + TRIP_SOME_MS) {
        int pct = 100 - (int) ((t - TRIP_ONDA_MS - TRIP_FICA_MS) * 100 / TRIP_SOME_MS);
        for (int i = 0; i < n; i++) leds[i] = corMistura(leds[i], COR_TRIP, pct);
    } else {
        pthread_mutex_lock(&mtxFita);
        if (tripInicio == tr) tripInicio = 0;
        pthread_mutex_unlock(&mtxFita);
    }
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

// Ultimo pulso mandado a cada canal (0 = posicao desconhecida)
static int servoTick[16];

// Move um servo devagar ate a posicao e corta o pulso em seguida. Sem o
// corte, o servo fica tremendo e zumbindo enquanto estiver sob comando.
// Na primeira vez (ao ligar), a posicao de partida e desconhecida: ai o
// servo vai direto, como antes.
static void moverServo(int canal, bool fechar) {
    if (pcaFd < 0) return;
    int alvo = fechar ? TICK_FECHADO : TICK_ABERTO;
    int inicio = servoTick[canal];

    if (inicio > 0 && inicio != alvo) {
        int tempo = fechar ? SERVO_TEMPO_FECHAR_MS : SERVO_TEMPO_ABRIR_MS;
        int passos = tempo / SERVO_PASSO_MS;
        if (passos < 1) passos = 1;
        for (int i = 1; i <= passos; i++) {
            double t = (double) i / passos;
            double s = t * t * (3.0 - 2.0 * t);        // suave no comeco e no fim
            double tick = inicio + (alvo - inicio) * s;
            pcaSetPwm(pcaFd, canal, 0, (int) (tick + 0.5));
            delay(SERVO_PASSO_MS);
        }
        delay(SERVO_FIRME_MS);
    } else {
        pcaSetPwm(pcaFd, canal, 0, alvo);
        delay(500);
    }
    servoTick[canal] = alvo;
    pcaSetPwm(pcaFd, canal, 0, PCA_FULL_OFF);
}

static void setLedsDisjuntor(int pinVerde, int pinVerm, bool fechado) {
    digitalWrite(pinVerde, fechado ? HIGH : LOW);
    digitalWrite(pinVerm,  fechado ? LOW  : HIGH);
}

// ----------------------------------------------------------------
// Escreve uma posicao (0 a 3) e o selo de tempo no modelo. Se essa
// posicao esta no dsPos, a escrita dispara o GOOSE de posicoes.
// IedServer_updateDbposValue grava no formato da norma (01 = aberto,
// 10 = fechado), que e o que o Elipse, a MU e a PROT leem.
// ----------------------------------------------------------------
static void escreverPosicao(DataAttribute* stVal, DataAttribute* t, int pos) {
    IedServer_lockDataModel(iedServer);
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());   // horario antes do valor
    IedServer_updateDbposValue(iedServer, stVal, (Dbpos) pos);
    IedServer_unlockDataModel(iedServer);
}

// Mesma coisa, sem travar o modelo: usada nos disjuntores, que ja estao
// protegidos pelo mtxDj. (A funcao de atualizar o valor ja se protege
// sozinha por dentro.)
static void escreverPosicaoDj(DataAttribute* stVal, DataAttribute* t, int pos) {
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());
    IedServer_updateDbposValue(iedServer, stVal, (Dbpos) pos);
}

// Monta o quadro de uma fita de cobre. 'sent' = sentido das medidas.
static void fitaQuadroCobre(ws2811_led_t* leds, int n, uint64_t agora, int sent) {
    corInteira(leds, n, corAtenuada(COR_FITAS23, COBRE_FUNDO_PCT * COBRE_PCT / 100));
    pthread_mutex_lock(&mtxFita);
    uint64_t ci = cobreCmdInicio;
    pthread_mutex_unlock(&mtxFita);

    // Comando: MSG_RAJADA bolinhas maiores, no sentido contrario ao das medidas
    uint64_t duracao = MSG_VOLTA_MS + (uint64_t) MSG_RAJADA * MSG_INTERVALO_MS + 300;
    bool rajada = ci != 0 && agora >= ci && agora - ci < duracao;
    int medPct = COBRE_PCT;
    if (ci != 0 && agora >= ci) {
        uint64_t desde = agora - ci;
        if (desde < duracao) medPct = 0;
        else if (desde < duracao + SV_VOLTA_APOS_MS) medPct = (int) (COBRE_PCT * (desde - duracao) / SV_VOLTA_APOS_MS);
    }

    // Medidas (TC/TP -> MU)
    if (medPct > 0) {
        int desloc = (int) ((agora * (uint64_t) n / COBRE_MED_VOLTA_MS) % COBRE_MED_ESPACO);
        for (int cab = desloc; cab < n + 2; cab += COBRE_MED_ESPACO) {
            int pos = (sent > 0) ? cab : n - 1 - cab;
            desenhaBolinha(leds, n, pos, COR_FITAS23, 1, 1, medPct, sent);
        }
    }
    // Comando (MU -> equipamento)
    if (rajada) {
        for (int q = 0; q < MSG_RAJADA; q++) {
            uint64_t t0 = ci + (uint64_t) q * MSG_INTERVALO_MS;
            if (agora < t0) continue;
            int p = (int) ((agora - t0) * (uint64_t) n / MSG_VOLTA_MS);
            if (p - (MSG_TAMANHO + MSG_CAUDA) >= n) continue;
            int pos = (sent > 0) ? n - 1 - p : p;
            desenhaBolinha(leds, n, pos, COR_FITAS23, MSG_TAMANHO, MSG_CAUDA, COBRE_PCT, -sent);
        }
    }
}

// Thread da fita: desenha um quadro a cada FITA_QUADRO_MS. A fibra e
// calculada pelo relogio, entao as bolinhas andam sempre no mesmo ritmo.
// As fitas de cobre tambem tem movimento, entao sao redesenhadas a cada quadro.
void* fita_thread(void* arg) {
    while (running) {
        uint64_t agora = Hal_getTimeInMs();
        if (fitaOk) {
            fitaQuadroFibra(fita.channel[0].leds, FITA_COUNT, agora);
            if (FITA2_COUNT > 0) fitaQuadroCobre(fita.channel[1].leds, FITA2_COUNT, agora, COBRE2_SENTIDO_MED);
            ws2811_render(&fita);
        }
        if (fita3Ok) {
            fitaQuadroCobre(fita3.channel[0].leds, FITA3_COUNT, agora, COBRE3_SENTIDO_MED);
            ws2811_render(&fita3);
        }
        Thread_sleep(FITA_QUADRO_MS);
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
        // Abertura automatica da chave 1 depois do trip (ver CHAVE_AUTO_NA_FALTA)
        if (chaveAutoEm != 0 && Hal_getTimeInMs() >= chaveAutoEm) {
            chaveAutoEm = 0;
            pthread_mutex_lock(&mtxDj);
            int dj = posDisjuntor[DJ_TRIP_INDICE];
            pthread_mutex_unlock(&mtxDj);
            if (dj == POS_ABERTA && posChave[DJ_TRIP_INDICE] == POS_FECHADA) {
                LOG_PRINT("--------------------------------------------------\n");
                LOG_PRINT("[AUTO] Falta isolada pelo %s: abrindo a %s sozinha\n", DJ_TRIP_NOME, chaves[DJ_TRIP_INDICE].nome);
                LOG_PRINT("       (so na maquete; no real quem abre e o operador).\n");
                pthread_mutex_lock(&mtxPedidos);
                pedidoChave[DJ_TRIP_INDICE] = POS_ABERTA;
                pthread_mutex_unlock(&mtxPedidos);
            }
        }
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

            escreverPosicao(chaves[n].stVal, chaves[n].t, POS_INTERMEDIARIA);
            LOG_PRINT("[CHAVE] %s %s...\n", chaves[n].nome, fechar ? "fechando" : "abrindo");

            fitaCobreComando();                                // a ordem desce pelo cobre
            moverServo(chaves[n].canal, fechar);               // leva SERVO_TEMPO_MS

            escreverPosicao(chaves[n].stVal, chaves[n].t, alvo);
            posChave[n] = alvo;
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
    fitaCobreComando();                                  // a ordem de abrir desce pelo cobre
    pthread_mutex_lock(&mtxDj);
    setLedsDisjuntor(DJ_TRIP_VERDE, DJ_TRIP_VERM, false);
    posDisjuntor[DJ_TRIP_INDICE] = POS_ABERTA;
    escreverPosicaoDj(DJ_TRIP_STVAL, DJ_TRIP_T, POS_ABERTA);
    pthread_mutex_unlock(&mtxDj);
#if CHAVE_AUTO_NA_FALTA
    chaveAutoEm = Hal_getTimeInMs() + CHAVE_AUTO_ATRASO_MS;   // a thread do patio abre a chave 1
#endif
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
    if ((int64_t) stNum == ultimoStNum) {                // repeticao do mesmo estado
        fitaRepeticaoGoose();                            // so uma bolinha amarela de vez em quando
        return;
    }

    bool primeira = (ultimoStNum < 0);
    ultimoStNum = stNum;

    MmsValue* valores = GooseSubscriber_getDataSetValues(sub);
    MmsValue* tr = valores ? MmsValue_getElement(valores, 0) : NULL;
    if (tr == NULL || MmsValue_getType(tr) != MMS_BOOLEAN) {
        LOG_PRINT("[GOOSE] Mensagem com formato inesperado (stNum=%u), ignorada.\n", stNum);
        return;
    }

    tripAtivo = MmsValue_getBoolean(tr);
    if (MmsValue_getBoolean(tr)) {
        fitaTrip();                                      // onda vermelha na fibra
        abrirDisjuntorPorTrip();
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[GOOSE] TRIP recebido do EmpElas_PROT (stNum=%u)\n", stNum);
        LOG_PRINT("   >> Acao: %s ABERTO pela protecao\n", DJ_TRIP_NOME);
        LOG_PRINT("--------------------------------------------------\n");
    }
    else if (primeira) {
        LOG_PRINT("[GOOSE] Assinatura do trip ativa (stNum=%u, sem trip).\n", stNum);
        fitaMensagem(COR_GOOSE, 1);
    }
    else {
        LOG_PRINT("[GOOSE] Trip retirado (stNum=%u). %s continua aberto: fechar pelo supervisorio (CSWI4).\n",
                  stNum, DJ_TRIP_NOME);
        fitaMensagem(COR_GOOSE, MSG_RAJADA);
    }
}

// ----------------------------------------------------------------
// Manobra de um disjuntor pedida pelo IED de controle (CSWI4-6, por GOOSE).
// O intertravamento (CILO4-6) ja foi conferido la. Aqui so se confere o
// que e do proprio patio: o disjuntor do trip nao fecha com o trip ativo.
// ----------------------------------------------------------------
static const int ledVerde[3] = { LED_D1_VERDE, LED_D2_VERDE, LED_D3_VERDE };
static const int ledVerm[3]  = { LED_D1_VERM,  LED_D2_VERM,  LED_D3_VERM };
static DataAttribute* const djStVal[3] = { IEDMODEL_VAO_XCBR1_Pos_stVal, IEDMODEL_VAO_XCBR2_Pos_stVal, IEDMODEL_VAO_XCBR3_Pos_stVal };
static DataAttribute* const djT[3]     = { IEDMODEL_VAO_XCBR1_Pos_t, IEDMODEL_VAO_XCBR2_Pos_t, IEDMODEL_VAO_XCBR3_Pos_t };

static void manobrarDisjuntor(int n, bool fechar) {
    if (fechar && n == DJ_TRIP_INDICE && tripAtivo) {
        LOG_PRINT("[DISJUNTOR] Disjuntor %d NAO fechou: o trip esta ativo.\n", n + 1);
        LOG_PRINT("--------------------------------------------------\n");
        return;
    }
    fitaCobreComando();                                  // a ordem desce pelo cobre
    pthread_mutex_lock(&mtxDj);
    setLedsDisjuntor(ledVerde[n], ledVerm[n], fechar);
    posDisjuntor[n] = fechar ? POS_FECHADA : POS_ABERTA;
    escreverPosicaoDj(djStVal[n], djT[n], posDisjuntor[n]);
    pthread_mutex_unlock(&mtxDj);
    LOG_PRINT("[DISJUNTOR] Disjuntor %d (XCBR%d) %s. Posicao publicada por GOOSE (gcbPos).\n",
              n + 1, n + 1, fechar ? "FECHADO" : "ABERTO");
    LOG_PRINT("--------------------------------------------------\n");
}

// ----------------------------------------------------------------
// Chamada a cada GOOSE de comandos recebido (inclusive as repeticoes).
// Ordem do dsCmd: chave 1 abrir/fechar, chave 2, chave 3, disjuntor 1
// abrir/fechar, disjuntor 2, disjuntor 3 (12 valores).
//
// Cada equipamento tem dois sinais: abrir (OpOpn) e fechar (OpCls). O IED
// de controle deixa o sinal em "verdadeiro" enquanto espera o equipamento
// chegar na posicao pedida, e depois volta para "falso". A manobra
// acontece so na SUBIDA do sinal (falso -> verdadeiro). As repeticoes
// trazem os mesmos valores e a volta para "falso" nao e subida, entao
// nenhuma delas faz o equipamento mexer de novo.
//
// A primeira mensagem depois que este programa abre so serve de
// referencia: um comando que ja estava no ar antes disso nao e executado.
// ----------------------------------------------------------------
static bool cmdReferencia = false;        // ja chegou a primeira mensagem?

static void gooseCmdListener(GooseSubscriber sub, void* parameter) {
    uint32_t stNum = GooseSubscriber_getStNum(sub);
    // Na fibra: estado novo = rajada amarela; repeticao = uma bolinha de vez em quando
    if ((int64_t) stNum != ultimoStNumCmd) fitaMensagem(COR_GOOSE, MSG_RAJADA);
    else fitaRepeticaoGoose();
    MmsValue* valores = GooseSubscriber_getDataSetValues(sub);
    bool agora[N_CMD];
    for (int k = 0; k < N_CMD; k++) {
        MmsValue* v = valores ? MmsValue_getElement(valores, k) : NULL;
        if (v == NULL || MmsValue_getType(v) != MMS_BOOLEAN) {
            if ((int64_t) stNum != ultimoStNumCmd)
                LOG_PRINT("[GOOSE] Comando com formato inesperado (stNum=%u), ignorado. Os dois .icd estao na mesma versao?\n", stNum);
            ultimoStNumCmd = stNum;
            return;
        }
        agora[k] = MmsValue_getBoolean(v);
    }
    ultimoStNumCmd = stNum;

    if (!cmdReferencia) {
        cmdReferencia = true;
        memcpy(cmdAnterior, agora, sizeof(agora));
        LOG_PRINT("[GOOSE] Assinatura dos comandos (chaves e disjuntores) ativa (stNum=%u).\n", stNum);
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
    for (int n = 0; n < 3; n++) {
        int k = 6 + 2 * n;
        bool abrir  = agora[k]     && !cmdAnterior[k];
        bool fechar = agora[k + 1] && !cmdAnterior[k + 1];
        if (!abrir && !fechar) continue;
        if (abrir && fechar) {
            LOG_PRINT("[GOOSE] CSWI%d pediu abrir e fechar ao mesmo tempo (stNum=%u). Ignorado.\n", n + 4, stNum);
            continue;
        }
        LOG_PRINT("--------------------------------------------------\n");
        LOG_PRINT("[GOOSE] Comando do IED de controle (stNum=%u): %s o disjuntor %d\n",
                  stNum, abrir ? "ABRIR" : "FECHAR", n + 1);
        manobrarDisjuntor(n, fechar);
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

// Posicao inicial no modelo, antes de o servidor abrir. Assim o primeiro
// GOOSE de posicoes ja diz a verdade (sem isso, tudo comecaria em 0,
// "em movimento", e o intertravamento bloquearia as chaves).
static void posicaoInicial(DataAttribute* stVal, DataAttribute* t, int pos) {
    IedServer_updateDbposValue(iedServer, stVal, (Dbpos) pos);
    IedServer_updateUTCTimeAttributeValue(iedServer, t, Hal_getTimeInMs());
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
        LOG_PRINT("[FITA] Fibra roxa com SV (branco), GOOSE (amarelo) e trip (vermelho).\n");
        if (FITA2_COUNT > 0)
            LOG_PRINT("[FITA 2] Cobre com medidas e comandos em GPIO%d (fisico 33), %d pixels.\n", FITA2_GPIO, FITA2_COUNT);
    }

    // Fita 3 (SPI). Se falhar, as outras continuam.
    if (FITA3_COUNT > 0) {
        ret = ws2811_init(&fita3);
        if (ret != WS2811_SUCCESS) {
            LOG_PRINT("[FITA 3] ws2811_init FALHOU: %s\n", ws2811_get_return_t_str(ret));
            LOG_PRINT("[FITA 3] O SPI esta ligado? Confira com: ls /dev/spidev0.0\n");
        } else {
            fita3Ok = true;
            LOG_PRINT("[FITA 3] Cobre com medidas e comandos em GPIO%d (fisico 19, SPI), %d pixels.\n", FITA3_GPIO, FITA3_COUNT);
        }
    }
    fitaApaga();

    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null != -1) dup2(dev_null, STDOUT_FILENO);

    iedServer = IedServer_create(&iedModel);
    atualizarRelogio();                         // antes de qualquer horario ser escrito
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

    // Disjuntores: tambem so mostram a posicao. O comando do operador vem por
    // GOOSE do IED de controle (CSWI4-6); o trip, direto da protecao.
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR1_Pos, CONTROL_MODEL_STATUS_ONLY);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR2_Pos, CONTROL_MODEL_STATUS_ONLY);
    IedServer_updateCtlModel(iedServer, IEDMODEL_VAO_XCBR3_Pos, CONTROL_MODEL_STATUS_ONLY);

    IedServer_setConnectionIndicationHandler(iedServer, (IedConnectionIndicationHandler) connectionHandler, NULL);

    // Agora este IED tambem PUBLICA GOOSE (as posicoes), entao a
    // publicacao sai pelo cabo, como a recepcao.
    IedServer_setGooseInterfaceId(iedServer, GOOSE_INTERFACE);
    IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer)) {
        LOG_PRINT("Falha ao iniciar servidor!\n");
        IedServer_destroy(iedServer);
        if (fitaOk) ws2811_fini(&fita);
        if (fita3Ok) ws2811_fini(&fita3);
        exit(-1);
    }

    // Habilita a publicacao do GOOSE de posicoes (gcbPos)
    IedServer_enableGoosePublishing(iedServer);

    // Assinaturas: trip e comandos (chaves e disjuntores), os dois vindos do EmpElas_PROT
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
        LOG_PRINT("[GOOSE] Escutando os comandos (chaves e disjuntores) em %s (APPID 0x%04X).\n",
                  GOOSE_INTERFACE, GOOSE_CMD_APPID);
    }
    else
        LOG_PRINT("[GOOSE] ERRO: receptor nao iniciou. Confira se %s existe e se rodou com sudo.\n",
                  GOOSE_INTERFACE);
    LOG_PRINT("[STATUS] Servos: canais %d, %d e %d do PCA9685 | LEDs D1-D3 | Fita GPIO%d (%d px)\n", SERVO1_CH, SERVO2_CH, SERVO3_CH, FITA_GPIO, FITA_COUNT);
    LOG_PRINT("[STATUS] Chaves fechadas, disjuntores abertos. Comandos so por GOOSE do IED de controle (CSWI1-6).\n");
    LOG_PRINT("[STATUS] Rodando na porta %d.\n", tcpPort);

    running = 1;
    if (fitaOk || fita3Ok) {
        Thread fitaThread = Thread_create((ThreadExecutionFunction)fita_thread, NULL, true);
        Thread_start(fitaThread);
    }
    Thread patioThread = Thread_create((ThreadExecutionFunction)patio_thread, NULL, false);
    Thread_start(patioThread);

    int ciclos = 0;
    while (running) {
        Thread_sleep(100);
        if (++ciclos % 50 == 0) atualizarRelogio();     // a cada 5 s
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
    fitaApaga();
    if (fitaOk) ws2811_fini(&fita);
    if (fita3Ok) ws2811_fini(&fita3);

    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    if (dev_null != -1) close(dev_null);
    return 0;
}
