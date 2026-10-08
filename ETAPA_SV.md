# Etapa SV: merging unit com a "árvore na linha"

Nesta etapa entra uma terceira Raspberry Pi, a **EmpElas_MU** (merging unit). Ela faz o papel da linha, do TC e do TP: gera as correntes e tensões das três fases e manda as amostras por **Sampled Values (SV)**. A Pi das telinhas deixa de ter o botão de falta. Agora ela só mede o que chega da MU e decide sozinha, como um relé de verdade.

A falta é causada por um **botão físico na MU**: "Aperte: uma árvore caiu na linha!". O mesmo comando também pode vir do Elipse.

A Pi do servo **não muda nada** nesta etapa.

---

## 1. Como fica a maquete

```
   botão "árvore"                      Elipse (wi-fi do laboratório, MMS)
        │                                 │                │
   EmpElas_MU ──── SV, 4800/s ────► EmpElas_PROT ── GOOSE trip ──► EmpElas_CTRL
   (Pi 3: linha + TC + TP)          (Pi 1: telinhas)               (Pi 2: servo)
        └────────────────── cabo, roteador da maquete ─────────────────┘
```

| Pi | Papel | Cabo (eth0) | O que mudou |
|---|---|---|---|
| EmpElas_MU (nova) | linha + TC + TP + merging unit | 192.168.10.103 (reservar) | tudo novo: pasta `empelas_mu` |
| EmpElas_PROT (telinhas) | medição e proteção | 192.168.10.101 | recebe SV, mede 3 fases, sem botão de falta |
| EmpElas_CTRL (servo) | controle do vão | 192.168.10.100 | nada |

### O que é o SV, em poucas palavras

O SV é parecido com o GOOSE: vai para um endereço de grupo, não usa IP e só anda pelo cabo da rede local. A diferença é o assunto. O GOOSE manda um aviso quando algo muda. O SV manda **as medidas o tempo todo**: 4800 mensagens por segundo, cada uma com o valor daquele instante das 4 correntes e das 4 tensões. É como tirar 80 fotos de cada ciclo da onda de 60 Hz.

A Pi das telinhas junta as 80 fotos de um ciclo e calcula o **valor eficaz (RMS)**: eleva cada amostra ao quadrado, tira a média e depois a raiz. É esse valor que aparece no display e que a proteção compara com o ajuste de 300 A, a cada ciclo (16,7 ms).

O formato segue o perfil **9-2LE**, o mesmo que os IEDs reais usam: 4 correntes (A, B, C e neutro), 4 tensões (A, B, C e neutro), 80 amostras por ciclo. Assim, no teste de interoperabilidade, um IED do laboratório consegue assinar o mesmo SV.

---

## 2. A falta: o que acontece na linha

A árvore encosta na **fase A**: é uma falta fase-terra, o tipo mais comum em linhas aéreas. A corrente da fase A sobe, a tensão da fase A cai e aparece corrente no neutro. As fases B e C continuam normais.

| Grandeza | Normal | Árvore na linha |
|---|---|---|
| Corrente fase A | 100 A | **800 A** |
| Correntes fases B e C | 100 A | 100 A |
| Corrente de neutro | 0 A | **cerca de 747 A** |
| Tensão fase A | 289 kV | **87 kV** |
| Tensões fases B e C | 289 kV | 289 kV |
| Tensão entre fases A-B | 500 kV | 340 kV |

As tensões de fase aparecem como 289 kV porque são a tensão entre fases dividida por √3 (500 / 1,732 = 289 kV).

**O trip é tripolar:** qualquer fase acima de 300 A faz a proteção mandar um trip só, e o disjuntor abre as três fases juntas. A Pi do servo continua recebendo o mesmo GOOSE de antes.

**Botão:** cada aperto alterna. Um aperto derruba a árvore e o seguinte retira. Pelo Elipse, escrever 1 derruba a árvore e 0 retira. Depois que a árvore é retirada, o trip sai, mas o disjuntor continua aberto até o operador fechar pelo Elipse, como antes.

**Combinado desta versão:** com o disjuntor aberto, a corrente continua alta até a árvore ser retirada. A MU não sabe a posição do disjuntor.

---

## 3. Preparar a Pi nova (MU)

