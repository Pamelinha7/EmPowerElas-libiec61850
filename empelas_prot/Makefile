# Nome do executavel
TARGET = empelas_prot

# Compilacao dos arquivos C
SRCS = server_prot.c static_model.c

# Flags do Compilador (todos os caminhos -I para os headers)
CFLAGS = -g \
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

# Flags do Linker (caminhos -L para as bibliotecas .a)
# -L/usr/local/lib para garantir que ache o wiringPi
LDFLAGS = -L../../build -L../../build/src -L../../build/hal -L/usr/local/lib

# Bibliotecas a linkar (todas as flags -l)

LDLIBS = -liec61850 -lpthread -lm -lsqlite3 -lwiringPiDev -lwiringPi

# --- Regras do Make ---

all: $(TARGET)

# Como construir o TARGET
$(TARGET): $(SRCS)

	gcc $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS) $(LDLIBS)

# "make clean"
clean:
	rm -f $(TARGET)
