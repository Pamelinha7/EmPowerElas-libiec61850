# EmPowerElas — Maquete de Subestação Digital

Maquete física e interativa de uma subestação elétrica digital, construída
para mostrar a norma **IEC 61850** funcionando de verdade: com equipamentos
que se movem, indicações que acendem e comunicação real entre dispositivos.

Projeto de extensão da **Universidade Federal Fluminense (UFF)**.

## Por que existe

Subestação digital é difícil de explicar porque o que ela tem de mais
interessante é invisível. A norma IEC 61850 substituiu quilômetros de fiação
de cobre por mensagens trafegando numa rede — e mensagem em rede não se vê.

A maquete torna isso tangível: o operador dá um comando no SCADA e uma chave
se move, um LED muda de cor, um rastro de luz percorre a "fibra". O que era
abstrato vira visível.

## O que a maquete faz

- **Merging unit (MU):** simula o TC e o TP da linha e publica as medidas em
  **SV** (IEC 61850-9-2LE, 4800 amostras por segundo). Um botão na maquete
  derruba uma árvore na linha e cria uma falta na fase A.
- **Proteção e controle (PROT):** recebe o SV, mostra correntes e tensões em
  dois LCDs, faz a proteção de sobrecorrente instantânea (**PIOC**, função 50)
  e manda o trip por **GOOSE**. Também é o IED de controle: o operador comanda
  chaves e disjuntores no **CSWI1-6**, e o intertravamento (**CILO1-6**) decide
  se a manobra pode.
- **Pátio (CTRL):** três servos movem as chaves seccionadoras (XSWI1-3), seis
  LEDs mostram os disjuntores (XCBR1-3; vermelho = fechado, verde = aberto) e
  fitas de LED mostram as mensagens na fibra e no cobre.
- **Supervisório web e gêmeo 3D:** rodam na CTRL e abrem pelo Wi-Fi da
  maquete. O gêmeo só mostra a maquete, nunca manda comando.
- **Áudio:** zumbido do transformador enquanto há vão energizado.

O operador pode usar o **Elipse E3** ou o supervisório web. Os dois falam
**IEC 61850 (MMS, porta 102)** com servidores escritos em C sobre a
biblioteca **libiec61850**.

## Arquitetura (3 Raspberry Pis)

| Pi | Pasta | Cabo (switch) | Função |
|----|-------|---------------|--------|
| **MU** | `empelas_mu` | 192.168.10.103 | SV, botão da falta |
| **PROT** | `empelas_prot` | 192.168.10.101 | medição, proteção, controle (CSWI/CILO), LCDs, áudio, relógio da maquete |
| **CTRL** | `empelas_ctrl` | 192.168.10.100 | servos, LEDs, fitas; supervisório e gêmeo (`tablet_scada`) |

As Pis ficam num switch só delas. O roteador cuida só do Wi-Fi, sem cabo para
o switch, para o SV não chegar ao Wi-Fi. Detalhes em
**[ETAPA_REDE.md](ETAPA_REDE.md)**. As mudanças para o formato da norma
(PIOC, CSWI4-6, posição Dbpos) estão em **[ETAPA_NORMA.md](ETAPA_NORMA.md)**.

## Controle dos servos — PCA9685

> **Mudança de arquitetura:** os servos deixaram de ser controlados por PWM
> de software na própria Pi e passaram a usar o módulo **PCA9685 via I2C**.
> O PCA9685 gera o PWM em hardware próprio, o que **libera o PCM da Pi para a
> fita WS2811**, elimina o tremor dos servos e permite os três servos sem
> disputa de temporizador.

Pontos de atenção que costumam travar a montagem (todos documentados no
[INSTALACAO.md](INSTALACAO.md)):

- **VCC do PCA9685 no 3,3V da Pi com contato firme.** Se o VCC ficar mal
  conectado, o chip é "alimentado de fome" pelos pinos de I2C: aparece no
  `i2cdetect` mas **as saídas não acionam** e os servos não mexem.
- **OE no GND** para habilitar as saídas.
- **V+** por fonte externa de 5V (nunca pelo 5V da Pi), com **GND comum**
  entre fonte, PCA9685 e Pi.
- Servos nos canais **0, 1 e 2**; em cada canal amarelo→PWM, vermelho→V+,
  preto→GND.

## Instalação

Passo a passo completo (dependências, I2C, áudio, compilação e ligações) em
**[INSTALACAO.md](INSTALACAO.md)**.

Resumo — clonar e rodar numa Pi nova:

```bash
git clone https://github.com/Pamelinha7/EmPowerElas-libiec61850.git
cd EmPowerElas-libiec61850
chmod +x setup.sh
./setup.sh
sudo reboot
```

Depois do reboot:

```bash
sudo i2cdetect -y 1                 # deve mostrar o endereço 40 (PCA9685)
cd empelas_ctrl && sudo ./empelas_ctrl
```

## Estrutura do repositório

```
EmPowerElas-libiec61850/
├── empelas_ctrl/          # CTRL — pátio (servos, LEDs, fitas)
│   ├── server_ctrl.c      # servidor IEC 61850 principal
│   ├── static_model.c/.h  # modelo IEC gerado (já vem pronto)
│   ├── empelas_ctrl.icd   # descrição SCL do modelo
│   ├── Makefile
│   ├── genmodel.jar       # regera o static_model a partir do .icd
│   ├── libws2811.a + headers   # biblioteca da fita WS2811
│   └── testes/            # programas de diagnóstico (servo, pinos, fita)
├── empelas_prot/          # PROT — medição, proteção e controle
├── empelas_mu/            # MU — merging unit (SV) e botão da falta
├── tablet_scada/          # supervisório web e gêmeo 3D (roda na CTRL)
├── servicos/              # serviços do systemd e arquivos do relógio
├── genmodel.jar
├── simulador_json.py
├── setup.sh               # instalação automática numa Pi limpa
├── INSTALACAO.md          # guia detalhado de instalação e ligações
├── ETAPA_NORMA.md         # PIOC, CSWI4-6 e posição no formato da norma
├── ETAPA_REDE.md          # switch, Wi-Fi, serviços e relógio
└── README.md
```

## Regenerar o modelo IEC

O `static_model.c/.h` já vem pronto no repositório. Só regere se editar o
`empelas_ctrl.icd`:

```bash
cd empelas_ctrl
java -jar genmodel.jar empelas_ctrl.icd
make
```

## Créditos
Karina Santos e Pamela Moura
-- Projeto de extensão da Universidade Federal Fluminense (UFF).
