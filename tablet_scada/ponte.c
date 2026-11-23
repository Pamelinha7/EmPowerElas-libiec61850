/*
 * EmPowerElas - ponte MMS do SCADA do tablet
 *
 * O navegador do tablet nao fala MMS. Este programinha fala: ele abre uma
 * conexao MMS com UM IED e fica esperando pedidos simples, um por linha,
 * na entrada padrao. A resposta sai na saida padrao, tambem uma por linha.
 * Quem conversa com ele e o servidor.py (um processo da ponte por IED).
 *
 *   ./ponte <IP do IED> [porta]
 *
 * Pedidos (os campos sao separados por espaco):
 *
 *   LEV fc ref qref;fc ref qref;...   le varios atributos de uma vez
 *        fc   = ST, MX, CF, SP...
 *        ref  = referencia do atributo, ex. EmpElas_CTRLVAO/XCBR1.Pos.stVal
 *        qref = referencia da qualidade (ex. ...XCBR1.Pos.q) ou "-" se nao tiver
 *      resposta: R item;item;...   cada item e "tipo valor qualidade" ou "E codigo"
 *        tipo: b (booleano) i (inteiro) u (sem sinal) f (real) s (texto)
 *              d (posicao de ponto duplo, ja convertida pela norma:
 *                 0 = em movimento, 1 = aberto, 2 = fechado, 3 = invalida)
 *        qualidade: g (boa) i (invalida) q (duvidosa) - (sem qualidade)
 *
 *   OP tipo ref valor [origem]        comanda (Oper) um objeto de controle
 *        tipo: d (posicao: 1 = abrir, 2 = fechar, convencao do projeto;
 *                 a ponte monta o ctlVal no tipo que o IED pede: booleano
 *                 true = fechar, como manda a norma, ou ponto duplo)
 *              b (booleano: 0 ou 1)  i (inteiro)  f (real)
 *        ref:  o objeto de dados, ex. EmpElas_CTRLVAO/XCBR1.Pos
 *      resposta: OK  ou  NEG addCause erro
 *
 *   LISTA                             lista todas as variaveis do IED
 *      resposta: L nome nome nome...  (no formato MMS, ex. VAO/XCBR1$ST$Pos$stVal)
 *
 * Se o IED nao estiver conectado, a resposta e "X" e a ponte tenta
 * reconectar no proximo pedido (no maximo a cada 2 s).
 */

#include "iec61850_client.h"
#include "hal_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static IedConnection con = NULL;
static const char* ipIed;
static int portaIed = 102;
static uint64_t ultimaTentativa = 0;

static bool garantirConexao(void)
{
    if (con && IedConnection_getState(con) == IED_STATE_CONNECTED)
        return true;

    uint64_t agora = Hal_getTimeInMs();
    if (ultimaTentativa != 0 && agora - ultimaTentativa < 2000)
        return false;
    ultimaTentativa = agora;

    if (con) {
        IedConnection_destroy(con);
        con = NULL;
    }
    con = IedConnection_create();
    IedConnection_setConnectTimeout(con, 1500);
    IedConnection_setRequestTimeout(con, 1500);

    IedClientError err;
    IedConnection_connect(con, &err, ipIed, portaIed);
    if (err != IED_ERROR_OK) {
        fprintf(stderr, "[ponte %s] nao conectou (erro %d)\n", ipIed, err);
        return false;
    }
    fprintf(stderr, "[ponte %s] conectado\n", ipIed);
    return true;
}

static FunctionalConstraint fcDoTexto(const char* t)
{
    FunctionalConstraint fc = FunctionalConstraint_fromString(t);
    return fc;
}

/* Escreve "tipo valor" de um MmsValue no buffer. Devolve false se o tipo
 * nao for suportado. */
