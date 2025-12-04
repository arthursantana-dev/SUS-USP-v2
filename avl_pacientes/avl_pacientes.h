#ifndef AVL_PACIENTES_H
#define AVL_PACIENTES_H

#include "paciente/paciente.h"

typedef struct Avl_Pacientes AVL_PACIENTES;

AVL_PACIENTES* avl_pacientes_criar();

void avl_pacientes_inserir(AVL_PACIENTES *avl_pacientes, PACIENTE *paciente);

void avl_pacientes_apagar(AVL_PACIENTES **avl_pacientes);

void avl_pacientes_buscar(AVL_PACIENTES *avl_pacientes, int id);

bool avl_pacientes_remover(AVL_PACIENTES* avl_pacientes, int id);

void avl_pacientes_imprimir(const AVL_PACIENTES *avl_pacientes);

void avl_pacientes_percorrer(AVL_PACIENTES *avl_pacientes, void (*funcao)(void *paciente, void *args), void *args);

#endif