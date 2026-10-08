# Etapa das chaves: intertravamento por GOOSE

Até agora, o Elipse mandava direto no servo da chave. Nada impedia alguém de abrir uma chave seccionadora com o disjuntor fechado.

Nesta etapa, o pedido do operador vai para o **IED de controle** (Pi das telinhas). Ele confere se a manobra é segura e só então manda a ordem para a Pi do servo, **por GOOSE**. A Pi do servo, por sua vez, avisa por GOOSE a posição de todos os disjuntores e chaves. É assim que o IED de controle sabe o que está aberto.

Os disjuntores continuam sendo comandados pelo Elipse direto na Pi do servo, como antes. A MU não muda.

Junto vai a configuração da fita nova de 12 V (seção 11).

---

## 1. Como fica a maquete

```
                       Elipse (wi-fi do laboratório, MMS)
                      chaves │                 │ disjuntores
                             ▼                 ▼
EmpElas_MU ── SV ──► EmpElas_PROT ── GOOSE trip ─────────────► EmpElas_CTRL
(linha, TC, TP)      (telinhas)    ── GOOSE comando das chaves ► (servo)
                     CSWI + CILO   ◄─ GOOSE posições ──────────
       └──────────────────── cabo, roteador da maquete ─────────────┘
```

Mensagens que passam pelo cabo:

| Mensagem | De → para | MAC de destino | APPID | O que leva |
|---|---|---|---|---|
| SV | MU → telinhas | 01-0C-CD-04-00-01 | 0x4000 | correntes e tensões |
| GOOSE `gcbTrip` | telinhas → servo | 01-0C-CD-01-00-01 | 0x1001 | o trip |
| GOOSE `gcbCmd` (nova) | telinhas → servo | 01-0C-CD-01-00-03 | 0x1003 | abrir ou fechar cada chave |
| GOOSE `gcbPos` (nova) | servo → telinhas | 01-0C-CD-01-00-02 | 0x1002 | posição dos 3 disjuntores e das 3 chaves |

| Pi | O que muda |
|---|---|
| EmpElas_PROT (telinhas) | ganha CSWI1-3 e CILO1-3, publica `gcbCmd`, assina `gcbPos`, mostra avisos das chaves no LCD2 |
| EmpElas_CTRL (servo) | publica `gcbPos`, assina `gcbCmd`; as chaves não aceitam mais comando direto do Elipse |
| EmpElas_MU | nada |

---

## 2. A regra do intertravamento

A chave seccionadora não foi feita para cortar corrente: ela não tem como apagar o arco elétrico que aparece quando um circuito com carga é aberto. Quem corta corrente é o disjuntor. Por isso a ordem certa é **abrir o disjuntor primeiro e só depois a chave**. Para religar, é ao contrário: fecha a chave e depois o disjuntor.

Na maquete, a **chave N pertence ao vão do disjuntor N** (chave 1 com disjuntor 1, e assim por diante). A regra:

| Situação | O que acontece |
|---|---|
| Disjuntor N aberto | a chave N pode abrir e fechar |
| Disjuntor N fechado | comando recusado. LCD2: `CH1 BLOQUEADA` / `ABRA O DJ1 ANTES` |
| Posições da Pi do servo não chegam há 3 s | todas as chaves bloqueadas. LCD2: `SEM POSICOES` |
| A chave já está na posição pedida | comando recusado. LCD2: `CH1 JA ABERTA` |
| A chave ainda está se mexendo | comando recusado |

Sem saber onde está o disjuntor, o IED de controle não arrisca: bloqueia. É melhor bloquear do que deixar abrir uma chave com carga.

Os disjuntores não têm restrição: podem abrir e fechar a qualquer hora, inclusive pelo trip.

---

## 3. Os nós lógicos novos

| Nó lógico | Onde | O que faz |
|---|---|---|
| `CSWI1`, `CSWI2`, `CSWI3` | Pi das telinhas | Controlador da chave. Recebe o pedido do operador e, se liberado, liga o sinal `OpOpn` (abrir) ou `OpCls` (fechar), que vai no GOOSE `gcbCmd`. O `CSWI.Pos` mostra a posição da chave que chegou por GOOSE. |
| `CILO1`, `CILO2`, `CILO3` | Pi das telinhas | O intertravamento. `EnaOpn` = pode abrir, `EnaCls` = pode fechar. Verdadeiro = liberada. |
| `XSWI1`, `XSWI2`, `XSWI3` | Pi do servo | A chave física (servo). Só mostra a posição: o comando chega pelo GOOSE. `OpCnt` conta as manobras. |

