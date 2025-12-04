
# Makefile gerado: compila main e módulos dependentes
# Variáveis
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -O2 -g -I. -MMD -MP
LDFLAGS :=
TARGET := main

# Lista de fontes - adicione/remova arquivos conforme necessário
SRCS := main.c \
        avl/avl.c \
        no/no.c \
		paciente/paciente.c \
		avl_pacientes/avl_pacientes.c \
		heap/heap.c \
		fila_espera/fila_espera.c \
		IO/IO.c

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Regra genérica para compilar .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Incluir dependências geradas (.d) se existirem
-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

run: all
	./$(TARGET)

