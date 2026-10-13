/*
 * EmPowerElas - lista de eventos da maquete (pelo terminal)
 *
 * Liga o relatorio de eventos (brcbEventos) das tres Pis e mostra cada
 * mudanca com o horario em que ela aconteceu NA PI que a viu (o "t" de cada
 * valor), em ordem de horario. E a mesma informacao que o Elipse usa para a
 * lista de eventos. Os relogios das Pis precisam estar sincronizados (chrony):
 * um horario marcado com (relogio nao sinc.) veio de uma Pi sem sincronismo.
 *
 * Primeiro mostra o estado atual de tudo; depois, so as mudancas.
 * Pode rodar em qualquer Pi ou computador ligado no cabo da maquete, junto
 * com o Elipse (cada Pi aceita dois clientes de relatorio ao mesmo tempo).
 *
 *   make testes
 *   ./testes/ver_eventos                       (IPs do cabo: MU .103, telinhas .101, servo .100)
 *   ./testes/ver_eventos <ip-mu> <ip-telinhas> <ip-servo>
 *   (cada IP pode levar a porta: 127.0.0.1:10101)
 *
 * Ctrl+C para sair.
 */

#include "iec61850_client.h"
#include "hal_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

#define ESPERA_ORDEM_MS  400     // segura cada evento um pouco para ordenar por horario
#define MAX_PENDENTES    256
#define MAX_ITENS        16

typedef struct {
    const char* apelido;         // como aparece na lista
    const char* ld;              // nome do dispositivo logico (IED + LD)
    char ip[64];
    int porta;
    IedConnection con;
    char rcbRef[128];
    char nomes[MAX_ITENS][64];   // itens do dsEventos, na ordem (ex.: "PTOC1.Str")
    int nItens;
    int conectado;
    int avisouFalha;             // so avisa a falha de conexao uma vez
    uint64_t ultimoT[MAX_ITENS]; // ultimo evento de cada item, para nao repetir
    char ultimoTexto[MAX_ITENS][160];
} Ied;

static Ied ieds[3] = {
    { .apelido = "MU      ", .ld = "EmpElas_MUMU01" },
    { .apelido = "TELINHAS", .ld = "EmpElas_PROTMEDPROT" },
    { .apelido = "SERVO   ", .ld = "EmpElas_CTRLVAO" },
};

typedef struct {
    uint64_t t;                  // horario do evento (ms desde 1970, UTC)
    uint64_t chegada;            // quando chegou aqui
    unsigned seq;                // ordem de chegada (desempate no mesmo milissegundo)
    int naoSinc;
    int estadoInicial;
    char texto[200];
} Evento;

static Evento pendentes[MAX_PENDENTES];
static int nPendentes = 0;
static unsigned proximoSeq = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static volatile int rodando = 1;

static void parar(int s) { (void) s; rodando = 0; }

// ------------------------------------------------------------------
// Texto de cada evento
// ------------------------------------------------------------------
static const char* textoPos(MmsValue* v) {
    if (v == NULL || MmsValue_getType(v) != MMS_BIT_STRING) return "?";
    switch (MmsValue_getBitStringAsInteger(v)) {   // convencao da maquete
        case 0:  return "EM MOVIMENTO";
        case 1:  return "ABERTA";
        case 2:  return "FECHADA";
        default: return "INVALIDA";
    }
}

static int ligado(MmsValue* estrutura, int idx) {
    MmsValue* v = MmsValue_getElement(estrutura, idx);
    return (v && MmsValue_getType(v) == MMS_BOOLEAN) ? MmsValue_getBoolean(v) : 0;
}

static void fases(MmsValue* d, int iA, int iB, int iC, char* saida, size_t n) {
    snprintf(saida, n, "%s%s%s", ligado(d, iA) ? " A" : "", ligado(d, iB) ? " B" : "", ligado(d, iC) ? " C" : "");
}

