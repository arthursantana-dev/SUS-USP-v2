#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include "../paciente/paciente.h"
#include <stdbool.h>

typedef struct fila_espera FILA_ESPERA;

FILA_ESPERA* fila_criar(int capacidade);

bool fila_inserir(FILA_ESPERA* f, PACIENTE* paciente);

PACIENTE* fila_remover(FILA_ESPERA* f);

PACIENTE* fila_consultar_proximo(FILA_ESPERA* f);

void fila_imprimir(FILA_ESPERA *f);

int fila_tamanho(FILA_ESPERA* f);

void fila_apagar(FILA_ESPERA** f);

int fila_obter_prioridade_paciente(void* dado);

#endif