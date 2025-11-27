#ifndef AVL_H
#define AVL_H

#include <stdbool.h>

#include "../no/no.h"

typedef struct Avl AVL;

AVL *avl_criar(int (*comparar)(void *a, void *b), void (*imprimir)(void *valor), void (*apagar)(void *valor), int (*get_chave)(void *valor));

NO* avl_get_raiz(AVL* avl);

void avl_set_raiz(AVL* avl, NO* no);

NO* avl_inserir(AVL* avl, void* valor);

void avl_apagar(AVL **avl);

bool avl_buscar(AVL *avl, void *valor);

void avl_imprimir(AVL *avl);

bool avl_remover(AVL* avl, void* id);

#endif