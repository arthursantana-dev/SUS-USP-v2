#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../historico/historico.h"

struct Paciente
{
    char *nome;
    int id;
    int risco; /* 1-5 (máx - mín)*/
    bool esta_em_triagem;
    HISTORICO *historico;
};

PACIENTE *paciente_criar(char *nome, int id, int risco, bool esta_em_triagem)
{
    PACIENTE *paciente = (PACIENTE *)calloc(1, sizeof(PACIENTE));

    if (paciente == NULL)
        return NULL;

    paciente->nome = (char *)malloc(strlen(nome) + 1);
    paciente->esta_em_triagem = esta_em_triagem;
    paciente->risco = risco;

    if (paciente->nome == NULL)
    {
        free(paciente);
        paciente = NULL;
        return NULL;
    }

    strcpy(paciente->nome, nome);

    paciente->historico = historico_criar();

    if (paciente->historico == NULL)
    {
        free(paciente->nome);
        free(paciente);
        paciente = NULL;
        return NULL;
    }

    paciente->id = id;

    return paciente;
}

char *paciente_get_nome(PACIENTE *paciente)
{
    if (paciente == NULL)
        return NULL;

    return paciente->nome;
}

int paciente_get_id(PACIENTE *paciente)
{
    if (paciente == NULL)
        return 0;

    return paciente->id;
}

void set_esta_em_triagem(PACIENTE* paciente, bool status){
    if(paciente == NULL) return;
    paciente->esta_em_triagem = status;
}

bool get_esta_em_triagem(PACIENTE* paciente){
    if(paciente == NULL) return false;
    return paciente->esta_em_triagem;
}

int paciente_get_risco(PACIENTE *paciente){
    if (paciente == NULL)
        return -1;

    return paciente->risco;
}

void paciente_remover(PACIENTE **paciente)
{
    if (*paciente == NULL)
        return;


    free((*paciente)->nome);
    free(*paciente);
    *paciente = NULL;
}

void paciente_remover_ponteiro(PACIENTE* paciente){
    if (paciente == NULL)
        return;

    free(paciente->nome);
    free(paciente);
}

bool comparar_pacientes(void *p1, void *p2)
{
    if (p1 == NULL || p2 == NULL)
        return false;

    PACIENTE *paciente1 = (PACIENTE *)p1;
    PACIENTE *paciente2 = (PACIENTE *)p2;

    return (paciente1->id == paciente2->id) && (strcmp(paciente1->nome, paciente2->nome) == 0);
}

bool paciente_adicionar_procedimento(PACIENTE *paciente, char *procedimento)
{
    if (paciente == NULL || strlen(procedimento) == 0 || paciente->historico == NULL)
        return false;

    historico_inserir(paciente->historico, procedimento);
    return true;
}

bool paciente_remover_procedimento(PACIENTE *paciente)
{
    if (paciente == NULL || paciente->historico == NULL)
        return false;

    return historico_remover(paciente->historico);
}

void paciente_listar_procedimentos(PACIENTE *paciente)
{
    if (paciente == NULL || paciente->historico == NULL)
    {
        printf("Erro: Impossível listar procedimentos. Paciente ou histórico nulo.\n");
        return;
    }

    printf("Procedimentos do paciente %s (ID: %d):\n", paciente->nome, paciente->id);

    char *lista_procedimentos = historico_listar(paciente->historico);

    if (lista_procedimentos == NULL)
    {
        printf(" -> Nenhum procedimento registrado ou falha na alocação de memória.\n\n");
    }
    else
    {
        printf("%s\n", lista_procedimentos);

        free(lista_procedimentos);
        lista_procedimentos = NULL;
    }
}

HISTORICO *paciente_get_historico(PACIENTE *paciente)
{
    if (paciente == NULL)
        return NULL;

    return paciente->historico;
}