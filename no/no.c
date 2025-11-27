#include "no.h"
#include <stdio.h>
#include <stdlib.h>

/*Nó é uma estrutura genérica, seu valor pode apontar para qualquer coisa. Os TADs que o manipulam são, portanto, genéricos também. Assim, cada um desses TADs foi "englobado" por um TAD que manipula um tipo específico de dado. Ex: Nó <- lista <- lista_pacientes */
struct No {
    void* valor;
    NO* esquerda;
    NO* direita;
    int altura;
    int fator_balanceamento;
};

NO* no_criar(void* valor, NO* esquerda, NO* direita, int altura, int fator_balanceamento) {
    NO *no = (NO*) malloc(sizeof(NO));
    if (no != NULL) {
        no->valor = valor;
        no->esquerda = esquerda;
        no->direita = direita;
        no->altura = altura;
        no->fator_balanceamento = fator_balanceamento;
    }
    return no;
}


void no_remover(NO **no) {
    if (*no != NULL) {
        (*no)->valor = NULL;
        (*no)->esquerda = NULL;
        (*no)->direita = NULL;
        free(*no);
        *no = NULL;
    }
}

/*Método alternativo para remoção, pois um método get do TAD retorna um NO*, não NO**, e usar &no não funcionaria */
void no_remover_ponteiro(NO *no) {
    if (no != NULL) {
        no->valor = NULL;
        no->esquerda = NULL;
        no->direita = NULL;
        free(no);
    }
}

void* no_get_valor(NO* no){

    if(no != NULL){
        return no->valor;
    }

    return NULL;

}

void no_set_valor(NO* no, void* valor){
    if(no != NULL){
        no->valor = valor;
    }
}

int no_calcular_altura(NO* no) {
    if (no == NULL) {
        return -1;
    }
    int altura_esquerda = no_calcular_altura(no->esquerda);
    int altura_direita = no_calcular_altura(no->direita);
    return (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
}

int no_get_altura(NO* no){
    if(no != NULL){
        return no->altura;
    }
    return -1;
}

int no_get_fator_balanceamento(NO* no){
    if(no != NULL){
        return no->fator_balanceamento;
    }
    return 0;
}

NO* no_get_esquerda(NO* no){
    if(no != NULL){
        return no->esquerda;
    }
    return NULL;
}

NO* no_set_esquerda(NO* no, NO* esquerda){
    if(no != NULL){
        no->esquerda = esquerda;
    }
    return no;
}

NO* no_get_direita(NO* no){
    if(no != NULL){
        return no->direita;
    }
    return NULL;
}

NO* no_set_direita(NO* no, NO* direita){
    if(no != NULL){
        no->direita = direita;
    }
    return no;
}

int no_calcular_fator_balanceamento(NO* no) {
    if (no == NULL) {
        return 0;
    }
    int altura_esquerda = no_calcular_altura(no->esquerda);
    int altura_direita = no_calcular_altura(no->direita);
    return altura_esquerda - altura_direita;
}

void no_set_altura(NO* no, int altura){
    if(no != NULL){
        no->altura = altura;
    }
}

void no_atualizar_altura(NO* no) {
    if (no == NULL) return;
    int altura_esquerda = (no->esquerda != NULL) ? no->esquerda->altura : -1;
    int altura_direita = (no->direita != NULL) ? no->direita->altura : -1;
    no->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
}
