#include "avl_pacientes.h"
#include "../avl/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../paciente/paciente.h"

struct Avl_Pacientes {
    int (*comparar)(void *a, void *b);
    void (*imprimir)(void *valor);
    AVL *a;
};

int comparar_ids(void *a, void *b) {
    int int_a = paciente_get_id((PACIENTE *)a);
    int int_b = paciente_get_id((PACIENTE *)b);

    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

void imprimir_paciente(void *valor) {
    PACIENTE *paciente = (PACIENTE *)valor;
    if (paciente != NULL) {
        printf("Paciente ID: %d, Nome: %s, Risco: %d\n", paciente_get_id(paciente), paciente_get_nome(paciente), paciente_get_risco(paciente));
    }
}

int avl_pacientes_get_chave(void *valor) {
    return (int)valor;
}

void avl_pacientes_apagar_paciente(void *valor) {
    PACIENTE *paciente = (PACIENTE *)valor;
    if (paciente != NULL) {
        paciente_remover_ponteiro(paciente);
        free(paciente);
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
    if (*avl_pacientes != NULL) {
        free(*avl_pacientes);
        *avl_pacientes = NULL;
    }
}

bool avl_pacientes_remover(AVL_PACIENTES* avl_pacientes, int id){
    if(avl_pacientes == NULL) return false;

    void* id_ptr = &id;

    return avl_remover(avl_pacientes->a, id_ptr);
}

void avl_pacientes_imprimir(const AVL_PACIENTES *avl_pacientes) {
    if (avl_pacientes == NULL) return;

    printf("Imprimindo AVL de Pacientes:\n");
    avl_imprimir(avl_pacientes->a);
    printf("\n");
}

void avl_pacientes_buscar(AVL_PACIENTES *avl_pacientes, int id){
    PACIENTE* paciente = paciente_criar("", id, 0, false);
    if(avl_pacientes == NULL || paciente == NULL) return;
    bool encontrado = avl_buscar(avl_pacientes->a, paciente);
    if(encontrado){
        printf("Paciente com ID %d encontrado na AVL.\n", paciente_get_id(paciente));
    } else {
        printf("Paciente com ID %d não encontrado na AVL.\n", paciente_get_id(paciente));
    }
}