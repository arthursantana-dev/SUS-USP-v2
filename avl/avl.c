#include "avl.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)

struct Avl
{
    NO *raiz;
    int profundidade;

    int (*comparar)(int a, int b);
    void (*imprimir)(void *valor);
    void (*apagar)(void *valor);
    int (*get_chave)(void *valor);
};

AVL *avl_criar(int (*comparar)(int a, int b), void (*imprimir)(void *valor), void (*apagar)(void *valor), int (*get_chave)(void *valor))
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

void avl_apagar_auxiliar(AVL* avl,NO *no)
{
    if (no == NULL)
        return;

    avl->apagar(no_get_valor(no));

    avl_apagar_auxiliar(avl, no_get_esquerda(no));
    avl_apagar_auxiliar(avl, no_get_direita(no));
    no_remover(&no);
    free(no);
}

void avl_apagar(AVL **avl)
{
    if (*avl != NULL)
    {
        avl_apagar_auxiliar(*avl, (*avl)->raiz);
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

NO *avl_inserir_auxiliar(AVL *avl, NO *no, NO* no_a_ser_inserido)
{
    // printf("Inserindo valor auxiliar: %d\n", avl->get_chave(no_get_valor(no_a_ser_inserido)));

    if (no == NULL)
    {
        // printf("\tFolha\n");
        no = no_a_ser_inserido;
    }
    else if (avl->comparar(avl->get_chave(no_get_valor(no_a_ser_inserido)), avl->get_chave(no_get_valor(no))) <= 0)
    {
        // printf("\tEsquerda\n");

        no_set_esquerda(no, avl_inserir_auxiliar(avl, no_get_esquerda(no), no_a_ser_inserido));
    }
    else
    {
        // printf("\tDireita\n");

        no_set_direita(no, avl_inserir_auxiliar(avl, no_get_direita(no), no_a_ser_inserido));
    }

    no_set_altura(no, 1 + max(no_get_altura(no_get_esquerda(no)), no_get_altura(no_get_direita(no))));

    int fb = no_calcular_fator_balanceamento(no);
    // printf("\tFator de balanceamento do nó %d: %d\n", avl->get_chave(no_get_valor(no)), fb);

    if (fb == -2)
    {
        // printf("\tfb filho esquerdo: %d\n", no_calcular_fator_balanceamento(no_get_esquerda(no)));
        if (no_calcular_fator_balanceamento(no_get_esquerda(no)) <= 0)
        {
            // printf("\tRotação Esquerda\n");
            no = rodar_esquerda(no);
        }
        else
        {
            // printf("\tRotação Direita-Esquerda\n");
            no = rodar_direita_esquerda(no);
        }
    }

    if (fb == 2)
    {
        int fb_direita = no_calcular_fator_balanceamento(no_get_direita(no));
        if (fb_direita > 0)
        {
            // printf("\tRotação Direita\n");
            no = rodar_direita(no);
        }
        else
        {
            // printf("\tRotação Esquerda-Direita\n");
            no = rodar_esquerda_direita(no);
        }
    }

    return no;
}

NO *avl_inserir(AVL *avl, void *valor)
{
    if (avl == NULL || valor == NULL)
        return NULL;

    // printf("Inserindo valor: %d\n", *(int *)valor);

    NO* no_a_ser_inserido = no_criar(valor, NULL, NULL, 0, 0);

    avl->raiz = avl_inserir_auxiliar(avl, avl->raiz, no_a_ser_inserido);

    return avl->raiz;
}

bool avl_buscar_auxiliar(AVL *avl, NO *raiz, int valor)
{
    if (raiz == NULL)
        return false;

    int cmp = avl->comparar(valor, avl->get_chave(no_get_valor(raiz)));

    if (cmp == 0)
        return true;
    else if (cmp < 0)
        return avl_buscar_auxiliar(avl, no_get_esquerda(raiz), valor);
    else
        return avl_buscar_auxiliar(avl, no_get_direita(raiz), valor);
}

void* avl_recuperar_auxiliar(AVL *avl, NO *raiz, int valor)
{
    if (raiz == NULL)
        return false;

    int cmp = avl->comparar(valor, avl->get_chave(no_get_valor(raiz)));

    if (cmp == 0)
        return no_get_valor(raiz);
    else if (cmp < 0)
        return avl_recuperar_auxiliar(avl, no_get_esquerda(raiz), valor);
    else
        return avl_recuperar_auxiliar(avl, no_get_direita(raiz), valor);
}

void* avl_recuperar(AVL *avl, int valor)
{
    if (avl == NULL)
        return NULL;

    return avl_recuperar_auxiliar(avl, avl->raiz, valor);
}

bool avl_buscar(AVL *avl, int valor)
{
    if (avl == NULL || valor == 0)
        return false;

    return avl_buscar_auxiliar(avl, avl->raiz, valor);
}

void avl_imprimir_auxiliar(AVL *avl, NO *no)
{
    if (no == NULL)
        return;

    avl_imprimir_auxiliar(avl, no_get_esquerda(no));
    avl->imprimir(no_get_valor(no));
    avl_imprimir_auxiliar(avl, no_get_direita(no));
}

void avl_imprimir(AVL *avl)
{
    if (avl == NULL)
        return;
    avl_imprimir_auxiliar(avl, avl->raiz);
    printf("\n");
}

NO *avl_remover_auxiliar(AVL *avl, NO *raiz, int id)
{
    NO *p;

    if (raiz == NULL)
        return NULL;

    // printf("chave raiz: %d\n", avl->get_chave(no_get_valor(raiz)));

    // printf("%d\n",avl->comparar(id, avl->get_chave(no_get_valor(raiz))));

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
            no_remover_ponteiro(p);
            p = NULL;
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

bool avl_remover(AVL *avl, int id)
{
    NO *raiz = avl_get_raiz(avl);

    avl_set_raiz(avl, avl_remover_auxiliar(avl, raiz, id));

    return avl_get_raiz(avl) != NULL;
}

void avl_percorrer_aux(NO *no, void (*funcao)(void *dado, void *args), void *args)
{
    if (no == NULL)
        return;

    funcao(no_get_valor(no), args);

    avl_percorrer_aux(no_get_esquerda(no), funcao, args);
    avl_percorrer_aux(no_get_direita(no), funcao, args);
}

void avl_percorrer(AVL *avl, void (*funcao)(void *dado, void *args), void *args)
{
    if (avl == NULL || funcao == NULL)
        return;

    avl_percorrer_aux(avl->raiz, funcao, args);
}