# Makefile - EmpElas_CTRL (Pi 2: controle de vao)
#
# Compila contra a libiec61850 e a rpi_ws281x INSTALADAS NO SISTEMA, nao
# contra as arvores de codigo delas. Por isso este diretorio pode ficar
# em qualquer lugar - inclusive num clone do repositorio.
#
#   make            compila
#   make modelo     regenera static_model.c/.h a partir do .icd
#   make clean      apaga o binario e os objetos
#
# Se as bibliotecas tiverem sido instaladas em outro prefixo:
#   make PREFIX=/opt/libiec61850

PREFIX ?= /usr/local

TARGET = empelas_ctrl
SRCS   = server_ctrl.c static_model.c
ICD    = empelas_ctrl.icd

CC      = gcc
CFLAGS  = -g -Wall -O2
CPPFLAGS = -I$(PREFIX)/include/libiec61850 -I$(PREFIX)/include
LDFLAGS  = -L$(PREFIX)/lib

# ws2811: fita enderecavel. wiringPi: GPIO dos LEDs e I2C do PCA9685.
LIBS = -liec61850 -lws2811 -lwiringPi -lpthread -lm -lrt

# Algumas compilacoes da libiec61850 incluem suporte a log em sqlite.
# Se o link reclamar de simbolos sqlite3_*, mantenha esta linha.
# Se reclamar que nao encontra -lsqlite3, comente-a.
LIBS += -lsqlite3

.PHONY: all modelo clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)
	@echo ""
	@echo "Pronto. Rode com:  sudo ./$(TARGET)"

# Regenera o modelo a partir do SCL. Necessario apenas quando o .icd muda.
# Os arquivos gerados sao versionados, entao um clone limpo ja compila
# sem precisar deste alvo.
modelo:
	java -jar ../genmodel.jar $(ICD)
	@echo ""
	@echo "Modelo regenerado. Recompile com 'make' e reimporte o $(ICD) no SCADA."

clean:
	rm -f $(TARGET) *.o
