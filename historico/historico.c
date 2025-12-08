#include "historico.h"
#include "../no_pilha/no.h"
#include "../pilha/pilha.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Historico
{
    PILHA *h;
};

HISTORICO *historico_criar()
{

    HISTORICO *historico = (HISTORICO *)malloc(sizeof(HISTORICO));

    if (historico == NULL)
    {
        return NULL;
    }

    historico->h = pilha_criar();
    if (historico->h == NULL)
    {
        free(historico);
        return NULL;
    }

    return historico;
}

// Limpa o histórico, apagando-o em seguida
void historico_apagar(HISTORICO **historico)
{
    while (!historico_vazio(*historico))
    {
        char *procedimento = (char *)no_p_get_valor(pilha_topo((*historico)->h));
        pilha_desempilhar((*historico)->h);
        free(procedimento);
    }

    // Destrói a pilha
    pilha_apagar(&((*historico)->h));

    // Libera o histórico
    free(*historico);
}

bool historico_vazio(HISTORICO *historico)
{
    return pilha_vazia(historico->h);
}

bool historico_inserir(HISTORICO *historico, char *procedimento)
{
    if (historico != NULL && procedimento != NULL)
    {
        // Cria uma cópia do procedimento para armazenar
        char *copia = (char *)malloc(strlen(procedimento) + 1);

        if (copia == NULL)
            return false;

        strcpy(copia, procedimento);

        bool sucesso = pilha_empilhar(historico->h, copia);

        if (!sucesso)
        {
            free(copia);
            return false;
        }

        return true;
    }

    return false;
}

bool historico_remover(HISTORICO *historico)
{
    if (historico != NULL)
    {
        char *procedimento = (char *)no_p_get_valor(pilha_topo(historico->h));
        pilha_desempilhar(historico->h);
        free(procedimento);
        return true;
    }

    return false;
}

char *historico_concatenar(char *destino, char *origem)
{
    if (origem == NULL)
        return destino;

    if (destino == NULL)
    {
        char *nova = (char *)malloc(strlen(origem) + 1);
        if (nova != NULL)
            strcpy(nova, origem);
        return nova;
    }

    size_t tamanho_atual = strlen(destino);
    size_t tamanho_origem = strlen(origem);
    size_t tamanho_total = tamanho_atual + tamanho_origem + 1;

    char *novo_destino = (char *)realloc(destino, tamanho_total);
    if (novo_destino == NULL)
    {
        free(destino);
        return NULL;
    }

    strcat(novo_destino, origem);
    return novo_destino;
}

// Método para percorrer o histórico (pilha) e listar os procedimentos em ordem
char *historico_listar(HISTORICO *historico)
{

    //printf("Histórico listar debug\n");

    if (historico == NULL)
        return NULL;

    //printf("historico nao nulo\n");

    NO_P *no = pilha_topo(historico->h);
    char *lista = NULL;
    char *quebra_linha = "\n";

    // printf("historico_listar debug\n");

    while (no != NULL)
    {
        char *procedimento = (char *)no_p_get_valor(no);

        // printf("proc(listar): %s\n", procedimento);

        // Concatena o procedimento
        lista = historico_concatenar(lista, procedimento);
        if (lista == NULL)
            return NULL;

        // printf("%s", lista);

        no = no_p_get_anterior(no);

        // Adiciona quebra de linha se não for o último elemento
        if (no != NULL)
        {
            lista = historico_concatenar(lista, quebra_linha);
            if (lista == NULL)
                return NULL;
        }
    }

    lista = historico_concatenar(lista, quebra_linha);

    // printf("%s", lista);

    return lista;
}

int historico_tamanho(HISTORICO *historico)
{
    if (historico && historico->h)
    {
        return pilha_tamanho(historico->h);
    }
    return 0;
}

NO_P *historico_get_topo(HISTORICO *historico)
{
    if (historico && historico->h)
    {
        return pilha_topo(historico->h);
    }
    return NULL;
}

size_t historico_calcular_tamanho_total(HISTORICO *historico)
{
    if (historico == NULL)
        return 0;

    size_t tamanho_total = 1; 
    NO_P *no = pilha_topo(historico->h);
    int count = 0;

    while (no != NULL)
    {
        char *procedimento = (char *)no_p_get_valor(no);
        if (procedimento != NULL)
        {
            tamanho_total += strlen(procedimento);
            count++;
        }
        no = no_p_get_anterior(no);
    }

    if (count > 1)
        tamanho_total += (count - 1);

    return tamanho_total;
}