### 3.1 Sistema, SSH e wi-fi
Grave o Raspberry Pi OS, ligue o SSH e conecte no wi-fi do laboratório, como nas outras Pis. Se o sistema for de 32 bits, o VS Code 1.122 que você já usa funciona. Para ver o IP do wi-fi: `hostname -I`.

### 3.2 Nome da Pi
```
sudo hostnamectl set-hostname empelas-mu
```

### 3.3 Cabo no roteador, internet pelo wi-fi
Ligue o cabo da Pi no roteador da maquete. Depois, faça a internet continuar saindo pelo wi-fi. O comando depende da versão do sistema. Primeiro descubra qual é:
```
systemctl is-active NetworkManager
```
- **Se aparecer `active`** (sistemas mais novos):
  ```
  nmcli connection show
  ```
  Ache o nome da conexão do cabo (algo como `Wired connection 1` ou `Conexão cabeada 1`) e rode, trocando o nome:
  ```
  sudo nmcli connection modify "Wired connection 1" ipv4.never-default yes
  sudo nmcli connection up "Wired connection 1"
  ```
- **Se aparecer `inactive`** (como nas outras duas Pis): acrescente no fim do `/etc/dhcpcd.conf`
  ```
  interface eth0
  nogateway
  ```
  e reinicie a Pi.

Confira com `ip route`: a linha `default` precisa sair pelo `wlan0`.

### 3.4 Reservar o IP no roteador
Veja o MAC do cabo com `cat /sys/class/net/eth0/address` e reserve o **192.168.10.103** para ele no roteador.

### 3.5 Programas básicos
```
sudo apt update
sudo apt install -y git build-essential default-jre-headless
```
O Java é usado só pelo `genmodel`, que gera o modelo a partir do `.icd`.

### 3.6 libiec61850 (mesma versão da Pi do servo)
Na **Pi do servo**, veja a versão:
```
cd ~/libiec61850 && git log -1 --oneline
```
Na **Pi nova**:
```
cd ~
git clone https://github.com/mz-automation/libiec61850.git
cd libiec61850
git checkout CODIGO_DA_PI_DO_SERVO
make
make install
sudo mkdir -p /usr/local/include/libiec61850
sudo cp .install/include/*.h /usr/local/include/libiec61850/
sudo cp .install/lib/libiec61850.a /usr/local/lib/
```

### 3.7 wiringPi (para o botão e o LED)
Primeiro confira se já está instalado: `gpio -v`. Se der "command not found":
```
cd ~
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build debian
mv debian-template/wiringpi*.deb .
sudo apt install ./wiringpi*.deb
```
Sem o wiringPi, ainda dá para testar o SV: compile com `make SEM_BOTAO=1` (seção 5).

### 3.8 Repositório
Clone o repositório, com o mesmo endereço que você usou nas outras Pis, e configure o seu nome:
```
cd ~
git clone <endereço do repositório> empelas
git config --global user.name "Pamela Moura"
git config --global user.email "pamela_mp@id.uff.br"
```
Arraste a pasta `empelas_mu` (deste pacote) para dentro de `~/empelas` pelo VS Code. Confira se ficou `~/empelas/empelas_mu/server_mu.c`, sem uma pasta dentro da outra.

No `.gitignore` da raiz do repositório, acrescente estas linhas, para os programas compilados não irem para o GitHub:
```
empelas_mu/empelas_mu
empelas_mu/testes/teste_sv
empelas_mu/testes/falta
```

---

## 4. Ligar o botão e o LED na MU

| Peça | Liga em | Pino físico |
|---|---|---|
| Botão, uma perna | GPIO17 | **11** |
| Botão, outra perna | GND | **9** |
| LED: resistor de 330 Ω | GPIO27 | **13** |
| Resistor → perna longa do LED (+) | | |
| Perna curta do LED (−) | GND | **14** |

- O botão **não precisa de resistor**: o programa liga o resistor interno da Pi (pull-up). Solto, o pino fica em 1; apertado, vai para 0.
- Botão de 4 perninhas: use **duas pernas em diagonal**. Assim funciona sempre, qualquer que seja o lado em que as pernas são ligadas por dentro.
- O LED fica aceso enquanto a árvore estiver na linha. Pode ser qualquer resistor entre 220 Ω e 1 kΩ.
- Sugestão de plaquinha: **"Aperte: uma árvore caiu na linha!"**

