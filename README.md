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

- **Chaves seccionadoras (XSWI1-3):** três servos motores que abrem e fecham
  sob comando do SCADA.
- **Disjuntores (XCBR1-3):** seis LEDs (verde = fechado, vermelho = aberto).
- **Medição (MMXU):** correntes e tensões do TC/TP exibidas em displays LCD.
- **Fibra óptica (comunicação):** fita LED endereçável WS2811 com um pulso
  contínuo de "medição" e um rastro rápido a cada comando de manobra.
- **Áudio:** som contínuo representando o transformador.

Tudo é comandado por um cliente SCADA (**Elipse E3**) via protocolo
**IEC 61850 (MMS, porta 102)**, falando com servidores escritos em C sobre a
biblioteca **libiec61850**.

## Arquitetura (2 Raspberry Pis)

| Pi | Pasta | Função | Componentes |
|----|-------|--------|-------------|
| **Pi 1** | `empelas_prot` | Medição / proteção | 2 LCDs 1602 (TC/TP), áudio (PAM8403 + alto-falante) |
| **Pi 2** | `empelas_ctrl` | Controle do vão | Servos (PCA9685), 6 LEDs (disjuntores), fita WS2811 (fibra) |

Cada Pi roda seu próprio servidor IEC 61850, com IP próprio na porta 102. O
Elipse conecta-se às duas.

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
├── empelas_ctrl/          # Pi 2 — controle (servos, LEDs, fita)
│   ├── server_ctrl.c      # servidor IEC 61850 principal
│   ├── static_model.c/.h  # modelo IEC gerado (já vem pronto)
│   ├── empelas_ctrl.icd   # descrição SCL do modelo
│   ├── Makefile
│   ├── genmodel.jar       # regera o static_model a partir do .icd
│   ├── libws2811.a + headers   # biblioteca da fita WS2811
│   └── testes/            # programas de diagnóstico (servo, pinos, fita)
├── empelas_prot/          # Pi 1 — medição / proteção
├── genmodel.jar
├── simulador_json.py
├── setup.sh               # instalação automática numa Pi limpa
├── INSTALACAO.md          # guia detalhado de instalação e ligações
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

Projeto de extensão da Universidade Federal Fluminense (UFF).