static void descrever(const char* nome, MmsValue* d, char* s, size_t n) {
    MmsValue* v0 = MmsValue_getElement(d, 0);
    int b = (v0 && MmsValue_getType(v0) == MMS_BOOLEAN) ? MmsValue_getBoolean(v0) : 0;
    char f[16];

    if (strstr(nome, "SPCSO1"))
        snprintf(s, n, "%-16s %s", nome, b ? "ARVORE CAIU na linha (falta na fase A)" : "arvore retirada");
    else if (strstr(nome, ".Str")) {
        fases(d, 2, 4, 6, f, sizeof(f));
        snprintf(s, n, "%-16s %s%s", nome, b ? "protecao PARTIU (viu sobrecorrente) - fase" : "partida voltou ao normal", b ? f : "");
    }
    else if (strstr(nome, ".Op")) {
        fases(d, 1, 2, 3, f, sizeof(f));
        snprintf(s, n, "%-16s %s%s", nome, b ? "protecao OPEROU - fase" : "operacao voltou ao normal", b ? f : "");
    }
    else if (strstr(nome, ".Tr"))
        snprintf(s, n, "%-16s %s", nome, b ? "TRIP (GOOSE para o disjuntor)" : "trip retirado");
    else if (strstr(nome, "EnaOpn"))
        snprintf(s, n, "%-16s chave %c %s", nome, nome[4], b ? "LIBERADA" : "BLOQUEADA pelo intertravamento");
    else if (strstr(nome, "XCBR")) {
        const char* p = textoPos(v0);
        snprintf(s, n, "%-16s disjuntor %c %s", nome, nome[4],
                 strcmp(p, "ABERTA") == 0 ? "ABERTO" : strcmp(p, "FECHADA") == 0 ? "FECHADO" : p);
    }
    else if (strstr(nome, "XSWI"))
        snprintf(s, n, "%-16s chave %c %s (no patio)", nome, nome[4], textoPos(v0));
    else if (strstr(nome, "CSWI"))
        snprintf(s, n, "%-16s chave %c %s (posicao recebida por GOOSE)", nome, nome[4], textoPos(v0));
    else
        snprintf(s, n, "%-16s mudou", nome);
}

// ------------------------------------------------------------------
// Recebe um relatorio: cada item incluido vira um evento
// ------------------------------------------------------------------
static void aoReceberRelatorio(void* parametro, ClientReport rpt) {
    Ied* ied = (Ied*) parametro;
    MmsValue* valores = ClientReport_getDataSetValues(rpt);
    if (valores == NULL) return;
    uint64_t agora = Hal_getTimeInMs();

    pthread_mutex_lock(&mtx);
    for (int i = 0; i < ied->nItens; i++) {
        ReasonForInclusion r = ClientReport_getReasonForInclusion(rpt, i);
        if (r == IEC61850_REASON_NOT_INCLUDED) continue;
        MmsValue* d = MmsValue_getElement(valores, i);
        if (d == NULL || MmsValue_getType(d) != MMS_STRUCTURE) continue;
        MmsValue* t = MmsValue_getElement(d, MmsValue_getArraySize(d) - 1);   // o ultimo e o horario
        if (nPendentes >= MAX_PENDENTES) break;

        uint64_t quando = (t && MmsValue_getType(t) == MMS_UTC_TIME) ? MmsValue_getUtcTimeInMs(t) : 0;
        char desc[160];
        descrever(ied->nomes[i], d, desc, sizeof(desc));
        // O mesmo evento pode chegar duas vezes (dois relatorios seguidos): mostra uma so
        if (r != IEC61850_REASON_GI && quando == ied->ultimoT[i] && strcmp(desc, ied->ultimoTexto[i]) == 0)
            continue;
        ied->ultimoT[i] = quando;
        snprintf(ied->ultimoTexto[i], sizeof(ied->ultimoTexto[0]), "%s", desc);

        Evento* e = &pendentes[nPendentes++];
        e->t = quando;
        e->naoSinc = (quando != 0) && ((MmsValue_getUtcTimeQuality(t) & 0x20) != 0);
        e->chegada = agora;
        e->seq = proximoSeq++;
        e->estadoInicial = (r == IEC61850_REASON_GI);
        snprintf(e->texto, sizeof(e->texto), "%s  %s", ied->apelido, desc);
    }
    pthread_mutex_unlock(&mtx);
}

