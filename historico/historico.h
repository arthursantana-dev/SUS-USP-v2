#ifndef HISTORICO_H
#define HISTORICO_H

#include "../no_pilha/no.h"
#include <stdbool.h>

typedef struct Historico HISTORICO;

HISTORICO* historico_criar();

void historico_apagar(HISTORICO **historico);

bool historico_inserir(HISTORICO* historico, char* procedimento);

bool historico_remover(HISTORICO* historico);

bool historico_vazio(HISTORICO *historico);

char* historico_listar(HISTORICO* historico);

int historico_tamanho(HISTORICO *historico);

NO_P* historico_get_topo(HISTORICO *historico);

#endif