---

## 5. Compilar e rodar a MU

```
cd ~/empelas/empelas_mu
make
sudo ./empelas_mu
```
Na primeira vez, o `make` também gera o `static_model.c` e o `static_model.h`. Ainda sem wiringPi ou sem botão ligado, use `make SEM_BOTAO=1`. Nesse caso, a falta só vem pelo Elipse ou pelo programa `falta` (seção 8).

Saída esperada:
```
--- EmpElas_MU : MERGING UNIT (TC e TP digitais da linha) ---
[SV]     Publicando em eth0: svID EmpElas_MU01, APPID 0x4000, 80 amostras/ciclo (4800 por segundo).
[LINHA]  Normal: 500 kV entre fases, 100 A por fase. Falta: fase A com 800 A.
[BOTAO]  Botao no pino fisico 11 (e GND). LED no pino fisico 13. Cada aperto alterna a falta.
[STATUS] Servidor na porta 102. Supervisorio: FLTGGIO1.SPCSO1 (1 = arvore cai, 0 = retira).
[SV] 4800 mensagens/s | puladas por atraso: 0 | arvore na linha: nao
```
A última linha se repete a cada 10 s. Aperte o botão: o LED acende e aparece `[FALTA] Uma arvore caiu na linha!`.

---

## 6. Conferir o SV antes de mexer na proteção

Na **Pi das telinhas**, puxe os arquivos novos e compile o monitor de SV. Ele não mexe em nenhum servidor:
```
cd ~/empelas
git pull
cd empelas_mu
make testes
sudo ./testes/teste_sv eth0
```
Se o `git pull` ainda não trouxer a pasta `empelas_mu` (porque você ainda não fez o commit na MU), copie a pasta pelo VS Code também.

Saída esperada, a cada segundo:
```
[SV] 4800 msg/s | perdidas 0 | repetidas 0 | svID EmpElas_MU01 | confRev 1 | smpSynch 0
     IA  100.0 A   IB  100.0 A   IC  100.0 A   IN    0.0 A
     VA  288.7 kV  VB  288.7 kV  VC  288.7 kV  VN    0.0 kV
```
Com a árvore na linha, IA vai para 800 A, IN para cerca de 747 A e VA para 86,6 kV. No primeiro segundo podem aparecer algumas "perdidas": é o programa começando no meio do fluxo.

Para ver as mensagens no cabo, sem programa nenhum:
```
sudo tcpdump -i eth0 -c 5 -e ether proto 0x88ba
```
(0x88BA é a "etiqueta" que identifica o SV; a do GOOSE é 0x88B8.)

---

## 7. Atualizar a Pi das telinhas

Troque o `server_prot.c`, o `empelas_prot.icd` e o `Makefile` pelos deste pacote e rode:
```
cd ~/empelas/empelas_prot
make modelo
make
sudo ./empelas_prot
```
(O ideal é já ter feito a migração para a pasta do repositório. Se ainda estiver na pasta antiga `~/moveuff-persistent-libiec61850/server/server_unifield_io`, copie só o `server_prot.c` e o `.icd`, gere o modelo com `java -jar genmodel.jar empelas_prot.icd` e rode `make`.)

Saída esperada:
```
--- EmpElas_PROT : MEDICAO (SV da merging unit) E PROTECAO ---
[STATUS] LCD1 (correntes) OK | LCD2 (tensoes) OK
[STATUS] Rodando na porta 102.
[SV]     Assinando EmpElas_MU01 em eth0 (APPID 0x4000). Aguardando a merging unit...
[GOOSE]  Publicando gcbTrip em eth0 (APPID 0x1001).
[PROTECAO] Sobrecorrente de fase, sem atraso, partida em 300 A. Trip tripolar.
[SV] Recebendo a merging unit (EmpElas_MU01).
[MEDICAO] IA 100.0 IB 100.0 IC 100.0 IN 0.0 A | VA 288.7 VB 288.7 VC 288.7 kV | SV perdidas: 0
```

Displays:

