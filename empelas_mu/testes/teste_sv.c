/*
 * Monitor de Sampled Values: mostra, a cada segundo, o que esta chegando da
 * merging unit (EmpElas_MU). Nao mexe em nenhum servidor.
 *
 * Use para conferir a rede antes de rodar a protecao: se aqui aparecerem
 * 4800 mensagens por segundo e os valores certos, o SV esta funcionando.
 *
 * Compilar (na pasta empelas_mu):  make testes
 * Rodar:                           sudo ./testes/teste_sv eth0
 */
#include "sv_subscriber.h"
#include "hal_thread.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/if_packet.h>

#define LOG_PRINT(...) printf(__VA_ARGS__)
#define SV_APPID            0x4000
#define SV_ID               "EmpElas_MU01"
#define AMOSTRAS_POR_SEG    4800

static volatile int running = 1;

// ----------------------------------------------------------------
// Pede para a placa de rede aceitar o endereco de grupo do SV.
//
// Sem isso, a placa descarta as mensagens de SV antes de chegarem no
// programa (a versao 1.6 da libiec61850 nao faz esse pedido sozinha para
// o SV; para o GOOSE ela faz). O pedido vale enquanto este socket estiver
// aberto, ou seja, enquanto o programa rodar. O socket nao recebe nada.
// ----------------------------------------------------------------
static int sockGrupoSV = -1;

static void aceitarGrupoSV(const char* interface, const uint8_t* mac) {
    sockGrupoSV = socket(AF_PACKET, SOCK_RAW, 0);
    if (sockGrupoSV < 0) {
        LOG_PRINT("[SV] Aviso: nao consegui pedir o grupo do SV (rode com sudo).\n");
        return;
    }
    struct packet_mreq mr;
    memset(&mr, 0, sizeof(mr));
    mr.mr_ifindex = (int) if_nametoindex(interface);
    mr.mr_type = PACKET_MR_MULTICAST;
    mr.mr_alen = 6;
    memcpy(mr.mr_address, mac, 6);
    if (mr.mr_ifindex == 0 ||
        setsockopt(sockGrupoSV, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) != 0)
        LOG_PRINT("[SV] Aviso: a placa %s nao aceitou o grupo do SV. Se nada chegar, rode:\n"
                  "     sudo ip link set %s allmulticast on\n", interface, interface);
}
static void parar(int s) { running = 0; }

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static double soma[8];
static long amostras, perdidas, repetidas, outros;
static int ultimoSmpCnt = -1;
static char svIdVisto[65] = "";
static unsigned confRevVisto = 0;
static int smpSynchVisto = -1;

static void aoReceber(SVSubscriber sub, void* p, SVSubscriber_ASDU asdu) {
    const char* id = SVSubscriber_ASDU_getSvId(asdu);
    if (id == NULL || strcmp(id, SV_ID) != 0 || SVSubscriber_ASDU_getDataSize(asdu) < 64) {
        pthread_mutex_lock(&mtx); outros++; pthread_mutex_unlock(&mtx);
        return;
    }
    int smpCnt = SVSubscriber_ASDU_getSmpCnt(asdu);

    pthread_mutex_lock(&mtx);
    if (smpCnt == ultimoSmpCnt) { repetidas++; pthread_mutex_unlock(&mtx); return; }
    if (ultimoSmpCnt >= 0) {
        int esperado = (ultimoSmpCnt + 1) % AMOSTRAS_POR_SEG;
        perdidas += (smpCnt - esperado + AMOSTRAS_POR_SEG) % AMOSTRAS_POR_SEG;
    }
    ultimoSmpCnt = smpCnt;

    for (int ch = 0; ch < 8; ch++) {
        double x = SVSubscriber_ASDU_getINT32(asdu, ch * 8);
        x *= (ch < 4) ? 0.001 : 0.01;          // mA -> A ; 10 mV -> V
        soma[ch] += x * x;
    }
    amostras++;
    strncpy(svIdVisto, id, sizeof(svIdVisto) - 1);
    confRevVisto = SVSubscriber_ASDU_getConfRev(asdu);
    smpSynchVisto = SVSubscriber_ASDU_getSmpSynch(asdu);
    pthread_mutex_unlock(&mtx);
}

int main(int argc, char** argv) {
    signal(SIGINT, parar); signal(SIGTERM, parar);
    const char* interface = (argc > 1) ? argv[1] : "eth0";

    SVReceiver r = SVReceiver_create();
    SVReceiver_setInterfaceId(r, interface);
    uint8_t dstMac[6] = {0x01, 0x0C, 0xCD, 0x04, 0x00, 0x01};
    SVSubscriber s = SVSubscriber_create(dstMac, SV_APPID);
    SVSubscriber_setListener(s, aoReceber, NULL);
    SVReceiver_addSubscriber(r, s);
    SVReceiver_start(r);
    aceitarGrupoSV(interface, dstMac);
    if (!SVReceiver_isRunning(r)) {
        printf("Receptor nao iniciou. Confira a interface (%s) e rode com sudo.\n", interface);
        return 1;
    }
    printf("Escutando SV em %s (APPID 0x%04X, svID %s). Ctrl+C para sair.\n\n", interface, SV_APPID, SV_ID);

    while (running) {
        Thread_sleep(1000);
        pthread_mutex_lock(&mtx);
        long n = amostras;
        double rms[8];
        for (int ch = 0; ch < 8; ch++) { rms[ch] = n ? sqrt(soma[ch] / n) : 0; soma[ch] = 0; }
        long pe = perdidas, re = repetidas, ou = outros;
        amostras = perdidas = repetidas = outros = 0;
        pthread_mutex_unlock(&mtx);

        if (n == 0) {
            printf("[SV] nada chegando%s\n", ou ? " (chegou SV de outro svID/formato)" : "");
            continue;
        }
        printf("[SV] %ld msg/s | perdidas %ld | repetidas %ld | svID %s | confRev %u | smpSynch %d\n",
               n, pe, re, svIdVisto, confRevVisto, smpSynchVisto);
        printf("     IA %6.1f A   IB %6.1f A   IC %6.1f A   IN %6.1f A\n", rms[0], rms[1], rms[2], rms[3]);
        printf("     VA %6.1f kV  VB %6.1f kV  VC %6.1f kV  VN %6.1f kV\n\n",
               rms[4] / 1000, rms[5] / 1000, rms[6] / 1000, rms[7] / 1000);
        fflush(stdout);
    }
    SVReceiver_stop(r);
    SVReceiver_destroy(r);
    return 0;
}
