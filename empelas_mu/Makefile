# Makefile - EmpElas_MU (Pi 3: merging unit)
#
# Compila contra a libiec61850 INSTALADA NO SISTEMA (/usr/local), igual aos
# outros IEDs do projeto.
#
#   make                 compila (com o botao fisico; precisa do wiringPi)
#   make SEM_BOTAO=1     compila sem o botao fisico (falta so pelo supervisorio)
#   make modelo          regenera static_model.c/.h a partir do .icd
#   make testes          compila os programas de teste da pasta testes/
#   make clean           apaga os binarios
#
# Se a biblioteca tiver sido instalada em outro prefixo:
#   make PREFIX=/opt/libiec61850

PREFIX ?= /usr/local

TARGET = empelas_mu
SRCS   = server_mu.c static_model.c
ICD    = empelas_mu.icd

# genmodel: usa o que veio com a libiec61850 clonada nesta Pi (mesma versao
# da biblioteca). Se nao existir, usa o da raiz do repositorio.
GENMODEL ?= $(firstword $(wildcard $(HOME)/libiec61850/tools/model_generator/genmodel.jar) ../genmodel.jar)

CC       = gcc
CFLAGS   = -g -Wall -O2
CPPFLAGS = -I$(PREFIX)/include/libiec61850 -I$(PREFIX)/include
LDFLAGS  = -L$(PREFIX)/lib
LIBS     = -liec61850 -lpthread -lm -lrt
# Se o link reclamar de simbolos sqlite3_*, acrescente:  LIBS += -lsqlite3

ifdef SEM_BOTAO
CPPFLAGS += -DSEM_BOTAO
else
LIBS += -lwiringPi
endif

.PHONY: all modelo testes clean

all: $(TARGET)

$(TARGET): $(SRCS) static_model.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)
	@echo ""
	@echo "Pronto. Rode com:  sudo ./$(TARGET)"

# O modelo e gerado sozinho na primeira compilacao (ou quando o .icd mudar)
static_model.c: $(ICD)
	java -jar $(GENMODEL) $(ICD)

static_model.h: static_model.c

modelo:
	java -jar $(GENMODEL) $(ICD)
	@echo ""
	@echo "Modelo regenerado. Recompile com 'make'."

testes: testes/teste_sv testes/falta

testes/teste_sv: testes/teste_sv.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) -liec61850 -lpthread -lm -lrt

testes/falta: testes/falta.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) -liec61850 -lpthread -lm -lrt

clean:
	rm -f $(TARGET) *.o testes/teste_sv testes/falta