| | Linha 1 | Linha 2 |
|---|---|---|
| LCD1 normal | `CORRENTE (A)` | `A100 B100 C100` |
| LCD1 com a árvore | `TRIP A   ->GOOSE` | `A800 B100 C100` |
| LCD1 sem SV | `SEM SINAL DA MU` | `A--- B--- C---` |
| LCD2 normal | `TENSAO FASE (kV)` | `A289 B289 C289` |
| LCD2 com a árvore | `TENSAO FASE (kV)` | `A 87 B289 C289` |

---

## 8. Teste completo

1. Rode as três Pis: servo (`sudo ./empelas_ctrl`), telinhas (`sudo ./empelas_prot`) e MU (`sudo ./empelas_mu`). A ordem não importa.
2. **Linha normal:** LCD1 `CORRENTE (A)` / `A100 B100 C100` e LCD2 `A289 B289 C289`. Feche o disjuntor 1 pelo Elipse.
3. **Aperte o botão (a árvore cai):**
   - na MU: LED aceso e `[FALTA] Uma arvore caiu na linha!`;
   - na Pi das telinhas: `[PROTECAO] Sobrecorrente na fase A ... TRIP publicado por GOOSE.` e LCD1 `TRIP A   ->GOOSE`;
   - na Pi do servo: `[GOOSE] TRIP recebido` e disjuntor 1 aberto (LED vermelho, fita vermelha);
   - no Elipse: `XCBR1$ST$Pos$stVal` = 1.
4. **Aperte de novo (árvore retirada):** a Pi das telinhas mostra `Corrente normalizada. Trip retirado` e volta ao normal. A Pi do servo avisa que o trip saiu, mas o disjuntor continua aberto.
5. **Feche o disjuntor pelo Elipse**, como sempre.
6. **Sem o Elipse**, dá para derrubar e retirar a árvore pelo terminal de qualquer Pi da rede:
   ```
   cd ~/empelas/empelas_mu && make testes
   ./testes/falta <IP da MU> 1      (a árvore cai)
   ./testes/falta <IP da MU> 0      (árvore retirada)
   ./testes/falta <IP da MU>        (só mostra o estado)
   ```
7. **Tire o cabo da MU:** em até 0,1 s a Pi das telinhas mostra `SEM SINAL DA MU`. A medição fica marcada como inválida, e a proteção fica bloqueada (não dá trip sem medida). Recoloque o cabo e tudo volta sozinho.

No teste feito aqui, com os programas rodando juntos num computador, a proteção atuou entre 4 e 20 ms depois da árvore cair (no máximo um ciclo e pouco). Na maquete deve ficar parecido, somando alguns milissegundos de rede.

Quando tudo funcionar, faça o commit da pasta nova (na MU) e dos arquivos da Pi das telinhas:
```
cd ~/empelas
git add .gitignore empelas_mu
git commit -m "Merging unit com SV e botao de falta (arvore na linha)"
git push
```
Na Pi das telinhas, faça o mesmo com `git add empelas_prot` depois de um `git pull`.

---

## 9. Tags do Elipse

**IED novo: EmpElas_MU** (dispositivo lógico `EmpElas_MUMU01`). Conecte no IP do wi-fi da MU.

| Tag | Uso |
|---|---|
| `FLTGGIO1$CO$SPCSO1$Oper` | escrever 1 = árvore cai; 0 = árvore retirada |
| `FLTGGIO1$ST$SPCSO1$stVal` | leitura: verdadeiro = árvore na linha |

**EmpElas_PROT** (dispositivo lógico `EmpElas_PROTMEDPROT`). O modelo mudou, então refaça a leitura dos dados do IED no Elipse.

| Tag | Uso |
|---|---|
| `MMXU1$MX$A$phsA$cVal$mag$f` (e `phsB`, `phsC`, `neut`) | correntes (A) |
| `MMXU1$MX$PhV$phsA$cVal$mag$f` (e `phsB`, `phsC`, `neut`) | tensões de fase (kV) |
| `MMXU1$MX$PPV$phsAB$cVal$mag$f` (e `phsBC`, `phsCA`) | tensões entre fases (kV) |
| `MMXU1$MX$A$phsA$q` | qualidade: fica inválida sem SV (bom para um alarme "sem sinal da MU") |
| `PTOC1$ST$Str$general` e `PTOC1$ST$Str$phsA` (`phsB`, `phsC`) | partida e em qual fase |
| `PTOC1$ST$Op$general` e `PTOC1$ST$Op$phsA` (`phsB`, `phsC`) | operação e em qual fase |
| `PTRC1$ST$Tr$general` | trip (igual a antes) |

