#ifndef HISTORICO_H
#define HISTORICO_H

#include "../no_pilha/no.h"
#include <stdbool.h>

typedef struct Historico HISTORICO;

/*
 * Aloca e inicializa uma estrutura de histórico (contendo uma pilha).
 * Retorna NULL se falhar a alocação.
 */
HISTORICO* historico_criar();

/*
 * Esvazia a pilha interna, liberando as strings dos procedimentos,
 * destrói a pilha e libera a struct historico.
 */
void historico_apagar(HISTORICO **historico);

/*
 * Empilha um novo procedimento.
 * Cria uma cópia da string passada para armazenar na pilha.
 */
bool historico_inserir(HISTORICO* historico, char* procedimento);

/*
 * Remove o procedimento do topo da pilha e libera a memória da string.
 * Retorna false se o histórico estiver vazio.
 */
bool historico_remover(HISTORICO* historico);

/* Verifica se não há procedimentos registrados. */
bool historico_vazio(HISTORICO *historico);

/*
 * Cria uma única string contendo todos os procedimentos concatenados,
 * separados por quebra de linha.
 * ATENÇÃO: A string retornada é alocada dinamicamente e DEVE ser liberada (free) pelo chamador.
 */
char* historico_listar(HISTORICO* historico);

/* Retorna a quantidade de procedimentos no histórico. */
int historico_tamanho(HISTORICO *historico);

/* Retorna o nó do topo da pilha (uso interno/avançado). */
NO_P* historico_get_topo(HISTORICO *historico);

#endif