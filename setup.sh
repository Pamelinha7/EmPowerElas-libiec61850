#!/usr/bin/env bash
#
# setup.sh - Prepara uma Raspberry Pi limpa para rodar o projeto EmPowerElas.
#
# Instala dependencias, habilita I2C, desliga o audio (necessario para a
# fita WS2811 no PCM), compila as bibliotecas de terceiros e o projeto.
#
# Uso:
#   chmod +x setup.sh
#   ./setup.sh
#
# Depois de rodar, REINICIE a Pi (por causa do I2C e do audio):
#   sudo reboot
#
# Rodar como usuario normal (o script chama sudo onde precisa).

set -e  # para no primeiro erro

DEPS="$HOME/deps"
mkdir -p "$DEPS"

echo "==============================================="
echo " EmPowerElas - setup da Raspberry Pi"
echo "==============================================="

# ---------- 1. Pacotes do sistema ----------
echo "[1/6] Instalando pacotes basicos..."
sudo apt-get update
sudo apt-get install -y \
    git build-essential cmake \
    libsqlite3-dev sqlite3 \
    i2c-tools \
    default-jre           # java, para rodar o genmodel.jar

# ---------- 2. Habilitar I2C (para o PCA9685) ----------
echo "[2/6] Habilitando I2C..."
sudo raspi-config nonint do_i2c 0 || true

# ---------- 3. Desligar audio onboard (libera o PCM para a fita WS2811) ----------
echo "[3/6] Desligando audio onboard (dtparam=audio=off)..."
# Em Pi OS novo o arquivo fica em /boot/firmware/config.txt; no antigo, /boot/config.txt
CONFIG=/boot/firmware/config.txt
[ -f "$CONFIG" ] || CONFIG=/boot/config.txt
if grep -q "^dtparam=audio=on" "$CONFIG"; then
    sudo sed -i 's/^dtparam=audio=on/dtparam=audio=off/' "$CONFIG"
elif ! grep -q "^dtparam=audio=off" "$CONFIG"; then
    echo "dtparam=audio=off" | sudo tee -a "$CONFIG"
fi

# ---------- 4. WiringPi (fork mantido) ----------
echo "[4/6] Instalando WiringPi..."
if ! command -v gpio >/dev/null 2>&1; then
    cd "$DEPS"
    rm -rf WiringPi
    git clone https://github.com/WiringPi/WiringPi.git
    cd WiringPi
    ./build
fi

# ---------- 5. libiec61850 ----------
echo "[5/6] Compilando e instalando libiec61850..."
if [ ! -f /usr/local/lib/libiec61850.a ] && [ ! -f /usr/local/lib/libiec61850.so ]; then
    cd "$DEPS"
    rm -rf libiec61850
    git clone https://github.com/mz-automation/libiec61850.git
    cd libiec61850
    mkdir -p build && cd build
    cmake ..
    make -j"$(nproc)"
    sudo make install
    sudo ldconfig
fi

# ---------- 6. Compilar o projeto ----------
echo "[6/6] Compilando o projeto..."
PROJ="$(cd "$(dirname "$0")" && pwd)"

# A libws2811.a e os headers ja vem no repo (pasta empelas_ctrl).
# Se preferir compilar do zero, descomente o bloco abaixo:
# cd "$DEPS"; rm -rf rpi_ws281x
# git clone https://github.com/jgarff/rpi_ws281x.git
# cd rpi_ws281x && mkdir -p build && cd build && cmake -D BUILD_SHARED=OFF .. && make
# cp libws2811.a "$PROJ/empelas_ctrl/"
# cp ../*.h "$PROJ/empelas_ctrl/"

cd "$PROJ/empelas_ctrl" && make
[ -d "$PROJ/empelas_prot" ] && (cd "$PROJ/empelas_prot" && make || true)

echo
echo "==============================================="
echo " Setup concluido!"
echo " REINICIE a Pi agora:   sudo reboot"
echo
echo " Depois, confira o PCA9685:   sudo i2cdetect -y 1   (deve mostrar 40)"
echo " E rode o controle:           cd empelas_ctrl && sudo ./empelas_ctrl"
echo "==============================================="