É o mesmo desenho do trip. No trip, o PTRC decide, o GOOSE leva e o XCBR executa. Aqui, o CSWI decide (com a liberação do CILO), o GOOSE leva e o XSWI executa.

### Uma manobra, passo a passo

1. O operador clica em "abrir chave 1" no Elipse. O pedido vai por MMS para o `CSWI1` da Pi das telinhas.
2. A Pi das telinhas confere o `CILO1`: o disjuntor 1 está aberto? (Ela sabe disso pelo GOOSE `gcbPos`.)
3. Liberado: o `CSWI1.OpOpn` vira verdadeiro e o GOOSE `gcbCmd` sai na hora. LCD2: `CH1 ABRINDO...`.
4. A Pi do servo recebe, confere mais uma vez se o disjuntor 1 continua aberto, mostra o rastro âmbar na fita e mexe o servo. Enquanto ele se mexe (cerca de 0,5 s), publica a chave como **em movimento** (posição 0), como uma chave real a caminho.
5. O servo termina e a Pi do servo publica a chave como **aberta** no `gcbPos`.
6. A Pi das telinhas vê a chave aberta, desliga o `OpOpn` e mostra `CH1 ABERTA` / `CONFIRMADO`. Se a chave não chegar em 3 s, ela desliga o sinal do mesmo jeito e avisa `CH1 SEM RESPOSTA`.

No teste feito aqui, do clique à confirmação deu cerca de 520 ms. Quase tudo é o tempo do servo.

---

## 4. Atualizar os arquivos

Os arquivos vão **só para a Pi das telinhas**. De lá, sobem para o GitHub, e a Pi do servo baixa com `git pull`.

**4.1.** Na Pi das telinhas, confira se o repositório está limpo e atualizado:
```
cd ~/EmPowerElas-libiec61850
git status
```
Tem que aparecer `nothing to commit, working tree clean`. Se aparecer algum arquivo modificado, pare e me mande a saída.

**4.2.** Ainda na Pi das telinhas:
```
git pull
```

**4.3.** Pelo VS Code, arraste o **conteúdo** da pasta `etapa_chaves` (não a pasta em si) para dentro de `~/EmPowerElas-libiec61850` e aceite substituir. São estes arquivos:

```
ETAPA_CHAVES.md
.gitignore
INSTALACAO.md
empelas_ctrl/Makefile
empelas_ctrl/empelas_ctrl.icd
empelas_ctrl/server_ctrl.c
empelas_ctrl/static_model.c
empelas_ctrl/testes/teste_fita.c
empelas_prot/Makefile
empelas_prot/empelas_prot.icd
empelas_prot/server_prot.c
empelas_prot/static_model.c
empelas_prot/static_model.h
empelas_prot/testes/manobra.c
```
O `.gitignore` começa com ponto e pode ficar escondido no explorador de arquivos. Se ele não for junto, tudo funciona igual (o passo 4.7 já evita mandar o programa compilado para o GitHub).

**4.4.** Confira:
```
git status
```
Devem aparecer como `modified` os 11 arquivos que já existiam e, como novos (`Untracked`), o `ETAPA_CHAVES.md`, o `empelas_ctrl/testes/teste_fita.c` e a pasta `empelas_prot/testes/`. Nada além disso.

**4.5.** Compile a Pi das telinhas:
```
cd ~/EmPowerElas-libiec61850/empelas_prot
make
```
Não precisa de `make modelo`: os arquivos do modelo (`static_model.c` e `.h`) já vão prontos.

**4.6.** Compile a ferramenta de teste:
```
make testes
```

**4.7.** Mande para o GitHub, para a Pi do servo poder baixar. Primeiro os arquivos que já existiam (o `-u` pega só os modificados):
```
cd ~/EmPowerElas-libiec61850
git add -u
```
Depois os três novos (os `.c`, não os programas compilados):
```
git add ETAPA_CHAVES.md empelas_prot/testes/manobra.c empelas_ctrl/testes/teste_fita.c
```
E o commit:
```
git commit -m "Chaves comandadas pelo IED de controle (CSWI e CILO) por GOOSE"
git push
```
Se algo der errado nos testes, a gente corrige e faz outro commit.

