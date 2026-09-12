/*
 * pin_test.c  -  Testa se a SAIDA do canal 0 do PCA9685 funciona.
 *
 * Nao usa pulso de servo: forca o canal 0 em 100% LIGADO por 3s e
 * 100% DESLIGADO por 3s, em loop. Assim da pra medir com o multimetro
 * sem ambiguidade (o pulso de servo e curto e engana o multimetro):
 *   LIGADO   -> pino PWM do canal 0 ~= 3,3V (nivel do VCC)
 *   DESLIGADO-> pino PWM do canal 0 ~= 0V
 *
 * Se NAO variar (fica sempre 0V), a saida do chip nao esta habilitada
 * (OE) ou o chip nao esta gerando saida.
 * Se VARIAR 0V <-> 3,3V, a saida FUNCIONA e o problema e o servo/pulso.
 *
 * Compilar:  gcc -o pin_test pin_test.c -lwiringPi -lm
 * Rodar:     sudo ./pin_test     (Ctrl+C para sair)
 */

#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PCA_ADDR      0x40
#define PCA_MODE1     0x00
#define PCA_PRESCALE  0xFE
#define PCA_LED0_ON_L 0x06
#define CANAL         0
#define PCA_FREQ      50.0f

static int fd = -1;
static volatile int rodando = 1;
static void para(int s) { rodando = 0; }

static void pcaSetFreq(int fd, float freq) {
    int prescale = (int)(25000000.0f / (4096.0f * freq) - 1.0f + 0.5f);
    int oldmode  = wiringPiI2CReadReg8(fd, PCA_MODE1);
    wiringPiI2CWriteReg8(fd, PCA_MODE1, (oldmode & 0x7F) | 0x10);
    wiringPiI2CWriteReg8(fd, PCA_PRESCALE, prescale);
    int wakemode = oldmode & ~0x10;
    wiringPiI2CWriteReg8(fd, PCA_MODE1, wakemode);
    delay(5);
    wiringPiI2CWriteReg8(fd, PCA_MODE1, wakemode | 0xA0);
}

static void pcaSetPwm(int fd, int canal, int on, int off) {
    int reg = PCA_LED0_ON_L + 4 * canal;
    wiringPiI2CWriteReg8(fd, reg,     on  & 0xFF);
    wiringPiI2CWriteReg8(fd, reg + 1, on  >> 8);
    wiringPiI2CWriteReg8(fd, reg + 2, off & 0xFF);
    wiringPiI2CWriteReg8(fd, reg + 3, off >> 8);
}

int main(void) {
    signal(SIGINT, para);
    if (wiringPiSetup() == -1) { printf("wiringPi falhou (use sudo)\n"); return 1; }
    fd = wiringPiI2CSetup(PCA_ADDR);
    if (fd < 0) { printf("PCA nao encontrado em 0x40\n"); return 1; }

    pcaSetFreq(fd, PCA_FREQ);
    printf("Alternando canal %d entre 100%% LIGADO e 100%% DESLIGADO.\n", CANAL);
    printf("Mede o pino PWM do canal %d <-> GND: deve ir de ~3,3V a ~0V.\n\n", CANAL);

    while (rodando) {
        printf("  LIGADO  (deve dar ~3,3V no pino)\n");
        pcaSetPwm(fd, CANAL, 4096, 0);   // full ON
        delay(3000);
        if (!rodando) break;
        printf("  DESLIGADO (deve dar ~0V no pino)\n");
        pcaSetPwm(fd, CANAL, 0, 4096);   // full OFF
        delay(3000);
    }
    pcaSetPwm(fd, CANAL, 0, 4096);
    printf("\nEncerrado.\n");
    return 0;
}
