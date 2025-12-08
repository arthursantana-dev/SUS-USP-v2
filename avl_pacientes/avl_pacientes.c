#include "avl_pacientes.h"
#include "../avl/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../paciente/paciente.h"
#include "../historico/historico.h"

struct Avl_Pacientes {
    int (*comparar)(int a, int b);
    void (*imprimir)(void *valor);
    AVL *a;
};

int comparar_ids(int a, int b) {

    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

static void imprimir_paciente(void *valor) {
    PACIENTE *paciente = (PACIENTE *)valor;
    if (paciente != NULL) {
        printf("Paciente ID: %d, Nome: %s, Risco: %d\n", paciente_get_id(paciente), paciente_get_nome(paciente), paciente_get_risco(paciente));
    }
}

int avl_pacientes_get_chave(void *valor) {
    PACIENTE *paciente = (PACIENTE *)valor;
    int id = paciente_get_id(paciente);
    return id;
}

void avl_pacientes_apagar_paciente(void *valor) {
    PACIENTE *paciente = (PACIENTE *)valor;
    if (paciente != NULL) {
        paciente_remover_ponteiro(paciente);
    }
}

AVL_PACIENTES* avl_pacientes_criar() {
    AVL_PACIENTES *avl_pacientes = (AVL_PACIENTES*) malloc(sizeof(AVL_PACIENTES));
    if (avl_pacientes != NULL) {
        avl_pacientes->comparar = comparar_ids;
        avl_pacientes->imprimir = imprimir_paciente;
        avl_pacientes->a = avl_criar(avl_pacientes->comparar, avl_pacientes->imprimir, avl_pacientes_apagar_paciente, avl_pacientes_get_chave);
    }
    return avl_pacientes;
}

void avl_pacientes_inserir(AVL_PACIENTES *avl_pacientes, PACIENTE *paciente){
    if (avl_pacientes == NULL || paciente == NULL) return;

    avl_inserir(avl_pacientes->a, paciente);
}

void avl_pacientes_apagar(AVL_PACIENTES **avl_pacientes) {
    if (avl_pacientes == NULL || *avl_pacientes == NULL) return;
    avl_apagar(&((*avl_pacientes)->a));
    free(*avl_pacientes);
}

bool avl_pacientes_remover(AVL_PACIENTES* avl_pacientes, int id){
    if(avl_pacientes == NULL) return false;

    return avl_remover(avl_pacientes->a, id);
}

void avl_pacientes_imprimir(const AVL_PACIENTES *avl_pacientes) {
    if (avl_pacientes == NULL) return;

    printf("Imprimindo AVL de Pacientes:\n");
    avl_imprimir(avl_pacientes->a);
    printf("\n");
}

bool avl_pacientes_buscar(AVL_PACIENTES *avl_pacientes, int id){
    if(avl_pacientes == NULL) return false;

    bool encontrado = avl_buscar(avl_pacientes->a, id);
    if(encontrado){
        printf("Paciente com ID %d encontrado na AVL.\n", id);
    } else {
        printf("Paciente com ID %d não encontrado na AVL.\n", id);
    }

    return encontrado;
}

PACIENTE* avl_pacientes_recuperar(AVL_PACIENTES *avl_pacientes, int id) {
    if (avl_pacientes == NULL) return NULL;

    PACIENTE *paciente = (PACIENTE *)avl_recuperar(avl_pacientes->a, id);
    return paciente;
}

void avl_pacientes_percorrer(AVL_PACIENTES *avl_pacientes, void (*funcao)(void *paciente, void *args), void *args)
{
    if (avl_pacientes == NULL) return;
    
    avl_percorrer(avl_pacientes->a, funcao, args);
}

bool avl_pacientes_adicionar_procedimento(AVL_PACIENTES *avl_pacientes, int id, char *procedimento)
{
    if (avl_pacientes == NULL || procedimento == NULL) return false;

    PACIENTE *p = avl_pacientes_recuperar(avl_pacientes, id);
    if (p == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado.\n", id);
        return false;
    }

    return paciente_adicionar_procedimento(p, procedimento);
}

bool avl_pacientes_remover_procedimento(AVL_PACIENTES *avl_pacientes, int id)
{
    if (avl_pacientes == NULL) return false;

    PACIENTE *p = avl_pacientes_recuperar(avl_pacientes, id);
    if (p == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado.\n", id);
        return false;
    }

    return paciente_remover_procedimento(p);
}

void avl_pacientes_listar_procedimentos(AVL_PACIENTES *avl_pacientes, int id)
{
    if (avl_pacientes == NULL) return;

    PACIENTE *p = avl_pacientes_recuperar(avl_pacientes, id);
    if (p == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado.\n", id);
        return;
    }

    paciente_listar_procedimentos(p);
}