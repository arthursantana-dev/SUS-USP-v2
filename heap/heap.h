#ifndef HEAP_H
#define HEAP_H

#include "no/no.h"

typedef struct heap HEAP;

typedef int (*FUNCAO_GET_PRIORIDADE)(void*);

HEAP* heap_criar(int capacidade_inicial, FUNCAO_GET_PRIORIDADE get_prioridade);

void heap_inserir(HEAP* heap, NO* no);

NO* heap_remover(HEAP* heap);

NO* heap_topo(HEAP* heap);

int heap_tamanho(HEAP* heap);

int heap_get_capacidade(HEAP* heap);

int heap_vazia(HEAP* heap);

int heap_cheia(HEAP* heap);

void heap_apagar(HEAP** heap);

int heap_get_prioridade_no(HEAP* heap, NO* no);

#endif