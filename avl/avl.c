#include "avl.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)

struct Avl
{
    NO *raiz;
    int profundidade;

    int (*comparar)(void *a, void *b);
};

AVL *avl_criar(int (*comparar)(void *a, void *b))
{
    AVL *avl = (AVL *)malloc(sizeof(AVL));
    if (avl != NULL)
    {
        avl->raiz = NULL;
        avl->profundidade = -1;
        avl->comparar = comparar;
    }
    return avl;
}

void avl_apagar_auxiliar(NO *no)
{
    if (no == NULL)
        return;

    avl_apagar_auxiliar(no_get_esquerda(no));
    avl_apagar_auxiliar(no_get_direita(no));
    no_remover(&no);
    free(no);
}

void avl_apagar(AVL **avl)
{
    if (*avl != NULL)
    {
        avl_apagar_auxiliar((*avl)->raiz);
        free(*avl);
        *avl = NULL;
    }
}

NO *avl_get_raiz(AVL *avl)
{
    if (avl != NULL)
    {
        return avl->raiz;
    }
    return NULL;
}

NO *avl_criar_no(void *valor)
{
    return no_criar(valor, NULL, NULL, 0, 0);
}

NO *rodar_direita(NO *a)
{
    NO *b = no_get_esquerda(a);

    no_set_esquerda(a, no_get_direita(b));

    no_set_direita(b, a);

    // no_set_altura(a, max(no_get_altura(no_get_esquerda(a)), no_get_altura(no_get_direita(a))) + 1);
    // no_set_altura(b, max(no_get_altura(no_get_esquerda(b)), no_get_altura(no_get_direita(b))) + 1);

    no_atualizar_altura(a);
    no_atualizar_altura(b);

    return b;
}

NO *rodar_esquerda(NO *a)
{
    NO *b = no_get_direita(a);

    no_set_direita(a, no_get_esquerda(b));

    no_set_esquerda(b, a);

    no_atualizar_altura(a);
    no_atualizar_altura(b);

    return b;
}

NO *rodar_esquerda_direita(NO *a)
{
    no_set_esquerda(a, rodar_esquerda(no_get_esquerda(a)));
    return rodar_direita(a);
}

NO *rodar_direita_esquerda(NO *a)
{
    no_set_direita(a, rodar_direita(no_get_direita(a)));
    return rodar_direita(a);
}

NO *avl_inserir_auxiliar(AVL* avl, NO *no, void *valor)
{
    printf("Inserindo valor auxiliar: %d\n", *(int *)valor);

    if (no == NULL)
    {
        printf("\tFolha\n");
        no = avl_criar_no(valor);
    }
    else if (avl->comparar(valor, no_get_valor(no)) < 0)
    {
        printf("\tEsquerda\n");

        no_set_esquerda(no, avl_inserir_auxiliar(avl, no_get_esquerda(no), valor));
    }
    else
    {
        printf("\tDireita\n");

        no_set_direita(no, avl_inserir_auxiliar(avl, no_get_direita(no), valor));
    }

    no_set_altura(no, 1 + max(no_get_altura(no_get_esquerda(no)), no_get_altura(no_get_direita(no))));

    int fb = no_calcular_fator_balanceamento(no);

    if (fb == -2)
    {
        if (no_calcular_fator_balanceamento(no_get_esquerda(no)) <= 0)
        {
            printf("\tRotação Esquerda\n");
            no = rodar_esquerda(no);
        }
        else
        {
            printf("\tRotação Direita-Esquerda\n");
            no = rodar_direita_esquerda(no);
        }
    }

    if (fb == 2)
    {
        if (no_calcular_fator_balanceamento(no_get_direita(no)) >= 0)
        {
            printf("\tRotação Direita\n");
            no = rodar_direita(no);
        }
        else
        {
            printf("\tRotação Esquerda-Direita\n");
            no = rodar_esquerda_direita(no);
        }
    }

    printf("\tAltura do nó com valor %d: %d\n", *(int *)no_get_valor(no), no_get_altura(no));

    return no;
}

NO *avl_inserir(AVL *avl, void *valor)
{
    if (avl == NULL || valor == NULL)
        return NULL;

    printf("Inserindo valor: %d\n", *(int *)valor);

    avl->raiz = avl_inserir_auxiliar(avl, avl->raiz, valor);

    return avl->raiz;
}

void avl_imprimir_auxiliar(NO *no)
{
    if (no == NULL)
        return;

    avl_imprimir_auxiliar(no_get_esquerda(no));
    printf("%d ", *(int *)no_get_valor(no));
    avl_imprimir_auxiliar(no_get_direita(no));
}

void avl_imprimir(AVL *avl)
{
    avl_imprimir_auxiliar(avl->raiz);
    printf("\n");
}
