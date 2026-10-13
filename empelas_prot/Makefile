# Makefile - EmpElas_PROT (Pi 1: medicao, protecao e assinatura do SV)
#
# Compila contra a libiec61850 INSTALADA NO SISTEMA, nao contra a arvore
# de codigo da biblioteca. Por isso este diretorio pode ficar em qualquer
# lugar - inclusive num clone do repositorio.
#
#   make            compila
#   make modelo     regenera static_model.c/.h a partir do .icd
#   make testes     compila os testes: manobra (comandar chaves e disjuntores pelo
#                   terminal), ver_goose (ver os GOOSE da maquete chegando) e
#                   ver_eventos (lista de eventos das tres Pis, com horario)
#   make clean      apaga o binario e os objetos
#
# Se a biblioteca tiver sido instalada em outro prefixo:
#   make PREFIX=/opt/libiec61850

PREFIX ?= /usr/local

TARGET = empelas_prot
SRCS   = server_prot.c static_model.c
ICD    = empelas_prot.icd

CC      = gcc
CFLAGS  = -g -Wall -O2
CPPFLAGS = -I$(PREFIX)/include/libiec61850 -I$(PREFIX)/include
LDFLAGS  = -L$(PREFIX)/lib

# wiringPiDev traz a biblioteca de LCD (lcd.h), usada pelos dois displays.
LIBS = -liec61850 -lwiringPi -lwiringPiDev -lpthread -lm -lrt

# Algumas compilacoes da libiec61850 incluem suporte a log em sqlite.
# Se o link reclamar de simbolos sqlite3_*, mantenha esta linha.
# Se reclamar que nao encontra -lsqlite3, comente-a.
LIBS += -lsqlite3

.PHONY: all modelo testes clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)
	@echo ""
	@echo "Pronto. Rode com:  sudo ./$(TARGET)"

# Regenera o modelo a partir do SCL. Necessario apenas quando o .icd muda.
# Os arquivos gerados sao versionados, entao um clone limpo ja compila
# sem precisar deste alvo.
# Usa o genmodel que veio com a libiec61850 clonada nesta Pi (mesma versao
# da biblioteca); se nao existir, usa o da raiz do repositorio.
GENMODEL ?= $(firstword $(wildcard $(HOME)/libiec61850/tools/model_generator/genmodel.jar) ../genmodel.jar)

modelo:
	java -jar $(GENMODEL) $(ICD)
	@echo ""
	@echo "Modelo regenerado. Recompile com 'make' e reimporte o $(ICD) no SCADA."

# Ferramenta de teste: so precisa da libiec61850 (roda em qualquer Pi da maquete)
testes: testes/manobra testes/ver_goose testes/ver_eventos

testes/manobra: testes/manobra.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) -liec61850 -lpthread -lm -lrt $(filter -lsqlite3,$(LIBS))
	@echo ""
	@echo "Pronto. Exemplo:  ./testes/manobra 192.168.10.101 chave 1 abrir"

testes/ver_goose: testes/ver_goose.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) -liec61850 -lpthread -lm -lrt $(filter -lsqlite3,$(LIBS))
	@echo ""
	@echo "Pronto. Rode com:  sudo ./testes/ver_goose"

testes/ver_eventos: testes/ver_eventos.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) -liec61850 -lpthread -lm -lrt $(filter -lsqlite3,$(LIBS))
	@echo ""
	@echo "Pronto. Rode com:  ./testes/ver_eventos"

clean:
	rm -f $(TARGET) *.o testes/manobra testes/ver_goose testes/ver_eventos