static bool formatarValor(MmsValue* v, char* buf, size_t tam)
{
    switch (MmsValue_getType(v)) {
    case MMS_BOOLEAN:
        snprintf(buf, tam, "b %d", MmsValue_getBoolean(v) ? 1 : 0);
        return true;
    case MMS_INTEGER:
        snprintf(buf, tam, "i %lld", (long long) MmsValue_toInt64(v));
        return true;
    case MMS_UNSIGNED:
        snprintf(buf, tam, "u %u", MmsValue_toUint32(v));
        return true;
    case MMS_FLOAT:
        snprintf(buf, tam, "f %.6g", MmsValue_toDouble(v));
        return true;
    case MMS_BIT_STRING:
        /* posicao (Dbpos): 2 bits no formato da norma, 01 = aberto e
         * 10 = fechado. Dbpos_fromMmsValue devolve 1 = aberto (OFF),
         * 2 = fechado (ON), 0 = em movimento, 3 = invalida. */
        if (MmsValue_getBitStringSize(v) == 2)
            snprintf(buf, tam, "d %d", (int) Dbpos_fromMmsValue(v));
        else
            snprintf(buf, tam, "u %u", MmsValue_getBitStringAsInteger(v));
        return true;
    case MMS_VISIBLE_STRING:
    case MMS_STRING: {
        const char* s = MmsValue_toString(v);
        size_t n = 0;
        n += snprintf(buf, tam, "s ");
        for (; s && *s && n + 2 < tam; s++)
            buf[n++] = (*s == ' ' || *s == ';' || *s == '\n') ? '_' : *s;
        buf[n] = 0;
        return true;
    }
    default:
        return false;
    }
}

static char qualidadeLetra(Quality q)
{
    switch (Quality_getValidity(&q)) {
    case QUALITY_VALIDITY_GOOD:
        return 'g';
    case QUALITY_VALIDITY_INVALID:
        return 'i';
    default:
        return 'q';
    }
}

/* "fc ref qref" -> "tipo valor q" ou "E codigo" */
static void lerItem(char* item, char* saida, size_t tam)
{
    char fcTxt[8], ref[160], qref[160];
    if (sscanf(item, "%7s %159s %159s", fcTxt, ref, qref) != 3) {
        snprintf(saida, tam, "E sintaxe");
        return;
    }
    IedClientError err;
    MmsValue* v = IedConnection_readObject(con, &err, ref, fcDoTexto(fcTxt));
    if (err != IED_ERROR_OK || v == NULL) {
        snprintf(saida, tam, "E %d", err);
        return;
    }
    char val[96];
    if (MmsValue_getType(v) == MMS_DATA_ACCESS_ERROR) {
        MmsValue_delete(v);
        snprintf(saida, tam, "E inexistente");
        return;
    }
    if (!formatarValor(v, val, sizeof(val))) {
        MmsValue_delete(v);
        snprintf(saida, tam, "E tipo");
        return;
    }
    MmsValue_delete(v);

    char q = '-';
    if (strcmp(qref, "-") != 0) {
        Quality qual = IedConnection_readQualityValue(con, &err, qref, fcDoTexto(fcTxt));
        q = (err == IED_ERROR_OK) ? qualidadeLetra(qual) : '-';
    }
    snprintf(saida, tam, "%s %c", val, q);
}

static void pedidoLer(char* lista)
{
    static char resposta[16384];
    size_t n = 0;
    n += snprintf(resposta + n, sizeof(resposta) - n, "R ");
    char* salvo = NULL;
    bool primeiro = true;
    for (char* item = strtok_r(lista, ";", &salvo); item; item = strtok_r(NULL, ";", &salvo)) {
        char saida[160];
        lerItem(item, saida, sizeof(saida));
        if (n + strlen(saida) + 2 >= sizeof(resposta))
            break;
        n += snprintf(resposta + n, sizeof(resposta) - n, "%s%s", primeiro ? "" : ";", saida);
        primeiro = false;
    }
    printf("%s\n", resposta);
}

