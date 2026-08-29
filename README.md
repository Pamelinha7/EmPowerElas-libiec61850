# EmPowerElas — Maquete de Subestação Digital

Maquete física e interativa de uma subestação elétrica digital, construída para mostrar a norma **IEC 61850** funcionando de verdade: com equipamentos que se movem, indicações que acendem e comunicação real entre dispositivos.

Projeto de extensão da **Universidade Federal Fluminense (UFF)**.

---

## Por que existe

Subestação digital é difícil de explicar porque o que ela tem de mais interessante é invisível. A norma IEC 61850 substituiu quilômetros de fiação de cobre por mensagens trafegando numa rede — e mensagem em rede não se vê.

Bancadas didáticas de subestação digital normalmente resolvem isso com equipamento comercial em rack, ou com dispositivos virtualizados em tela. Nos dois casos o público-alvo é quem já estuda o assunto.

Esta maquete tenta o caminho oposto: **tornar visível o que é invisível**, com processo físico animado, para quem ainda não escolheu a área. Uma chave seccionadora que abre de verdade, disjuntores que indicam sua posição, e uma fita de LED que mostra a mensagem percorrendo a fibra óptica no instante em que ela trafega.

## Como funciona

A maquete é controlada por dois servidores IEC 61850 rodando em Raspberry Pi, supervisionados pelo SCADA Elipse E3. Cada placa representa um dispositivo distinto, como acontece numa subestação real.

| | Pi 1 | Pi 2 |
|---|---|---|
| **IED** | `EmpElas_PROT` | `EmpElas_CTRL` |
| **Logical Device** | `MEDPROT` | `VAO` |
| **Papel** | Medição e proteção | Controle de vão |
| **Nós lógicos** | MMXU, LTIM, LTMS | XSWI, XCBR 1-3, LGOS, LTRK |
| **Periféricos** | Displays LCD, áudio | Servo, LEDs, fita endereçável |
| **Pasta** | `empelas_prot/` | `empelas_ctrl/` |

O supervisório abre uma conexão MMS com cada placa e apresenta um unifilar único, como um operador veria. Cada Raspberry compila apenas a pasta correspondente ao seu papel.

Essa divisão não é arbitrária: reproduz a separação entre relé de proteção e controlador de vão que existe em instalações reais, e faz com que a ordem de abertura precise atravessar a rede — que é exatamente o caso de uso do GOOSE, previsto para a etapa seguinte.

## O que a maquete faz

**Implementado**

- Medição de corrente e tensão, exibida em displays na própria maquete e no supervisório
- Chave seccionadora motorizada, aberta e fechada por comando do SCADA
- Indicação de posição de três disjuntores
- Fita de LED endereçável representando o caminho da fibra óptica
- Som ambiente de transformador
- Comunicação MMS com o supervisório, com dois IEDs independentes

**Planejado**

- Dial de carga: a visitante gira um botão, a corrente sobe e a proteção atua sozinha
- Proteção de sobrecorrente com curva de tempo inverso (IEC 60255-151)
- Intertravamento (CILO): o sistema recusa manobras perigosas e explica o motivo
- Seletividade: apenas o disjuntor mais próximo da falta atua
- Lista de eventos com selo de tempo em milissegundos
- Serviço de log no próprio dispositivo
- Comunicação GOOSE entre as duas placas

## Hardware

| Item | Onde | Função |
|---|---|---|
| Raspberry Pi 3 Model B (2 un.) | — | Servidores IEC 61850 |
| Display LCD 1602 (2 un.) | Pi 1 | Corrente e tensão |
| Amplificador PAM8403 e alto-falante | Pi 1 | Zumbido do transformador |
| Servo SG90 | Pi 2 | Abertura da chave seccionadora |
| LEDs (3 pares) | Pi 2 | Posição dos disjuntores |
| Fita endereçável WS2811 | Pi 2 | Caminho da comunicação |

A comunicação entre as placas é feita por cabo, em rede dedicada. GOOSE é multicast de camada 2 e não atravessa fronteiras de rede IP.

Uma restrição de hardware explica a divisão dos periféricos: na Pi 2 o servo ocupa o PWM e a fita ocupa o PCM, o que obriga a desligar o áudio embutido nessa placa. Por isso o som fica na Pi 1.

## Estrutura do repositório

```
empelas_prot/       Servidor da Pi 1 — modelo SCL, código e Makefile
empelas_ctrl/       Servidor da Pi 2 — modelo SCL, código e Makefile
genmodel.jar        Gerador do modelo em C a partir do arquivo SCL
simulador_json.py   Simulador que serve grandezas por socket
```

## Dependências

- [libiec61850](https://github.com/mz-automation/libiec61850) — pilha IEC 61850
- wiringPi — GPIO, PWM e LCD
- rpi_ws281x — fita de LED endereçável (apenas Pi 2)
- Java Runtime — para gerar o modelo a partir do SCL

## Como compilar

Cada Raspberry compila apenas a sua pasta: `empelas_prot` na Pi 1, `empelas_ctrl` na Pi 2.

```
cd empelas_prot
java -jar ../genmodel.jar empelas_prot.icd
make
sudo ./empelas_prot
```

A execução exige `sudo` por causa do acesso a GPIO — e, na Pi 2, também por causa do DMA usado pela fita.

**Os arquivos `static_model.c` e `static_model.h` não estão versionados.** São gerados pelo `genmodel` a partir do `.icd` e nunca devem ser editados à mão: a edição se perde na próxima geração e cria divergência silenciosa entre o modelo declarado e o modelo em execução. Sempre que alterar o `.icd`, regenere, recompile e reimporte o arquivo no driver do supervisório.

Pendência conhecida: os `Makefile` ainda esperam estar dentro da árvore de código da libiec61850, com caminhos relativos. Desacoplar o projeto da biblioteca deixaria este repositório autossuficiente.

## Estado do projeto

Em desenvolvimento ativo. As duas placas foram migradas do projeto anterior e estão em funcionamento: medição publicada e lida pelo supervisório, comandos de manobra atuando sobre servo, LEDs e fita.

## Equipe

Desenvolvido por [nomes] sob orientação da Profa. Yona Lopes.
[Laboratório / programa de extensão]
Universidade Federal Fluminense — Escola de Engenharia

## Licença

[a definir]

---

Este projeto usa a biblioteca libiec61850, desenvolvida pela MZ Automation e distribuída sob licença GPLv3.
