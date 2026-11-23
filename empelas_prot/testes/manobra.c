/*
 * EmPowerElas - manobra pelo terminal (sem o Elipse)
 *
 * Comanda as chaves (CSWI1-3) e os disjuntores (CSWI4-6) pelo IED de
 * controle, na Pi das telinhas, do mesmo jeito que o Elipse faz. Serve para
 * testar o intertravamento e para a demonstracao.
 *
 *   ./testes/manobra <IP da Pi das telinhas> chave <1-3> [abrir|fechar]
 *   ./testes/manobra <IP da Pi das telinhas> dj    <1-3> [abrir|fechar]
 *
 * Sem "abrir" ou "fechar" (ou com "ver"), so mostra o estado. Um numero no
 * fim troca a porta (padrao 102).
 *
 * Formato da norma: o comando e booleano (true = fechar, false = abrir) e a
 * posicao (Dbpos) vem com 01 = aberto e 10 = fechado.
 *
 * Exemplos (IPs do cabo, roteador da maquete):
 *   ./testes/manobra 192.168.10.101 chave 1 abrir
 *   ./testes/manobra 192.168.10.101 dj 1 fechar
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
    case 12: return "ainda esta manobrando";
    default: return "outro motivo (veja o terminal do IED)";
    }
}

// Le uma posicao de ponto duplo no formato da norma. Devolve 0 = em
// movimento, 1 = aberto, 2 = fechado, 3 = invalido; -1 se falhar.
static int lerPos(IedConnection con, const char* ref, bool* qualidadeBoa) {
    IedClientError err;
    char r[128];
    snprintf(r, sizeof(r), "%s.stVal", ref);
    MmsValue* v = IedConnection_readObject(con, &err, r, IEC61850_FC_ST);
    if (err != IED_ERROR_OK || v == NULL) return -1;
    int p = (MmsValue_getType(v) == MMS_BIT_STRING) ? (int) Dbpos_fromMmsValue(v) : -1;
    MmsValue_delete(v);
    if (qualidadeBoa) {
        snprintf(r, sizeof(r), "%s.q", ref);
        Quality q = IedConnection_readQualityValue(con, &err, r, IEC61850_FC_ST);
        *qualidadeBoa = (err == IED_ERROR_OK) && (Quality_getValidity(&q) == QUALITY_VALIDITY_GOOD);
    }
    return p;
}

// Chave N = CSWI/CILO N; disjuntor N = CSWI/CILO N+3
static void mostrar(IedConnection con, const char* ld, bool chave, int n) {
    IedClientError err;
    char ref[128];
    bool qOk = false;
    int k = chave ? n : n + 3;
    const char* nome = chave ? "Chave" : "Disjuntor";
    snprintf(ref, sizeof(ref), "%s/CSWI%d.Pos", ld, k);
    int p = lerPos(con, ref, &qOk);
    if (p < 0) printf("%s %d: nao consegui ler (o IED tem o CSWI%d? E a versao nova?)\n", nome, n, k);
    else if (!qOk) printf("%s %d: posicao desconhecida (nao chega o GOOSE da Pi do servo)\n", nome, n);
    else printf("%s %d: %s\n", nome, n, textoPos(p, chave));

    // Chave: abrir e fechar liberam juntos. Disjuntor: abre sempre, o que importa e o fechar.
    snprintf(ref, sizeof(ref), "%s/CILO%d.%s.stVal", ld, k, chave ? "EnaOpn" : "EnaCls");
    bool ena = IedConnection_readBooleanValue(con, &err, ref, IEC61850_FC_ST);
    if (err == IED_ERROR_OK) {
        if (chave) printf("Intertravamento (CILO%d): %s\n", k, ena ? "LIBERADA (disjuntor aberto)" : "BLOQUEADA");
        else       printf("Intertravamento (CILO%d): fechar %s\n", k, ena ? "LIBERADO" : "BLOQUEADO");
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Uso:\n"
               "  %s <IP da Pi das telinhas> chave <1-3> [abrir|fechar|ver] [porta]\n"
               "  %s <IP da Pi das telinhas> dj    <1-3> [abrir|fechar|ver] [porta]\n", argv[0], argv[0]);
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

    const char* ld = "EmpElas_PROTMEDPROT";
    char ref[128];
    snprintf(ref, sizeof(ref), "%s/CSWI%d.Pos", ld, chave ? n : n + 3);

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
            printf("O IED nao tem %s. Confira o IP: chaves e disjuntores sao comandados na Pi das telinhas.\n", ref);
            ret = 1;
        } else {
            MmsValue* v = MmsValue_newBoolean(alvo == POS_FECHADA);   // true = fechar
            ControlObjectClient_setOrigin(ctl, "terminal", 3);
            printf("Pedindo para %s %s %d...\n", alvo == POS_ABERTA ? "ABRIR" : "FECHAR", chave ? "a chave" : "o disjuntor", n);
            if (ControlObjectClient_operate(ctl, v, 0)) {
                printf("Comando ACEITO.\n");
                if (chave) Thread_sleep(2200);   // o servo leva 1,5 s, mais a ida e volta do GOOSE
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

    mostrar(con, ld, chave, n);

    IedConnection_close(con);
    IedConnection_destroy(con);
    return ret;
}
