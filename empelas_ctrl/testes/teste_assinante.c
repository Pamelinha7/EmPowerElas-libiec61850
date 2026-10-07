/* Assinante de teste do GOOSE de trip. Roda na Pi do servo, sem mexer no servidor dela.
 * Compilar:  gcc -I/usr/local/include/libiec61850 -o teste_assinante teste_assinante.c -L/usr/local/lib -liec61850 -lpthread -lm -lsqlite3
 * Rodar:     sudo ./teste_assinante eth0 */
#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"
#include <stdio.h>
#include <signal.h>
static int running = 1;
static void parar(int s){ running = 0; }
static void aoReceber(GooseSubscriber sub, void* p) {
    MmsValue* v = GooseSubscriber_getDataSetValues(sub);
    MmsValue* tr = v ? MmsValue_getElement(v, 0) : NULL;
    printf("GOOSE recebido | stNum=%u sqNum=%u | trip=%s | valido=%s\n",
        GooseSubscriber_getStNum(sub), GooseSubscriber_getSqNum(sub),
        tr ? (MmsValue_getBoolean(tr) ? "TRUE" : "false") : "?",
        GooseSubscriber_isValid(sub) ? "sim" : "nao");
    fflush(stdout);
}
int main(int argc, char** argv) {
    signal(SIGINT, parar); signal(SIGTERM, parar);
    GooseReceiver r = GooseReceiver_create();
    GooseReceiver_setInterfaceId(r, argc > 1 ? argv[1] : "eth0");
    GooseSubscriber s = GooseSubscriber_create("EmpElas_PROTMEDPROT/LLN0$GO$gcbTrip", NULL);
    /* Endereco de destino do GOOSE, igual ao do .icd (MAC-Address 01-0C-CD-01-00-01).
     * Informar o endereco faz a biblioteca pedir a placa de rede para aceitar
     * esse grupo. Sem isso, a placa pode descartar a mensagem antes do programa. */
    uint8_t dstMac[6] = {0x01, 0x0c, 0xcd, 0x01, 0x00, 0x01};
    GooseSubscriber_setDstMac(s, dstMac);
    GooseSubscriber_setAppId(s, 0x1001);
    GooseSubscriber_setListener(s, aoReceber, NULL);
    GooseReceiver_addSubscriber(r, s);
    GooseReceiver_start(r);
    if (!GooseReceiver_isRunning(r)) { printf("receptor nao iniciou\n"); return 1; }
    while (running) Thread_sleep(100);
    GooseReceiver_stop(r); GooseReceiver_destroy(r);
    return 0;
}
