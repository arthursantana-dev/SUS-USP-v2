#include "pilha.h"
#include "../no_pilha/no.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha
{
    int tamanho;
    NO_P *topo;
};

PILHA *pilha_criar()
{

    PILHA *p = (PILHA *)malloc(sizeof(PILHA));

    if (p != NULL)
    {
        p->tamanho = 0;
        p->topo = NULL;
    }

    return p;
}

bool pilha_vazia(PILHA *p)
{
    if (p != NULL)
    {
        return p->tamanho == 0;
    }

    return false;
}

bool pilha_cheia(PILHA *p)
{
    if (p != NULL)
    {

        NO_P *tentativa = no_p_criar(NULL, NULL);

        if (tentativa == NULL)
        {
            return true;
        }

        free(tentativa);
        return false;
    }

    return false;
}

int pilha_tamanho(PILHA *p)
{

    if (p != NULL)
    {
        return p->tamanho;
    }

    return -1;
}

bool pilha_empilhar(PILHA *p, void *valor)
{
    if (p == NULL)
    {
        return false;
    }

    NO_P *novo_no = no_p_criar(valor, NULL);

    if (novo_no == NULL)
    {
        return false;
    }

    no_p_set_anterior(novo_no, p->topo);

    p->topo = novo_no;
    p->tamanho++;

    return true;
}

void *pilha_desempilhar(PILHA *p)
{
    NO_P *no;
    if ((p != NULL) && (!pilha_vazia(p)))
    {

        no = pilha_topo(p);

        void *no_p_valor = no_p_get_valor(no);

        p->topo = no_p_get_anterior(no);

        no_p_remover(&no);

        p->tamanho--;

        return no_p_valor;
    }

    return NULL;
}

NO_P *pilha_topo(PILHA *p)
{
    if (p != NULL && p->tamanho > 0)
    {
        return p->topo;
    }

    return NULL;
}

void pilha_apagar(PILHA **p)
{
    if(pilha_vazia(*p)){
        free(*p);
        *p = NULL;
        return;
    }

    if (*p == NULL)
        return;

    NO_P *no_p_temp = pilha_topo(*p);

    while ((*p)->topo != NULL)
    {
        no_p_temp = (*p)->topo;
        // printf("valor_no: %s ", no_p_get_valor(no_p_temp));
        (*p)->topo = no_p_get_anterior(no_p_temp);
        no_p_remover(&no_p_temp);
        no_p_set_anterior(no_p_temp, NULL);
        free(no_p_temp);
        no_p_temp = NULL;
    }

    free(*p);
    *p = NULL;
}
