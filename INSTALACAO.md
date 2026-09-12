# Instalação — EmPowerElas

Passo a passo para clonar o projeto numa Raspberry Pi nova e deixar tudo
funcionando.

## Requisitos de hardware

- Raspberry Pi (testado em Pi 3) com Raspberry Pi OS.
- **Pi 2 (controle):** módulo PCA9685 (servos das seccionadoras), 6 LEDs
  (disjuntores), fita WS2811 (fibra), fonte externa 5V/2A para o V+ do PCA9685.
- **Pi 1 (medição):** 2 displays LCD 1602, amplificador PAM8403 + alto-falante.

## Instalação automática (recomendado)

```bash
git clone https://github.com/Pamelinha7/EmPowerElas-libiec61850.git
cd EmPowerElas-libiec61850
chmod +x setup.sh
./setup.sh
sudo reboot
```

O `setup.sh` faz tudo: instala pacotes, habilita o I2C, desliga o áudio
onboard (necessário para a fita no PCM), compila e instala a **libiec61850**
e o **WiringPi**, e por fim compila o projeto.

## Depois do reboot — conferir

```bash
# O PCA9685 deve aparecer no endereço 40:
sudo i2cdetect -y 1

# Rodar o IED de controle (Pi 2):
cd EmPowerElas-libiec61850/empelas_ctrl
sudo ./empelas_ctrl
```

No boot as 3 seccionadoras vão para a posição fechada (um tranco em cada
servo). Os comandos FECHAR/ABRIR do SCADA (Elipse) movem os servos, acendem
os LEDs dos disjuntores e disparam o rastro na fita.

## Ligações principais (Pi 2 — controle)

### PCA9685 (servos)
| PCA9685 | Pino da Pi (físico) |
|---------|---------------------|
| VCC     | 1 (3,3V) — **precisa de contato firme, senão as saídas não acionam** |
| GND     | 6 (ou qualquer GND) |
| SDA     | 3 (GPIO2)           |
| SCL     | 5 (GPIO3)           |
| OE      | GND (habilita as saídas) |
| V+ (borne verde) | + da fonte externa 5V |
| GND (borne verde) | – da fonte externa 5V (terra comum com a Pi) |

Servos nos canais **0, 1 e 2** (colunas da placa). Em cada canal:
amarelo→PWM (cima), vermelho→V+ (meio), preto→GND (baixo).

### Fita WS2811
- Dado no **GPIO21 (físico 40)**, **direto** (sem level shifter).
- 12V e GND por fonte externa; **GND comum** com a Pi.
- Todas as setas dos pedaços no mesmo sentido (dado entra pela cauda da seta).

### LEDs dos disjuntores (wiringPi)
D1: verde=0, verm=2 · D2: verde=3, verm=4 · D3: verde=5, verm=6.

## Regenerar o modelo IEC (só se editar o .icd)

O `static_model.c/.h` já vem pronto no repositório. Só precisa regerar se
mudar o `empelas_ctrl.icd`:

```bash
cd empelas_ctrl
java -jar genmodel.jar empelas_ctrl.icd
make
```

## Instalação manual (se o setup.sh falhar)

```bash
sudo apt update
sudo apt install -y git build-essential cmake libsqlite3-dev i2c-tools default-jre

# WiringPi
git clone https://github.com/WiringPi/WiringPi.git && cd WiringPi && ./build && cd ..

# libiec61850
git clone https://github.com/mz-automation/libiec61850.git
cd libiec61850 && mkdir build && cd build && cmake .. && make -j4 && sudo make install && sudo ldconfig && cd ../..

# Habilitar I2C e desligar audio
sudo raspi-config nonint do_i2c 0
sudo sed -i 's/^dtparam=audio=on/dtparam=audio=off/' /boot/firmware/config.txt

# Compilar
cd empelas_ctrl && make
```
