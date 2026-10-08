/*
 * Derruba ou retira a "arvore" da merging unit pelo terminal, sem o Elipse.
 * Faz o mesmo que o comando FLTGGIO1.SPCSO1 do supervisorio.
 *
 * Uso (de qualquer Pi ou computador na mesma rede da MU):
 *   ./testes/falta <ip-da-MU> 1     a arvore cai (falta na fase A)
 *   ./testes/falta <ip-da-MU> 0     a arvore e retirada
 *   ./testes/falta <ip-da-MU>       so mostra o estado atual
 *
 * Compilar (na pasta empelas_mu):  make testes
 */
#include "iec61850_client.h"
#include "hal_thread.h"
#include <stdio.h>
#include <stdlib.h>

#define REF_FALTA "EmpElas_MUMU01/FLTGGIO1.SPCSO1"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s <ip-da-MU> [1|0] [porta]\n", argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    int porta = (argc > 3) ? atoi(argv[3]) : 102;

    IedClientError erro;
    IedConnection con = IedConnection_create();
    IedConnection_connect(con, &erro, ip, porta);
    if (erro != IED_ERROR_OK) {
        printf("Nao consegui conectar na MU em %s:%d (erro %d).\n", ip, porta, erro);
        IedConnection_destroy(con);
        return 1;
    }

    if (argc > 2) {
        bool aplicar = (argv[2][0] == '1');
        ControlObjectClient ctl = ControlObjectClient_create(REF_FALTA, con);
        if (ctl == NULL) {
            printf("Nao achei %s nessa MU.\n", REF_FALTA);
        } else {
            ControlObjectClient_setOrigin(ctl, "terminal", 3);
            MmsValue* valor = MmsValue_newBoolean(aplicar);
            if (ControlObjectClient_operate(ctl, valor, 0))
                printf("Comando enviado: %s\n", aplicar ? "a arvore caiu (falta)" : "arvore retirada");
            else
                printf("A MU recusou o comando.\n");
            MmsValue_delete(valor);
            ControlObjectClient_destroy(ctl);
        }
        Thread_sleep(300);   // a MU executa o comando logo depois de aceitar
    }

    bool estado = IedConnection_readBooleanValue(con, &erro, REF_FALTA ".stVal", IEC61850_FC_ST);
    if (erro == IED_ERROR_OK)
        printf("Arvore na linha: %s\n", estado ? "SIM (falta na fase A)" : "nao (linha normal)");
    else
        printf("Nao consegui ler o estado (erro %d).\n", erro);

    IedConnection_close(con);
    IedConnection_destroy(con);
    return 0;
}
