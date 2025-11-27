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
    void (*imprimir)(void *valor);
    void (*apagar)(void *valor);
    void *(*get_chave)(void *valor);
};

AVL *avl_criar(int (*comparar)(void *a, void *b), void (*imprimir)(void *valor), void (*apagar)(void *valor), int (*get_chave)(void *valor))
{
    AVL *avl = (AVL *)malloc(sizeof(AVL));
    if (avl != NULL)
    {
        avl->raiz = NULL;
        avl->profundidade = -1;
        avl->comparar = comparar;
        avl->imprimir = imprimir;
        avl->apagar = apagar;
        avl->get_chave = get_chave;
    }
    return avl;
}

void avl_set_raiz(AVL *avl, NO *no)
{
    if (avl == NULL)
        return;

    avl->raiz = no;
}

void avl_troca_maximo_esquerda(AVL *avl, NO *troca, NO *raiz, NO *anterior)
{
    if (no_get_direita(troca) != NULL)
    {
        avl_troca_maximo_esquerda(avl, no_get_direita(troca), raiz, troca);
    }
    else
    {

        if (raiz == anterior)
        {
            no_set_esquerda(anterior, no_get_esquerda(troca));
        }
        else
        {
            no_set_direita(anterior, no_get_esquerda(troca));
        }

        void *valor_raiz = no_get_valor(raiz);
        no_set_valor(raiz, no_get_valor(troca));
        avl->apagar(&valor_raiz);
        no_remover(&troca);
    }
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
    return rodar_esquerda(a);
}

NO *avl_inserir_auxiliar(AVL *avl, NO *no, void *valor)
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
    printf("\tFator de balanceamento do nó %d: %d\n", *(int *)no_get_valor(no), fb);

    if (fb == -2)
    {
        printf("\tfb filho esquerdo: %d\n", no_calcular_fator_balanceamento(no_get_esquerda(no)));
        if (no_calcular_fator_balanceamento(no_get_esquerda(no)) < 0)
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
        int fb_direita = no_calcular_fator_balanceamento(no_get_direita(no));
        if (fb_direita > 0)
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

bool avl_buscar_auxiliar(AVL *avl, NO *raiz, void *valor)
{
    if (raiz == NULL)
        return false;

    int cmp = avl->comparar(valor, no_get_valor(raiz));

    if (cmp == 0)
        return true;
    else if (cmp < 0)
        return avl_buscar_auxiliar(avl, no_get_esquerda(raiz), valor);
    else
        return avl_buscar_auxiliar(avl, no_get_direita(raiz), valor);
}

bool avl_buscar(AVL *avl, void *valor)
{
    if (avl == NULL || valor == NULL)
        return false;

    return avl_buscar_auxiliar(avl, avl->raiz, valor);
}

void avl_imprimir_auxiliar(AVL *avl, NO *no)
{
    if (no == NULL)
        return;

    avl_imprimir_auxiliar(avl, no_get_esquerda(no));
    avl->imprimir(no_get_valor(no));
    printf("\t%d\n\n", no_get_altura(no));
    avl_imprimir_auxiliar(avl, no_get_direita(no));
}

void avl_imprimir(AVL *avl)
{
    avl_imprimir_auxiliar(avl, avl->raiz);
    printf("\n");
}

NO *avl_remover_auxiliar(AVL *avl, NO *raiz, void *id)
{
    NO *p;

    if (raiz == NULL)
        return NULL;

    printf("%d\n",avl->comparar(id, avl->get_chave(no_get_valor(raiz))));

    if (avl->comparar(id, avl->get_chave(no_get_valor(raiz))) == 0)
    {
        if (no_get_esquerda(raiz) == NULL || no_get_direita(raiz) == NULL)
        {
            p = raiz;
            if (no_get_esquerda(raiz) == NULL)
            {
                raiz = no_get_direita(raiz);
            }
            else
            {
                raiz = no_get_esquerda(raiz);
            }

            avl->apagar(no_get_valor(p));
            no_remover(&p);
        }
        else
        {
            avl_troca_maximo_esquerda(avl, no_get_esquerda(raiz), raiz, raiz);
        }
    }
    else if (avl->comparar(id, avl->get_chave(no_get_valor(raiz))) == -1)
    {
        no_set_esquerda(raiz, avl_remover_auxiliar(avl, no_get_esquerda(raiz), id));
    }
    else if (avl->comparar(id, avl->get_chave(no_get_valor(raiz))) == 1)
    {
        no_set_direita(raiz, avl_remover_auxiliar(avl, no_get_direita(raiz), id));
    }

    if (raiz != NULL)
    {
        no_atualizar_altura(raiz);
        int fb = no_calcular_fator_balanceamento(raiz);
        if (fb == -2)
        {
            if (no_calcular_fator_balanceamento(no_get_direita(raiz)) < 0)
            {
                raiz = rodar_esquerda(raiz);
            }
            else
            {
                raiz = rodar_direita_esquerda(raiz);
            }
        }
        else if (fb == 2)
        {
            if (no_calcular_fator_balanceamento(no_get_esquerda(raiz)) > 0)
            {
                raiz = rodar_direita(raiz);
            }
            else
            {
                raiz = rodar_esquerda_direita(raiz);
            }
        }
    }
    return raiz;
}

bool avl_remover(AVL *avl, void *id)
{
    NO *raiz = avl_get_raiz(avl);

    printf("id: %d\n", id);

    avl_set_raiz(avl, avl_remover_auxiliar(avl, raiz, id));

    return avl_get_raiz(avl) != NULL;
}