**Saíram da Pi das telinhas:** `GGIO1$CO$SPCSO1$Oper` (a falta agora é na MU), `MMXU1$MX$Amp$mag$f` e `MMXU1$MX$Vol$mag$f` (viraram as fases A, B e C).

**Pi do servo:** nada muda.

---

## 10. Cuidado com o wi-fi do roteador

São 4800 mensagens de SV por segundo, cerca de 5 Mbit/s. Para o cabo isso é pouco (uns 5% da capacidade). Mas o roteador repete essas mensagens em todas as portas e, provavelmente, também no wi-fi dele (**EmpowerElas**). Enquanto o Elipse continuar no wi-fi do laboratório, como hoje, tudo bem. **Não conectem celular, tablet ou notebook no wi-fi do roteador com a MU ligada**: ele pode ficar muito lento.

A Pi do servo também recebe essas mensagens pelo cabo e simplesmente as descarta, porque não são GOOSE. Isso gasta um pouco de processamento, mas não atrapalha.

---

## 11. Se algo não funcionar

| Sintoma | O que fazer |
|---|---|
| MU: `[SV] ERRO: nao consegui abrir a interface eth0` | Confira o cabo, o nome da interface (`ip link`) e se rodou com `sudo`. |
| MU: `Aviso: sem prioridade de tempo real` | Rodou sem `sudo`. O SV sai, mas com mais variação. |
| MU: "puladas por atraso" subindo | A Pi está sobrecarregada. Feche outros programas e confira com `top`. |
| `teste_sv` mostra "nada chegando" | Na Pi das telinhas, rode o `tcpdump` da seção 6. Se não aparecer nada, o problema é a MU ou o cabo. Se aparecer, confira se APPID e svID são iguais nos dois programas. |
| Pi das telinhas: `SEM SINAL DA MU` | Igual à linha de cima. |
| "SV perdidas" sempre maior que 0 | Perder poucas de vez em quando é normal. Muitas: confira os cabos e a carga da MU. |
| `make`: `wiringPi.h: No such file` | Instale o wiringPi (seção 3.7) ou use `make SEM_BOTAO=1`. |
| `make` da Pi das telinhas: `cannot find -lsqlite3` | Comente a linha `LIBS += -lsqlite3` no Makefile. |
| `make modelo`: `java: command not found` | `sudo apt install default-jre-headless` |
| O botão não faz nada | Confira os pinos 9 e 11, use as pernas em diagonal e veja se apareceu a linha `[BOTAO]` ao iniciar. |
| `ERRO: o empelas_mu ja esta rodando` | Já existe uma cópia aberta (talvez em outro terminal). Feche com Ctrl+C ou procure com `ps aux \| grep empelas_mu`. Os dois servidores agora se recusam a abrir duas vezes. |
| Elipse não acha `GGIO1` na Pi das telinhas | Ele saiu de lá: o comando de falta agora é `FLTGGIO1` na MU. |

---

## 12. Limites desta versão e próximos passos

- **Relógio:** a MU manda `smpSynch = 0` (amostras não sincronizadas com GPS ou PTP). Para a Pi das telinhas isso não importa. Alguns IEDs reais bloqueiam a proteção com SV não sincronizado: confira no manual do IED do laboratório antes do teste de interoperabilidade.
- **Teste de interoperabilidade:** a ferramenta de configuração do IED do laboratório vai precisar do `empelas_mu.icd`. Ele descreve o bloco `MSVCB01`, o conjunto de dados `PhsMeas1` e o endereço (MAC 01-0C-CD-04-00-01, APPID 0x4000).
- **Modo de simulação:** a norma prevê marcar o SV como simulado e usar `LPHD.Sim` no IED que recebe. A libiec61850 não tem função para isso, então ficou de fora.
- **Disjuntor aberto:** a corrente continua alta até a árvore ser retirada (combinado nesta versão). Para zerar a corrente quando o disjuntor abre, a Pi do servo precisaria publicar a posição do disjuntor por GOOSE.
- **Nome da proteção:** o `PTOC1` atua sem atraso. Pela norma, isso seria `PIOC1`. Ele passa a fazer jus ao nome quando entrar a curva inversa.
