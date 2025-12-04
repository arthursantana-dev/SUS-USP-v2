#ifndef IO_H
#define IO_H

#include "../avl_pacientes/avl_pacientes.h"
#include "../fila_espera/fila_espera.h"

void IO_SAVE(AVL_PACIENTES *avl, const char *nome_arquivo);

void IO_LOAD(AVL_PACIENTES *avl, FILA_ESPERA *fila, const char *nome_arquivo);

#endif