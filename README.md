# EmPowerElas — Maquete de Subestação Digital

Maquete física e interativa de uma subestação elétrica digital, construída para mostrar a norma **IEC 61850** funcionando de verdade: com equipamentos que se movem, indicações que acendem e comunicação real entre dispositivos.

Projeto de extensão da **Universidade Federal Fluminense (UFF)**.

---

## Por que existe

Subestação digital é difícil de explicar porque o que ela tem de mais interessante é invisível. A norma IEC 61850 substituiu quilômetros de fiação de cobre por mensagens trafegando numa rede — e mensagem em rede não se vê.

Bancadas didáticas de subestação digital normalmente resolvem isso com equipamento comercial em rack, ou com dispositivos virtualizados em tela. Nos dois casos o público-alvo é quem já estuda o assunto.

Esta maquete tenta o caminho oposto: **tornar visível o que é invisível**, com processo físico animado, para quem ainda não escolheu a área. Uma chave seccionadora que abre de verdade, disjuntores que indicam sua posição, e uma fita de LED que mostra a mensagem percorrendo a fibra óptica no instante em que ela trafega.

## Como funciona

A maquete é controlada por dois servidores IEC 61850 rodando em Raspberry Pi, supervisionados por um SCADA. Cada placa representa um dispositivo distinto, como acontece numa subestação real.

| | Pi 1 | Pi 2 |
|---|---|---|
| **IED** | `EmpElas_PROT` | `EmpElas_CTRL` |
| **Papel** | Medição e proteção | Controle de vão |
| **Nós lógicos** | MMXU, PTOC, PTRC | XCBR, XSWI, CILO |
| **Periféricos** | Displays, áudio, dial de carga | Servo, LEDs, fita endereçável |

As duas placas se comunicam entre si por **GOOSE** (comunicação horizontal, sem passar pelo supervisório). O SCADA conecta-se às duas por **MMS** e apresenta um unifilar único, como um operador veria.

Essa divisão não é arbitrária: reproduz a separação entre relé de proteção e controlador de vão que existe em instalações reais, e faz com que a ordem de abertura precise atravessar a rede — que é exatamente o caso de uso do GOOSE.

## O que a maquete faz

**Implementado**

- Medição de corrente e tensão, exibida em displays na própria maquete
- Chave seccionadora motorizada, aberta e fechada por comando do SCADA
- Indicação de posição de três disjuntores
- Fita de LED endereçável representando o caminho da fibra óptica
- Som ambiente de transformador
- Comunicação MMS com o supervisório

**Planejado**

- Dial de carga: a visitante gira um botão, a corrente sobe e a proteção atua sozinha
- Proteção de sobrecorrente com curva de tempo inverso (IEC 60255-151)
- Intertravamento: o sistema recusa manobras perigosas e explica o motivo
- Seletividade: apenas o disjuntor mais próximo da falta atua
- Lista de eventos com selo de tempo em milissegundos
- Serviço de log no próprio dispositivo
- Comunicação GOOSE entre as duas placas

## Hardware

| Item | Onde | Função |
|---|---|---|
| Raspberry Pi 3 Model B (2 un.) | — | Servidores IEC 61850 |
| Display LCD 1602 (2 un.) | Pi 1 | Corrente e tensão |
| Amplificador e alto-falante | Pi 1 | Zumbido do transformador |
| Servo SG90 | Pi 2 | Abertura da chave seccionadora |
| LEDs (3 pares) | Pi 2 | Posição dos disjuntores |
| Fita endereçável WS2811 | Pi 2 | Caminho da comunicação |

A comunicação entre as placas é feita por cabo, em rede dedicada. GOOSE é multicast de camada 2 e não atravessa fronteiras de rede IP.

## Estrutura do repositório

```
model/      Arquivos SCL (.icd) — o modelo de dados de cada IED
src/        Código dos servidores
  common/     compartilhado pelas duas placas
  prot/       servidor da Pi 1
  ctrl/       servidor da Pi 2
tools/      Utilitários de geração do modelo
docs/       Documentação de projeto
```

Os arquivos `static_model.c` e `static_model.h` são **gerados automaticamente** a partir dos `.icd` e nunca devem ser editados à mão.

## Dependências

- [libiec61850](https://github.com/mz-automation/libiec61850) — pilha IEC 61850
- wiringPi — acesso a GPIO, PWM e LCD
- rpi_ws281x — fita de LED endereçável
- Java Runtime — apenas para gerar o modelo a partir do SCL

## Estado do projeto

Em desenvolvimento. O código está sendo migrado de um repositório anterior e reorganizado; as instruções de compilação serão publicadas quando a migração terminar.

## Equipe

Desenvolvido por [nomes] sob orientação da Profa. Yona Lopes.
[Laboratório / programa de extensão]
Universidade Federal Fluminense — Escola de Engenharia

## Licença

[a definir]

---

Este projeto usa a biblioteca libiec61850, desenvolvida pela MZ Automation e distribuída sob licença GPLv3.