**4.8.** Na **Pi do servo**:
```
cd ~/EmPowerElas-libiec61850
git status
```
Também tem que estar limpo. Se aparecer o `server_ctrl.c` modificado, pare e me mande a saída antes de continuar (pode ter algum ajuste local, como o número de pixels da fita).

**4.9.** Ainda na Pi do servo:
```
git pull
cd empelas_ctrl
make
```
Se a fita nova já estiver ligada, faça agora a seção 11 (é rápido) e depois volte para a seção 5.

---

## 5. Rodar

A ordem não importa. Cada uma no seu terminal, como antes.

Pi do servo:
```
sudo ./empelas_ctrl
```
Saída esperada (além das linhas de servo e fita):
```
--- EmpElas_CTRL : PATIO (disjuntores, chaves e fita) ---
[GOOSE] Publicando gcbPos em eth0 (APPID 0x1002): posicao dos 3 disjuntores e das 3 chaves.
[GOOSE] Escutando o trip em eth0 (APPID 0x1001). Abre: Disjuntor 1 (XCBR1).
[GOOSE] Escutando os comandos das chaves em eth0 (APPID 0x1003).
[STATUS] Chaves fechadas, disjuntores abertos. Chaves so por GOOSE; disjuntores pelo SCADA.
[GOOSE] Assinatura do trip ativa (stNum=1, sem trip).
[GOOSE] Assinatura dos comandos das chaves ativa (stNum=1).
```
As duas últimas linhas só aparecem quando a Pi das telinhas está rodando.

Pi das telinhas:
```
cd ~/EmPowerElas-libiec61850/empelas_prot
sudo ./empelas_prot
```
Saída esperada (além das linhas de SV e proteção):
```
[GOOSE]  Publicando gcbCmd em eth0 (APPID 0x1003): comandos das chaves.
[GOOSE]  Assinando gcbPos em eth0 (APPID 0x1002): posicoes da Pi do servo. Aguardando...
[CHAVES] CSWI1-3 com intertravamento (CILO1-3): chave N so manobra com o disjuntor N aberto.
[GOOSE] Patio (stNum=1): DJ1 aberto, DJ2 aberto, DJ3 aberto | CH1 fechada, CH2 fechada, CH3 fechada
[GOOSE] Recebendo as posicoes da Pi do servo (gcbPos). Intertravamento ativo.
```
Toda vez que um disjuntor ou chave mudar, aparece uma linha `[GOOSE] Patio (...)` nova. É o GOOSE de posições chegando.

---

## 6. Teste pelo terminal (antes do Elipse)

Use um **segundo terminal na Pi das telinhas**. A ferramenta `manobra` faz o mesmo que os botões do Elipse:

- `./testes/manobra 192.168.10.101 chave N abrir|fechar` → manda na chave pelo IED de controle;
- `./testes/manobra 192.168.10.100 dj N abrir|fechar` → manda no disjuntor, direto na Pi do servo;
- sem `abrir` ou `fechar`, só mostra o estado.

O roteiro abaixo é a própria história da demonstração. Rode um bloco de cada vez.

**6.1. Fecha o disjuntor 1** (linha energizada):
```
cd ~/EmPowerElas-libiec61850/empelas_prot
./testes/manobra 192.168.10.100 dj 1 fechar
```
Esperado: `Comando ACEITO.` e `Disjuntor 1: fechado`.

**6.2. Tenta abrir a chave 1 com o disjuntor fechado:**
```
./testes/manobra 192.168.10.101 chave 1 abrir
```
Esperado:
```
Comando RECUSADO: bloqueado pelo intertravamento (addCause 10).
Chave 1: fechada
Intertravamento (CILO1): BLOQUEADA
```
No LCD2: `CH1 BLOQUEADA` / `ABRA O DJ1 ANTES`. O servo não mexe. No terminal da Pi das telinhas:
`[INTERTRAVAMENTO] Pedido de ABRIR a chave 1 RECUSADO: o disjuntor 1 esta fechado. Abra o disjuntor 1 antes.`

