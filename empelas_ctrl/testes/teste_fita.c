/*
 * EmPowerElas - teste da fita WS2811 (Pi do servo)
 *
 * Descobre as duas coisas que o server_ctrl.c precisa saber da fita:
 *
 *   Passo 1 - ORDEM DAS CORES (FITA_TIPO): acende os 3 primeiros pixels,
 *             que deveriam ficar vermelho, verde e azul. As cores que
 *             aparecerem dizem a ordem da fita.
 *   Passo 2 - TAMANHO (FITA_COUNT): acende um pixel branco a cada 10 e faz
 *             o ULTIMO pixel piscar. O pisca-pisca tem que cair no ultimo
 *             grupo de LEDs da fita.
 *
 * Um "pixel" e um grupo de 3 LEDs (um chip WS2811). Os pixels contam a
 * partir da ponta onde o dado entra (onde comeca a seta).
 *
 * O empelas_ctrl NAO pode estar rodando: os dois usam o mesmo PWM.
 *
 *   make testes
 *   sudo ./testes/teste_fita            (fita de 100 pixels)
 *   sudo ./testes/teste_fita 60         (outro tamanho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include "ws2811.h"

#define FITA_GPIO    18          // fisico 12, o mesmo do server_ctrl.c
#define FITA_DMA     10
#define FITA_BRILHO  128

static ws2811_t fita = {
    .freq = WS2811_TARGET_FREQ,
    .dmanum = FITA_DMA,
    .channel = {
        [0] = { .gpionum = FITA_GPIO, .invert = 0, .count = 100,
                .strip_type = WS2811_STRIP_RGB, .brightness = FITA_BRILHO },
        [1] = { .gpionum = 0, .invert = 0, .count = 0, .brightness = 0 },
    },
};

static volatile int rodando = 1;
static void parar(int s) { (void) s; rodando = 0; }

static void limpar(void) {
    for (int i = 0; i < fita.channel[0].count; i++) fita.channel[0].leds[i] = 0;
}

// Espera o Enter por ate 'ms' milissegundos. Devolve 1 se apertaram Enter.
static int esperarEnter(int ms) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    struct timeval tv = { ms / 1000, (ms % 1000) * 1000 };
    if (select(1, &fds, NULL, NULL, &tv) > 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    int n = (argc > 1) ? atoi(argv[1]) : 100;
    if (n < 3 || n > 1000) {
        printf("Use um tamanho entre 3 e 1000 pixels.\n");
        return 1;
    }
    fita.channel[0].count = n;

    signal(SIGINT, parar);
    signal(SIGTERM, parar);

    ws2811_return_t ret = ws2811_init(&fita);
    if (ret != WS2811_SUCCESS) {
        printf("ERRO ao iniciar a fita: %s\n", ws2811_get_return_t_str(ret));
        printf("Rodou com sudo? O empelas_ctrl esta fechado?\n");
        return 1;
    }

    // ---------------- Passo 1: ordem das cores ----------------
    limpar();
    fita.channel[0].leds[0] = 0x00FF0000;   // deveria ser vermelho
    fita.channel[0].leds[1] = 0x0000FF00;   // deveria ser verde
    fita.channel[0].leds[2] = 0x000000FF;   // deveria ser azul
    ws2811_render(&fita);

    printf("\nPASSO 1 - ORDEM DAS CORES\n");
    printf("Olhe os 3 primeiros grupos de LEDs, a partir da ponta onde o dado entra.\n");
    printf("Anote as cores, nesta ordem, e procure na tabela:\n\n");
    printf("  vermelho, verde,    azul      ->  WS2811_STRIP_RGB  (nada a mudar)\n");
    printf("  vermelho, azul,     verde     ->  WS2811_STRIP_RBG\n");
    printf("  verde,    vermelho, azul      ->  WS2811_STRIP_GRB\n");
    printf("  verde,    azul,     vermelho  ->  WS2811_STRIP_GBR\n");
    printf("  azul,     vermelho, verde     ->  WS2811_STRIP_BRG\n");
    printf("  azul,     verde,    vermelho  ->  WS2811_STRIP_BGR\n\n");
    printf("Esse nome vai no FITA_TIPO do server_ctrl.c.\n");
    printf("Nada acendeu? Confira 12 V, GND comum, fio do dado no pino 12 e o lado da seta.\n");
    printf("Aperte Enter para o passo 2 (ou Ctrl+C para sair).\n");
    while (rodando && !esperarEnter(200)) { }

    // ---------------- Passo 2: tamanho ----------------
    if (rodando) {
        printf("\nPASSO 2 - TAMANHO (%d pixels)\n", n);
        printf("Um grupo branco a cada 10 (o 1o, o 11o, o 21o...) e o grupo numero %d piscando.\n", n);
        printf("  - Pisca no ULTIMO grupo da fita: FITA_COUNT = %d esta certo.\n", n);
        printf("  - Pisca antes do fim: a fita tem mais. Conte os grupos e rode de novo com o numero maior.\n");
        printf("  - Nada pisca: a fita tem menos. Conte os brancos (cada um vale 10) e rode de novo.\n");
        printf("Ctrl+C para sair.\n");
    }
    int aceso = 0;
    while (rodando) {
        limpar();
        for (int i = 0; i < n; i += 10) fita.channel[0].leds[i] = 0x00404040;   // branco fraco
        if (aceso) fita.channel[0].leds[n - 1] = 0x00FFFFFF;                     // ultimo, piscando
        ws2811_render(&fita);
        aceso = !aceso;
        esperarEnter(500);
    }

    limpar();
    ws2811_render(&fita);
    ws2811_fini(&fita);
    printf("\nFita apagada.\n");
    return 0;
}