// Imprime, em ordem de horario, os eventos que ja esperaram o suficiente
static void imprimirProntos(int tudo) {
    uint64_t agora = Hal_getTimeInMs();
    pthread_mutex_lock(&mtx);
    for (;;) {
        int melhor = -1;
        for (int i = 0; i < nPendentes; i++)
            if ((tudo || agora - pendentes[i].chegada >= ESPERA_ORDEM_MS) &&
                (melhor < 0 || pendentes[i].t < pendentes[melhor].t ||
                 (pendentes[i].t == pendentes[melhor].t && pendentes[i].seq < pendentes[melhor].seq)))
                melhor = i;
        if (melhor < 0) break;

        Evento* e = &pendentes[melhor];
        char hora[16] = "--:--:--.---";        // horario zero: o valor nunca mudou desde que a Pi ligou
        if (e->t != 0) {
            time_t seg = (time_t) (e->t / 1000);
            struct tm tm;
            localtime_r(&seg, &tm);
            snprintf(hora, sizeof(hora), "%02d:%02d:%02d.%03d", tm.tm_hour, tm.tm_min, tm.tm_sec, (int) (e->t % 1000));
        }
        printf("%s  %s%s%s\n", hora, e->estadoInicial ? "[estado atual] " : "", e->texto,
               e->naoSinc ? "  (relogio nao sinc.)" : "");
        pendentes[melhor] = pendentes[--nPendentes];
    }
    pthread_mutex_unlock(&mtx);
    fflush(stdout);
}

// ------------------------------------------------------------------
// Conecta numa Pi e liga o relatorio de eventos dela
// ------------------------------------------------------------------
static int ligarRelatorio(Ied* ied) {
    IedClientError erro;
    ied->con = IedConnection_create();
    IedConnection_setConnectTimeout(ied->con, 2000);
    IedConnection_connect(ied->con, &erro, ied->ip, ied->porta);
    if (erro != IED_ERROR_OK) {
        if (!ied->avisouFalha)
            printf("   %s (%s): nao conectou. A Pi esta ligada e com o programa rodando?\n", ied->apelido, ied->ip);
        goto falhou;
    }

    // Nomes dos itens do conjunto de dados, na ordem em que vem no relatorio
    char ref[128];
    snprintf(ref, sizeof(ref), "%s/LLN0.dsEventos", ied->ld);
    LinkedList dir = IedConnection_getDataSetDirectory(ied->con, &erro, ref, NULL);
    if (erro != IED_ERROR_OK || dir == NULL) {
        if (!ied->avisouFalha)
            printf("   %s: nao achei o %s. O programa da Pi foi compilado com o ICD novo?\n", ied->apelido, ref);
        goto falhou;
    }
    ied->nItens = 0;
    for (LinkedList e = LinkedList_getNext(dir); e && ied->nItens < MAX_ITENS; e = LinkedList_getNext(e)) {
        const char* r = (const char*) LinkedList_getData(e);
        const char* barra = strchr(r, '/');
        snprintf(ied->nomes[ied->nItens], sizeof(ied->nomes[0]), "%s", barra ? barra + 1 : r);
        char* colchete = strchr(ied->nomes[ied->nItens], '[');
        if (colchete) *colchete = 0;
        ied->nItens++;
    }
    LinkedList_destroy(dir);

    // Usa a instancia 02 (deixa a 01 para o Elipse); se estiver ocupada, tenta a 01
    for (int inst = 2; inst >= 1; inst--) {
        snprintf(ied->rcbRef, sizeof(ied->rcbRef), "%s/LLN0.BR.brcbEventos%02d", ied->ld, inst);
        ClientReportControlBlock rcb = IedConnection_getRCBValues(ied->con, &erro, ied->rcbRef, NULL);
        if (erro != IED_ERROR_OK || rcb == NULL) continue;
        if (ClientReportControlBlock_getRptEna(rcb)) {   // outro cliente ja esta usando
            ClientReportControlBlock_destroy(rcb);
            continue;
        }
        IedConnection_installReportHandler(ied->con, ied->rcbRef, ClientReportControlBlock_getRptId(rcb),
                                           aoReceberRelatorio, ied);
        ClientReportControlBlock_setPurgeBuf(rcb, true);    // sem eventos antigos do buffer
        IedConnection_setRCBValues(ied->con, &erro, rcb, RCB_ELEMENT_PURGE_BUF, true);
        ClientReportControlBlock_setRptEna(rcb, true);
        IedConnection_setRCBValues(ied->con, &erro, rcb, RCB_ELEMENT_RPT_ENA, true);
        if (erro == IED_ERROR_OK) {
            ClientReportControlBlock_setGI(rcb, true);       // pede o estado atual de tudo
            IedConnection_setRCBValues(ied->con, &erro, rcb, RCB_ELEMENT_GI, true);
            ClientReportControlBlock_destroy(rcb);
            printf("   %s (%s): relatorio %s ligado, %d itens.\n", ied->apelido, ied->ip,
                   strrchr(ied->rcbRef, '.') + 1, ied->nItens);
            ied->conectado = 1;
            ied->avisouFalha = 0;
            return 1;
        }
        ClientReportControlBlock_destroy(rcb);
    }
    if (!ied->avisouFalha)
        printf("   %s: os dois relatorios estao ocupados ou deram erro.\n", ied->apelido);

falhou:
    ied->avisouFalha = 1;
    IedConnection_destroy(ied->con);
    ied->con = NULL;
    return 0;
}