**6.3. A árvore cai:** pelo botão da MU, pelo Elipse ou pelo `./testes/falta <IP da MU> 1`, como na etapa do SV. O trip abre o disjuntor 1, e o terminal da Pi das telinhas mostra `[INTERTRAVAMENTO] Chave 1 liberada (disjuntor 1 aberto).`

**6.4. Agora a chave 1 abre** (isolando a linha para a equipe tirar a árvore):
```
./testes/manobra 192.168.10.101 chave 1 abrir
```
Esperado: `Comando ACEITO.` e `Chave 1: aberta`. O servo mexe, a fita mostra o rastro âmbar, e o LCD2 mostra `CH1 ABRINDO...` e depois `CH1 ABERTA` / `CONFIRMADO`.

**6.5. Retira a árvore, fecha a chave e depois o disjuntor.** Primeiro a chave:
```
./testes/manobra 192.168.10.101 chave 1 fechar
```
Depois o disjuntor:
```
./testes/manobra 192.168.10.100 dj 1 fechar
```

**6.6. Tira o cabo da Pi do servo.** Em até 3 s, a Pi das telinhas mostra `Sem as posicoes da Pi do servo` e o LCD2 mostra `SEM POSICOES`. Qualquer comando de chave é recusado. Recoloque o cabo e tudo volta sozinho em cerca de 1 s.

---

## 7. Elipse

Os dois modelos mudaram. **Refaça a leitura dos dados** da Pi das telinhas e da Pi do servo no Elipse.

**Botões das chaves.** Hoje eles apontam para a Pi do servo. Troque o dispositivo e o nó lógico, mantendo o resto do caminho igual ao que vocês já usam:

| Antes | Depois |
|---|---|
| `EmpElas_CTRLVAO` → `XSWI1$CO$Pos$Oper...` | `EmpElas_PROTMEDPROT` → `CSWI1$CO$Pos$Oper...` |

Os valores continuam os mesmos: **1 = abrir, 2 = fechar**. O mesmo vale para as chaves 2 e 3.

Botão que continuar apontando para o `XSWI` da Pi do servo vai dar erro: lá as chaves agora só mostram a posição.

**Posição das chaves.** Pode continuar lendo `XSWI1$ST$Pos$stVal` na Pi do servo. Outra opção é ler `CSWI1$ST$Pos$stVal` na Pi das telinhas: é a mesma posição, que chegou por GOOSE. A qualidade (`CSWI1$ST$Pos$q`) fica inválida quando o GOOSE para de chegar.

Durante a manobra (cerca de 0,5 s), a posição passa por **0 (em movimento)**. Se a animação do Elipse não tiver um estado para 0, ela pode piscar nesse meio-tempo.

**Tags novas** (Pi das telinhas, `EmpElas_PROTMEDPROT`):

| Tag | Uso |
|---|---|
| `CILO1$ST$EnaOpn$stVal` (e `CILO2`, `CILO3`) | cadeado ao lado da chave: verdadeiro = liberada, falso = bloqueada |
| `CSWI1$ST$OpOpn$general` e `CSWI1$ST$OpCls$general` | ficam verdadeiros enquanto o comando está a caminho (bom para piscar a chave) |

**Pi do servo** (`EmpElas_CTRLVAO`), opcional: `XSWI1$ST$OpCnt$stVal` conta as manobras da chave 1.

**Disjuntores:** nada muda.

**Comando recusado.** O Elipse recebe um erro de escrita, e como ele aparece depende da configuração da tela. Para o público, quem explica o motivo é o LCD2 e o cadeado do `CILO`.

---

## 8. Wireshark

Com o notebook no cabo do roteador, como na etapa do SV:

| Filtro | Mostra |
|---|---|
| `goose` | as três mensagens GOOSE (trip, comando, posições) |
| `goose.appid == 0x1002 \|\| goose.appid == 0x1003` | só as das chaves |

Mesmo parada, cada mensagem GOOSE se repete a cada 1 s (é o "estou vivo"). Ao clicar em "abrir chave 1", aparece, nesta ordem:

1. `gcbCmd` com `stNum` novo e o primeiro valor `TRUE` (o OpOpn da chave 1);
2. `gcbPos` com a chave 1 em movimento;
3. cerca de 0,5 s depois, `gcbPos` com a chave 1 aberta;
4. `gcbCmd` de volta para tudo `FALSE`.

