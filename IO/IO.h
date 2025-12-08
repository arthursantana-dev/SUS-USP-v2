#ifndef IO_H
#define IO_H

#include "../avl_pacientes/avl_pacientes.h"
#include "../fila_espera/fila_espera.h"

/*
 * Salva todos os dados da AVL em um arquivo binário.
 * Formato: ID, Risco, Flag Triagem, Tamanho Nome, Nome, Tamanho Histórico, Histórico.
 */
void IO_SAVE(AVL_PACIENTES *avl, const char *nome_arquivo);

/*
 * Carrega os dados do arquivo binário para a memória.
 * Popula a AVL com todos os pacientes.
 * Se o paciente estava em triagem (flag true), também o insere na Fila de Espera.
 */
void IO_LOAD(AVL_PACIENTES *avl, FILA_ESPERA *fila, const char *nome_arquivo);

#endif