static void pedidoOperar(char* args)
{
    char tipo[4], ref[160], valor[32], origem[32] = "tablet";
    if (sscanf(args, "%3s %159s %31s %31s", tipo, ref, valor, origem) < 3) {
        printf("NEG 0 sintaxe\n");
        return;
    }
    ControlObjectClient ctl = ControlObjectClient_create(ref, con);
    if (ctl == NULL) {
        printf("NEG 0 objeto_inexistente\n");
        return;
    }
    MmsValue* v;
    switch (tipo[0]) {
    case 'd': {
        int pos = atoi(valor);
        if (pos != 1 && pos != 2) {
            printf("NEG 6 valor_invalido\n");
            ControlObjectClient_destroy(ctl);
            return;
        }
        if (ControlObjectClient_getCtlValType(ctl) == MMS_BIT_STRING)
            v = Dbpos_toMmsValue(NULL, pos == 2 ? DBPOS_ON : DBPOS_OFF);
        else
            v = MmsValue_newBoolean(pos == 2);   /* norma: true = fechar */
        break;
    }
    case 'b':
        v = MmsValue_newBoolean(atoi(valor) != 0);
        break;
    case 'f':
        v = MmsValue_newFloat((float) atof(valor));
        break;
    default:
        v = MmsValue_newIntegerFromInt32(atoi(valor));
        break;
    }
    ControlObjectClient_setOrigin(ctl, origem, 3);

    /* select-before-operate: se o objeto pedir, seleciona antes */
    ControlModel modelo = ControlObjectClient_getControlModel(ctl);
    bool ok = true;
    if (modelo == CONTROL_MODEL_SBO_NORMAL)
        ok = ControlObjectClient_select(ctl);
    else if (modelo == CONTROL_MODEL_SBO_ENHANCED)
        ok = ControlObjectClient_selectWithValue(ctl, v);

    if (ok)
        ok = ControlObjectClient_operate(ctl, v, 0);

    if (ok) {
        printf("OK\n");
    } else {
        LastApplError e = ControlObjectClient_getLastApplError(ctl);
        printf("NEG %d %d\n", e.addCause, e.error);
    }
    MmsValue_delete(v);
    ControlObjectClient_destroy(ctl);
}

static void pedidoListar(void)
{
    IedClientError err;
    LinkedList lds = IedConnection_getLogicalDeviceList(con, &err);
    if (err != IED_ERROR_OK) {
        printf("L\n");
        return;
    }
    printf("L");
    for (LinkedList ld = LinkedList_getNext(lds); ld; ld = LinkedList_getNext(ld)) {
        const char* nomeLd = (const char*) LinkedList_getData(ld);
        LinkedList vars = IedConnection_getLogicalDeviceVariables(con, &err, nomeLd);
        if (err != IED_ERROR_OK)
            continue;
        for (LinkedList x = LinkedList_getNext(vars); x; x = LinkedList_getNext(x))
            printf(" %s/%s", nomeLd, (const char*) LinkedList_getData(x));
        LinkedList_destroy(vars);
    }
    LinkedList_destroy(lds);
    printf("\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <IP do IED> [porta]\n", argv[0]);
        return 1;
    }
    ipIed = argv[1];
    if (argc > 2)
        portaIed = atoi(argv[2]);

    setvbuf(stdout, NULL, _IOLBF, 0);

    static char linha[16384];
    while (fgets(linha, sizeof(linha), stdin)) {
        linha[strcspn(linha, "\r\n")] = 0;
        if (linha[0] == 0)
            continue;

        if (!garantirConexao()) {
            printf("X\n");
            continue;
        }

        if (strncmp(linha, "LEV ", 4) == 0)
            pedidoLer(linha + 4);
        else if (strncmp(linha, "OP ", 3) == 0)
            pedidoOperar(linha + 3);
        else if (strcmp(linha, "LISTA") == 0)
            pedidoListar();
        else if (strcmp(linha, "PING") == 0)
            printf("PONG\n");
        else
            printf("? %s\n", linha);
    }

    if (con) {
        IedConnection_close(con);
        IedConnection_destroy(con);
    }
    return 0;
}