Logo depois de cada mudança, a mensagem é repetida algumas vezes, a cada 10 ms, e depois volta para uma por segundo. É de propósito: se uma se perder, a próxima chega logo.

A posição aparece como um campo `bit-string` de 2 bits, em hexadecimal: no nosso projeto, `80` = aberto, `40` = fechado, `00` = em movimento (veja a seção 10).

**Wireshark 4.2.2:** essa versão tem um defeito no decodificador de GOOSE. Em mensagens com mais de um valor (como `gcbCmd` e `gcbPos`), ela mostra só o primeiro e depois `Dissector bug, protocol GOOSE ... recursion_depth <= 100`. O problema é do Wireshark, não da mensagem (conferimos os bytes aqui). Para ver tudo, use uma versão mais nova. Para saber qual está instalada: menu **Help → About Wireshark**.

---

## 9. Se algo não funcionar

| Sintoma | O que fazer |
|---|---|
| Telinhas: `Sem as posicoes da Pi do servo` ou LCD2 `SEM POSICOES` | A Pi do servo está rodando a versão nova? Cabo? Na Pi das telinhas: `sudo tcpdump -i eth0 -c 3 -e ether dst 01:0c:cd:01:00:02`. Se nada aparecer, o problema está na Pi do servo ou no cabo. |
| Pi do servo nunca mostra `Assinatura dos comandos das chaves ativa` | A Pi das telinhas está com a versão nova? Na Pi do servo: `sudo tcpdump -i eth0 -c 3 -e ether dst 01:0c:cd:01:00:03`. |
| `Chave 1 nao chegou a ficar aberta em 3 s` | Veja o terminal da Pi do servo. Se apareceu `NAO mexeu: o disjuntor 1 fechou antes da manobra`, alguém fechou o disjuntor no meio do caminho e a chave ficou parada de propósito. Se não apareceu nem `[GOOSE] Comando do IED de controle`, o GOOSE de comando não chegou: confira o cabo. |
| `Posicoes com formato inesperado` | Uma das Pis está com a versão antiga. `git pull` e `make` nas duas. |
| `manobra`: `O IED nao tem ...` | IP trocado: `chave` vai no IP da Pi das telinhas (.101), `dj` no da Pi do servo (.100). |
| `manobra`: `Nao conectou` | O programa daquela Pi não está rodando. |
| Botão da chave no Elipse dá erro sempre | Ainda aponta para o `XSWI` na Pi do servo. Veja a seção 7. |
| `ERRO: o empelas_ctrl ja esta rodando` | Já existe uma cópia aberta. A Pi do servo agora também se recusa a abrir duas vezes, como as outras. |
| As chaves fecham sozinhas quando a Pi do servo liga | Normal, como antes: ao ligar, as três vão para fechada. |
| Wireshark: `Dissector bug ... recursion_depth` | Defeito do Wireshark 4.2.2 (seção 8). As mensagens estão certas. |

---

## 10. Limites desta versão e próximos passos

- **Disjuntores ainda sem IED de controle.** Eles continuam recebendo comando do Elipse direto na Pi do servo. O próximo passo natural é criar `CSWI4-6` para eles, pelo mesmo caminho das chaves.
- **Posição "de mentira".** O servo não tem fim de curso. A Pi do servo considera que a chave chegou depois de 0,5 s, e nem percebe se a placa dos servos (PCA9685) estiver desligada. Com microchaves de fim de curso, a posição passaria a ser medida.
- **Codificação da posição.** O projeto grava a posição com os 2 bits na ordem contrária à da norma: aberto sai como `10` (hexa `80`), e a norma diz `01` (hexa `40`) para aberto. Entre as nossas Pis e o Elipse está tudo coerente, porque todos usam a mesma convenção desde o começo. Mas um IED de outro fabricante que assinar o `gcbPos` leria aberto como fechado. O comando (`ctlVal`) também usa esse formato de 2 bits, enquanto a norma usa verdadeiro/falso. Isso não afeta o trip nem o SV. Se o teste de interoperabilidade incluir as posições, vale corrigir antes. A correção mexe nas duas Pis e inverte 1 e 2 nas telas do Elipse.
- **Comando atrasado.** Se a Pi do servo travar no meio de uma manobra e voltar depois, ela termina a manobra, mesmo que o IED de controle já tenha avisado `SEM RESPOSTA`.
- **A MU ainda não sabe a posição do disjuntor.** Agora que existe o `gcbPos`, a MU poderia assiná-lo e zerar a corrente quando o disjuntor 1 abrir. Fica para depois, se quiserem.

