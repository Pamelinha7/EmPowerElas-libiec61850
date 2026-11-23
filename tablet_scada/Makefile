# Makefile - ponte MMS do SCADA do tablet
#
# Compila contra a libiec61850 instalada no sistema (a mesma das Pis).
#
#   make            compila a ponte
#   make clean      apaga o binario
#
# Se a biblioteca estiver em outro prefixo:  make PREFIX=/opt/libiec61850

PREFIX ?= /usr/local

CC       = gcc
CFLAGS   = -g -Wall -O2
CPPFLAGS = -I$(PREFIX)/include/libiec61850 -I$(PREFIX)/include
LDFLAGS  = -L$(PREFIX)/lib
LIBS     = -liec61850 -lpthread -lm -lrt

# A libiec61850 das Pis da maquete foi compilada com o log em sqlite, entao
# o link precisa do -lsqlite3 (igual aos Makefiles do projeto). Se em outra
# maquina ele reclamar que nao encontra o -lsqlite3, rode:  make SQLITE=
SQLITE ?= -lsqlite3
LIBS += $(SQLITE)

.PHONY: all clean

all: ponte

ponte: ponte.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) $(LIBS)
	@echo ""
	@echo "Pronto. Agora rode:  python3 servidor.py"

clean:
	rm -f ponte
