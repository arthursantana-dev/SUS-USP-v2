#ifndef AVL_H
#define AVL_H

#include "../no/no.h"

typedef struct Avl AVL;

AVL* avl_criar(int (*comparar)(void *a, void *b));

NO* avl_get_raiz(AVL* avl);

NO* avl_inserir(AVL* avl, void* valor);

void avl_apagar(AVL **avl);

void avl_imprimir(AVL *avl);

#endif