---

## 11. Fita nova (12 V, 5 m, 300 LEDs)

**O que já mudou no código** (`server_ctrl.c`, Pi do servo):

- `FITA_COUNT` passou de 19 para **100**. Na fita de 12 V, cada chip WS2811 comanda um grupo de 3 LEDs (cerca de 5 cm), e é esse grupo que o programa chama de pixel: 300 LEDs ÷ 3 = 100. Se cortarem a fita, o número é a quantidade de LEDs do pedaço dividida por 3.
- A cauda dos pulsos cresce com o tamanho da fita: com 100 pixels, 8 na medição e 12 no comando. Na fita curta continuava 2.
- O rastro de um comando agora entra por uma ponta e sai inteiro pela outra. Antes, a cauda aparecia no fim da fita no começo do rastro (com cauda de 2 quase não se notava; com 12, notaria).
- A ordem das cores virou uma linha própria, `FITA_TIPO`. Ela continua `WS2811_STRIP_RGB` até o teste abaixo dizer outra coisa.

A velocidade não muda: a medição dá uma volta na fita a cada 3 s e o comando atravessa em cerca de 1 s, qualquer que seja o tamanho.

Enquanto a fita antiga estiver ligada, volte o `FITA_COUNT` para 19. Com 100, o pulso passaria a maior parte do tempo "fora" da fita curta.

**O que precisa conferir com a fita ligada.** Na Pi do servo, com o `empelas_ctrl` **fechado** (os dois usam o mesmo PWM):
```
cd ~/EmPowerElas-libiec61850/empelas_ctrl
make testes
```
Depois:
```
sudo ./testes/teste_fita
```
- **Passo 1, cores:** os 3 primeiros grupos deveriam ficar vermelho, verde e azul. O programa mostra uma tabela: anote as cores que aparecerem, na ordem, e veja o nome correspondente. Se não for `WS2811_STRIP_RGB`, troque na linha `#define FITA_TIPO` do `server_ctrl.c` (pelo VS Code) e rode `make`.
- **Passo 2, tamanho:** um grupo branco a cada 10 e o último piscando. O pisca-pisca tem que cair no último grupo da fita. Se cortaram a fita, rode com o número certo, por exemplo `sudo ./testes/teste_fita 60`, e troque o `FITA_COUNT` no `server_ctrl.c`.

Se mudar o `server_ctrl.c` na Pi do servo, mande para o GitHub de lá:
```
cd ~/EmPowerElas-libiec61850
git add empelas_ctrl/server_ctrl.c
git commit -m "Fita nova: tamanho e ordem das cores"
git push
```
Na próxima vez que mexer na Pi das telinhas, faça um `git pull` nela.

**Para a equipe da montagem:**

- **Dado:** pino físico **12** (GPIO18) da Pi do servo no **DIN** da fita, na ponta onde começa a seta (a mesma ponta onde a controladora vinha ligada). GND da Pi no GND da fita. O `INSTALACAO.md` antigo dizia pino 40; já corrigi, o código usa o 12.
- **Controladora que veio com a fita:** não entra na maquete, a Pi faz o papel dela. Mas serve para testar a fita sozinha antes: se ela acender com a controladora, a fita e a fonte estão boas, e qualquer problema depois está na ligação com a Pi.
- **Fonte:** 12 V (a fita aceita até 14,4 V; acima disso queima). A fita inteira acesa em branco puxa perto de 6 A (cada grupo de 3 LEDs, uns 60 mA). A nossa animação acende poucos grupos de cada vez e fica bem abaixo de 1 A, mas uma fonte de 12 V e 5 A dá folga. Os 12 V nunca podem encostar na Pi; só o GND é comum.
- **Se os primeiros grupos piscarem sozinhos ou mostrarem cores aleatórias:** o sinal de 3,3 V da Pi pode estar no limite para essa fita. A solução é um 74AHCT125 (ou 74HCT245) alimentado em 5 V entre a Pi e o DIN. Evite os módulos conversores bidirecionais com transistor: costumam ser lentos para os 800 kHz da fita. O comentário antigo do código registra que um conversor testado deixava a fita sempre acesa.
