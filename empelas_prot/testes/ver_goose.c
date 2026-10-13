/*
 * EmPowerElas - monitor das mensagens GOOSE da maquete (pelo terminal)
 *
 * Assina as tres mensagens GOOSE e mostra cada mudanca de estado:
 *   Pos  - posicoes publicadas pela Pi do servo (gcbPos)
 *   Cmd  - comandos das chaves publicados pela Pi das telinhas (gcbCmd)
 *   Trip - trip publicado pela Pi das telinhas (gcbTrip)
 * Nas repeticoes (o "estou vivo" a cada 1 s) so conta, sem imprimir.
 *
 * Nao mexe em nenhum servidor: pode rodar junto com eles, em qualquer Pi.
 *
 *   make testes
 *   sudo ./testes/ver_goose          (Ctrl+C para sair)
 */

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

static volatile int rodando = 1;
static void parar(int s) { (void) s; rodando = 0; }

static const char* NOME[3] = { "Pos ", "Cmd ", "Trip" };
static volatile unsigned recebidas[3];

static void aoReceber(GooseSubscriber sub, void* p) {
    static int64_t ultimo[3] = { -1, -1, -1 };
    int k = (int) (intptr_t) p;
    recebidas[k]++;
    uint32_t st = GooseSubscriber_getStNum(sub);
    if ((int64_t) st == ultimo[k]) return;
    ultimo[k] = st;

    char valores[300];
    MmsValue* v = GooseSubscriber_getDataSetValues(sub);
    if (v) MmsValue_printToBuffer(v, valores, sizeof(valores));
    else snprintf(valores, sizeof(valores), "(sem valores)");

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%02ld:%02ld.%03ld  %s stNum=%-4u %s\n", (long) (tv.tv_sec / 60) % 60, (long) tv.tv_sec % 60,
           (long) tv.tv_usec / 1000, NOME[k], st, valores);
    fflush(stdout);
}

static void assinar(GooseReceiver r, const char* ref, uint16_t appid, uint8_t ultimoByteMac, int k) {
    GooseSubscriber s = GooseSubscriber_create((char*) ref, NULL);
    uint8_t mac[6] = { 0x01, 0x0c, 0xcd, 0x01, 0x00, ultimoByteMac };
    GooseSubscriber_setDstMac(s, mac);
    GooseSubscriber_setAppId(s, appid);
    GooseSubscriber_setListener(s, aoReceber, (void*) (intptr_t) k);
    GooseReceiver_addSubscriber(r, s);
}

int main(int argc, char** argv) {
    const char* interface = (argc > 1) ? argv[1] : "eth0";
    signal(SIGINT, parar);
    signal(SIGTERM, parar);

    GooseReceiver r = GooseReceiver_create();
    GooseReceiver_setInterfaceId(r, interface);
    assinar(r, "EmpElas_CTRLVAO/LLN0$GO$gcbPos", 0x1002, 0x02, 0);
    assinar(r, "EmpElas_PROTMEDPROT/LLN0$GO$gcbCmd", 0x1003, 0x03, 1);
    assinar(r, "EmpElas_PROTMEDPROT/LLN0$GO$gcbTrip", 0x1001, 0x01, 2);
    GooseReceiver_start(r);
    if (!GooseReceiver_isRunning(r)) {
        printf("Nao consegui abrir %s. Rodou com sudo?\n", interface);
        return 1;
    }
    printf("Escutando GOOSE em %s. Posicoes: 10 = aberto, 01 = fechado, 00 = em movimento.\n", interface);
    printf("A cada 5 s mostra quantas mensagens chegaram de cada uma (contando as repeticoes).\n\n");

    int t = 0;
    while (rodando) {
        Thread_sleep(100);
        if (++t % 50 == 0) {
            printf("   [recebidas ate agora] Pos %u | Cmd %u | Trip %u\n", recebidas[0], recebidas[1], recebidas[2]);
            fflush(stdout);
        }
    }
    GooseReceiver_stop(r);
    GooseReceiver_destroy(r);
    return 0;
}
