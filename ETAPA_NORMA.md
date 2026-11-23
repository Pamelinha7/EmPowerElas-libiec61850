# Etapa: maquete no formato da norma

Esta etapa deixa a maquete mais perto da IEC 61850 em quatro pontos. As três Pis precisam ser atualizadas juntas: as mensagens mudaram de formato, e uma Pi na versão antiga não entende a outra.

## O que mudou

1. **Proteção: PIOC no lugar do PTOC.** A sobrecorrente da maquete atua sem atraso, e na norma isso é o PIOC (função 50). O PTOC é a temporizada (função 51). Mudou só o nome do nó lógico. (Depois, o ajuste passou de 300 A para 600 A: ver ETAPA_VALORES.md.)
2. **Disjuntores comandados pelo IED de controle.** O operador comanda os disjuntores no CSWI4, CSWI5 e CSWI6 da PROT, como já fazia com as chaves (CSWI1-3). O comando sai por GOOSE (gcbCmd, agora com 12 valores) para a CTRL. O XCBR da CTRL ficou só mostrando a posição (status-only). O trip continua indo direto do PTRC para o XCBR1, sem passar pelo CSWI.
3. **Intertravamento dos disjuntores (CILO4-6).** O disjuntor abre sempre. Ele só fecha se a chave do mesmo vão estiver parada, aberta ou fechada, e nunca no meio do caminho. O DJ1 também não fecha enquanto o trip estiver ativo.
4. **Posição e comando no formato da norma.**
   - Posição (Dbpos): 01 = aberto, 10 = fechado, 00 = em movimento, 11 = inválido. Antes os dois bits estavam na ordem contrária.
   - Comando (ctlVal): booleano, true = fechar e false = abrir. Antes era 1 = abrir e 2 = fechar.

Também entram aqui as mudanças anteriores que ainda não estavam no repositório:

- a MU zera as correntes com o vão 1 aberto;
- a PROT mostra `ULTIMO TRIP` no LCD1 até o DJ1 fechar de novo;
- a chave 1 abre sozinha 2 s depois do trip (`CHAVE_AUTO_NA_FALTA` no `server_ctrl.c`);
- as fitas novas (SV branco, GOOSE amarelo, cobre).

## Arquivos de cada Pi

| Pi | Arquivos |
| --- | --- |
| PROT (telinhas) | `empelas_prot/empelas_prot.icd`, `static_model.c`, `static_model.h`, `server_prot.c`, `testes/manobra.c`, `testes/ver_eventos.c`, `testes/ver_goose.c` |
| CTRL (servo) | `empelas_ctrl/empelas_ctrl.icd`, `static_model.c`, `static_model.h`, `server_ctrl.c` |
| MU | `empelas_mu/server_mu.c` (o `.icd` da MU não mudou) |

## Como atualizar

Em cada Pi:

1. Pare o programa (Ctrl+C).
2. Copie os arquivos da tabela por cima dos antigos, na mesma pasta.
3. Compile com `make`. Na PROT, rode também `make testes`.
4. Rode o programa do jeito de sempre.

Se o `make` disser que vai gerar o modelo de novo (`java -jar ... genmodel.jar`), tudo bem: ele gera o mesmo `static_model.c` que já veio pronto.

Se aparecer `formato inesperado` no terminal da PROT ou da CTRL, uma das Pis ficou na versão antiga.

## Elipse: o que trocar nas telas

| Para quê | Antes | Agora |
| --- | --- | --- |
| Comandar o DJ1 | CTRL `XCBR1$CO$Pos$Oper`, valor 1 (abrir) ou 2 (fechar) | PROT `CSWI4$CO$Pos$Oper`, valor **0 (abrir) ou 1 (fechar)** |
| Comandar o DJ2 e o DJ3 | CTRL `XCBR2` e `XCBR3` | PROT `CSWI5` e `CSWI6` |
| Comandar as chaves 1-3 | PROT `CSWI1-3$CO$Pos$Oper`, valor 1 ou 2 | mesmo tag, valor **0 (abrir) ou 1 (fechar)** |
| Posição dos disjuntores | CTRL `XCBR1$ST$Pos$stVal` | o mesmo, ou PROT `CSWI4$ST$Pos$stVal` |
| Cadeado do fechar dos disjuntores | não existia | PROT `CILO4$ST$EnaCls$stVal` (CILO5 e CILO6 para DJ2 e DJ3) |
| Atuação da proteção | PROT `PTOC1$ST$Op$general` e `PTOC1$ST$Str$general` | PROT `PIOC1$ST$Op$general` e `PIOC1$ST$Str$general` |

**Confira os números da posição no Elipse.** Como os bits mudaram de ordem, o Elipse pode passar a mostrar o aberto com o número que antes era do fechado. Feche o DJ1 e veja o valor do `XCBR1$ST$Pos$stVal` no Elipse:

- se aparecer o mesmo número de antes para fechado, nada muda nas telas;
- se aparecer o outro número, troque as cores e os textos de 1 e 2 nas animações de posição.

Depois de trocar os tags, faça de novo a leitura dos dados do IED no driver, porque o modelo da PROT ganhou nós novos.

## Teste rápido pelo terminal (na PROT)

```
cd ~/EmPowerElas-libiec61850/empelas_prot
./testes/manobra 192.168.10.101 dj 1 fechar      # ACEITO: LED vermelho, MU passa a uns 250 A
./testes/manobra 192.168.10.101 chave 1 abrir    # RECUSADO: intertravamento (addCause 10)
./testes/manobra 192.168.10.101 dj 1 abrir       # ACEITO
./testes/manobra 192.168.10.101 chave 1 abrir    # ACEITO: o servo levanta a chave
./testes/manobra 192.168.10.101 dj 1 ver         # mostra a posição e o CILO4
```

O `./testes/ver_eventos` mostra os eventos das três Pis em ordem, já no formato novo.

## Wireshark

- No `gcbPos`, a posição aparece com os bits da norma: `01` para aberto e `10` para fechado.
- O `gcbCmd` agora tem 12 valores: abrir e fechar de cada chave, depois de cada disjuntor.

## Testado

As três Pis foram compiladas e rodadas juntas num computador, numa rede virtual com um switch, contra a libiec61850 1.6.2. Funcionaram:

- SV e os três GOOSE;
- comandos pelo CSWI e intertravamento das chaves e dos disjuntores;
- a falta, com trip e corrente indo a zero;
- a chave 1 abrindo sozinha;
- religar em cima da falta (trip de novo);
- o relatório de eventos.

Ainda falta o teste na maquete de verdade.
