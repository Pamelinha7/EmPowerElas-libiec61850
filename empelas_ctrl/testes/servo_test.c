/*
 * servo_test3.c  -  Testa os TRES servos (canais 0, 1 e 2) do PCA9685.
 *
 * Varre os 3 canais juntos entre ~1,0 ms e ~2,0 ms, em loop.
 * Serve para confirmar os 3 servos e a fiacao de cada canal.
 *
 * Compilar: gcc -o servo_test3 servo_test3.c -lwiringPi -lm
 * Rodar:    sudo ./servo_test3   (Ctrl+C para sair)
 */

#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PCA_ADDR      0x40
#define PCA_MODE1     0x00
#define PCA_PRESCALE  0xFE
#define PCA_LED0_ON_L 0x06
#define PCA_FREQ      50.0f

#define TICK_MIN      205      // ~1,0 ms
#define TICK_MAX      410      // ~2,0 ms

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
    printf("Varrendo os canais 0, 1 e 2. Ctrl+C para parar.\n");

    while (rodando) {
        printf("  -> %d (~1,0 ms)  [canais 0,1,2]\n", TICK_MIN);
        pcaSetPwm(fd, 0, 0, TICK_MIN);
        pcaSetPwm(fd, 1, 0, TICK_MIN);
        pcaSetPwm(fd, 2, 0, TICK_MIN);
        delay(1000);
        if (!rodando) break;

        printf("  -> %d (~2,0 ms)  [canais 0,1,2]\n", TICK_MAX);
        pcaSetPwm(fd, 0, 0, TICK_MAX);
        pcaSetPwm(fd, 1, 0, TICK_MAX);
        pcaSetPwm(fd, 2, 0, TICK_MAX);
        delay(1000);
    }

    pcaSetPwm(fd, 0, 0, 4096);
    pcaSetPwm(fd, 1, 0, 4096);
    pcaSetPwm(fd, 2, 0, 4096);
    printf("\nEncerrado.\n");
    return 0;
}
