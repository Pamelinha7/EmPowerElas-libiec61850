/*
 * EmPowerElas - manobra pelo terminal (sem o Elipse)
 *
 * Comanda as chaves pelo IED de controle (CSWI, na Pi das telinhas) e os
 * disjuntores direto na Pi do servo (XCBR), do mesmo jeito que o Elipse
 * faz. Serve para testar o intertravamento e para a demonstracao.
 *
 *   ./testes/manobra <IP da Pi das telinhas> chave <1-3> [abrir|fechar]
 *   ./testes/manobra <IP da Pi do servo>     dj    <1-3> [abrir|fechar]
 *
 * Sem "abrir" ou "fechar" (ou com "ver"), so mostra o estado. Um numero no
 * fim troca a porta (padrao 102).
 *
 * Exemplos (IPs do cabo, roteador da maquete):
 *   ./testes/manobra 192.168.10.101 chave 1 abrir
 *   ./testes/manobra 192.168.10.100 dj 1 fechar
 */

#include "iec61850_client.h"
#include "hal_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_ABERTA   1
#define POS_FECHADA  2

static const char* textoPos(int p, bool chave) {
    switch (p) {
    case 0:  return "em movimento";
    case 1:  return chave ? "aberta" : "aberto";
    case 2:  return chave ? "fechada" : "fechado";
    default: return chave ? "invalida" : "invalido";
    }
}

static const char* textoAddCause(int c) {
    switch (c) {
    case 5:  return "ja esta nessa posicao";
    case 10: return "bloqueado pelo intertravamento";
    case 12: return "a chave ainda esta manobrando";
    default: return "outro motivo (veja o terminal do IED)";
    }
}

// Le uma posicao de ponto duplo (1 = aberto, 2 = fechado). -1 se falhar.
static int lerPos(IedConnection con, const char* ref, bool* qualidadeBoa) {
    IedClientError err;
    char r[128];
    snprintf(r, sizeof(r), "%s.stVal", ref);
    MmsValue* v = IedConnection_readObject(con, &err, r, IEC61850_FC_ST);
    if (err != IED_ERROR_OK || v == NULL) return -1;
    int p = (MmsValue_getType(v) == MMS_BIT_STRING) ? (int) MmsValue_getBitStringAsInteger(v) : -1;
    MmsValue_delete(v);
    if (qualidadeBoa) {
        snprintf(r, sizeof(r), "%s.q", ref);
        Quality q = IedConnection_readQualityValue(con, &err, r, IEC61850_FC_ST);
        *qualidadeBoa = (err == IED_ERROR_OK) && (Quality_getValidity(&q) == QUALITY_VALIDITY_GOOD);
    }
    return p;
}

static void mostrarChave(IedConnection con, const char* ld, int n) {
    IedClientError err;
    char ref[128];
    bool qOk = false;
    snprintf(ref, sizeof(ref), "%s/CSWI%d.Pos", ld, n);
    int p = lerPos(con, ref, &qOk);
    snprintf(ref, sizeof(ref), "%s/CILO%d.EnaOpn.stVal", ld, n);
    bool ena = IedConnection_readBooleanValue(con, &err, ref, IEC61850_FC_ST);
    bool enaOk = (err == IED_ERROR_OK);

    if (p < 0) printf("Chave %d: nao consegui ler (o IED tem o CSWI%d? E a versao nova?)\n", n, n);
    else if (!qOk) printf("Chave %d: posicao desconhecida (nao chega o GOOSE da Pi do servo)\n", n);
    else printf("Chave %d: %s\n", n, textoPos(p, true));
    if (enaOk)
        printf("Intertravamento (CILO%d): %s\n", n, ena ? "LIBERADA (disjuntor aberto)" : "BLOQUEADA");
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Uso:\n"
               "  %s <IP da Pi das telinhas> chave <1-3> [abrir|fechar|ver] [porta]\n"
               "  %s <IP da Pi do servo>     dj    <1-3> [abrir|fechar|ver] [porta]\n", argv[0], argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    bool chave = (strcmp(argv[2], "chave") == 0);
    bool dj = (strcmp(argv[2], "dj") == 0);
    int n = atoi(argv[3]);
    int alvo = 0;
    int porta = 102;
    int prox = 4;                                // proximo argumento a ler
    if (argc > prox) {
        if (strcmp(argv[prox], "abrir") == 0) { alvo = POS_ABERTA; prox++; }
        else if (strcmp(argv[prox], "fechar") == 0) { alvo = POS_FECHADA; prox++; }
        else if (strcmp(argv[prox], "ver") == 0) prox++;
        else if (atoi(argv[prox]) <= 0) { printf("Use abrir, fechar ou ver.\n"); return 1; }
    }
    if (argc > prox) porta = atoi(argv[prox]);
    if ((!chave && !dj) || n < 1 || n > 3) {
        printf("Use 'chave' ou 'dj' e um numero de 1 a 3.\n");
        return 1;
    }

    const char* ld = chave ? "EmpElas_PROTMEDPROT" : "EmpElas_CTRLVAO";
    char ref[128];
    if (chave) snprintf(ref, sizeof(ref), "%s/CSWI%d.Pos", ld, n);
    else       snprintf(ref, sizeof(ref), "%s/XCBR%d.Pos", ld, n);

    IedClientError err;
    IedConnection con = IedConnection_create();
    IedConnection_connect(con, &err, ip, porta);
    if (err != IED_ERROR_OK) {
        printf("Nao conectou em %s:%d (erro %d). O programa do IED esta rodando?\n", ip, porta, err);
        IedConnection_destroy(con);
        return 1;
    }

    int ret = 0;
    if (alvo) {
        ControlObjectClient ctl = ControlObjectClient_create(ref, con);
        if (ctl == NULL) {
            printf("O IED nao tem %s. Confira o IP: chave vai na Pi das telinhas, dj na Pi do servo.\n", ref);
            ret = 1;
        } else {
            MmsValue* v = MmsValue_newBitString(2);
            MmsValue_setBitStringFromInteger(v, alvo);
            ControlObjectClient_setOrigin(ctl, "terminal", 3);
            printf("Pedindo para %s %s %d...\n", alvo == POS_ABERTA ? "ABRIR" : "FECHAR", chave ? "a chave" : "o disjuntor", n);
            if (ControlObjectClient_operate(ctl, v, 0)) {
                printf("Comando ACEITO.\n");
                if (chave) Thread_sleep(1500);   // o servo leva ~0,5 s, mais a ida e volta do GOOSE
                else Thread_sleep(300);
            } else {
                LastApplError e = ControlObjectClient_getLastApplError(ctl);
                printf("Comando RECUSADO: %s (addCause %d).\n", textoAddCause(e.addCause), e.addCause);
                ret = 2;
            }
            MmsValue_delete(v);
            ControlObjectClient_destroy(ctl);
        }
    }

    if (chave) mostrarChave(con, ld, n);
    else {
        int p = lerPos(con, ref, NULL);
        if (p < 0) printf("Disjuntor %d: nao consegui ler.\n", n);
        else printf("Disjuntor %d: %s\n", n, textoPos(p, false));
    }

    IedConnection_close(con);
    IedConnection_destroy(con);
    return ret;
}