static void separarIpPorta(const char* arg, Ied* ied) {
    snprintf(ied->ip, sizeof(ied->ip), "%s", arg);
    ied->porta = 102;
    char* p = strchr(ied->ip, ':');
    if (p) { *p = 0; ied->porta = atoi(p + 1); }
}

int main(int argc, char** argv) {
    const char* padrao[3] = { "192.168.10.103", "192.168.10.101", "192.168.10.100" };
    for (int i = 0; i < 3; i++) separarIpPorta(argc > 3 ? argv[1 + i] : padrao[i], &ieds[i]);
    signal(SIGINT, parar);
    signal(SIGTERM, parar);

    printf("Lista de eventos da maquete. Horario = quando a Pi viu a mudanca.\n");
    for (int i = 0; i < 3; i++) ligarRelatorio(&ieds[i]);
    printf("\n");

    int ciclos = 0;
    while (rodando) {
        Thread_sleep(100);
        imprimirProntos(0);
        if (++ciclos % 30 == 0) {                         // a cada 3 s: alguma Pi caiu ou voltou?
            for (int i = 0; i < 3; i++) {
                Ied* ied = &ieds[i];
                if (ied->con && IedConnection_getState(ied->con) == IED_STATE_CONNECTED) continue;
                if (ied->conectado) {
                    printf("--- %s desconectou. Tentando de novo a cada 3 s...\n", ied->apelido);
                    ied->conectado = 0;
                }
                if (ied->con) { IedConnection_destroy(ied->con); ied->con = NULL; }
                ligarRelatorio(ied);
            }
        }
    }

    imprimirProntos(1);
    for (int i = 0; i < 3; i++) {
        if (ieds[i].con == NULL) continue;
        IedClientError erro;
        ClientReportControlBlock rcb = IedConnection_getRCBValues(ieds[i].con, &erro, ieds[i].rcbRef, NULL);
        if (rcb) {
            ClientReportControlBlock_setRptEna(rcb, false);   // devolve o relatorio para quem precisar
            IedConnection_setRCBValues(ieds[i].con, &erro, rcb, RCB_ELEMENT_RPT_ENA, true);
            ClientReportControlBlock_destroy(rcb);
        }
        IedConnection_close(ieds[i].con);
        IedConnection_destroy(ieds[i].con);
    }
    printf("\nFim.\n");
    return 0;
}
