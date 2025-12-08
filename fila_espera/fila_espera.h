#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include "../paciente/paciente.h"
#include <stdbool.h>

typedef struct fila_espera FILA_ESPERA;

/*
 * Cria uma fila de prioridade (Min-Heap) com capacidade definida.
 * A prioridade é baseada no Risco (menor valor = maior urgência).
 */
FILA_ESPERA* fila_criar(int capacidade);

/*
 * Insere um paciente na fila de espera.
 * O paciente é organizado automaticamente conforme seu risco.
 */
bool fila_inserir(FILA_ESPERA* f, PACIENTE* paciente);

/*
 * Remove e retorna o paciente com maior prioridade (menor risco/topo da heap).
 * Não libera a memória do paciente, apenas o retira da fila.
 */
PACIENTE* fila_remover(FILA_ESPERA* f);

/* Retorna o próximo paciente a ser atendido sem removê-lo da fila. */
PACIENTE* fila_consultar_proximo(FILA_ESPERA* f);

/* Imprime o estado atual da fila (geralmente usada para debug). */
void fila_imprimir(FILA_ESPERA *f);

/* Retorna a quantidade de pacientes na fila. */
int fila_tamanho(FILA_ESPERA* f);

/*
 * Libera a estrutura da fila.
 * Nota: Não apaga os pacientes, pois eles pertencem à AVL (Banco de Dados).
 */
void fila_apagar(FILA_ESPERA** f);

/* Função auxiliar para extrair a prioridade (risco) de um dado genérico. */
int fila_obter_prioridade_paciente(void* dado);

#endif