# Nome do executavel
TARGET = empelas_ctrl

# Compilacao dos arquivos C
SRCS = server_ctrl.c static_model.c

# Flags do Compilador (todos os caminhos -I para os headers)
# -I. no fim: acha os headers da fita (ws2811.h) copiados para a pasta
CFLAGS = -g \
-I. \
-I../../config \
-I../../hal/inc \
-I../../src/common/inc \
-I../../src/mms/inc \
-I../../src/mms/inc_private \
-I../../src/mms/asn1 \
-I../../src/iec61850/inc \
-I../../src/iec61850/inc_private \
-I../../src/goose \
-I../../src/sampled_values \
-I../../src/logging \
-I../../src/tls \
-I../../src/r_session

# Flags do Linker (caminhos -L). -L. acha a libws2811.a na pasta atual.
LDFLAGS = -L. -L../../build -L../../build/src -L../../build/hal -L/usr/local/lib

# Bibliotecas a linkar. -lws2811 = fita; -lrt = usado por ela.
LDLIBS = -liec61850 -lws2811 -lpthread -lm -lrt -lsqlite3 -lwiringPi

# --- Regras do Make ---

all: $(TARGET)

$(TARGET): $(SRCS)
	gcc $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(TARGET)