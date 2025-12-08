#include "no.h"
#include <stdio.h>
#include <stdlib.h>

/*Nó é uma estrutura genérica, seu valor pode apontar para qualquer coisa. Os TADs que o manipulam são, portanto, genéricos também. Assim, cada um desses TADs foi "englobado" por um TAD que manipula um tipo específico de dado. Ex: Nó <- lista <- lista_pacientes */
struct No {
    void* valor;
    NO_P* anterior;
};

NO_P* no_p_criar(void* valor, NO_P* anterior) {
    NO_P *no = (NO_P*) malloc(sizeof(NO_P));
    if (no != NULL) {
        no->valor = valor;
        no->anterior = anterior;
    }
    return no;
}

NO_P* no_p_get_anterior(NO_P* no){
    if(no != NULL){
        return no->anterior;
    }
    return NULL;
}

void no_p_set_anterior(NO_P* no, NO_P* anterior){
    if(no != NULL){
        no->anterior = anterior;
    }
}

void no_p_remover(NO_P **no) {
    if (*no != NULL) {
        (*no)->valor = NULL;
        (*no)->anterior = NULL;
        free(*no);
        *no = NULL;
    }
}

/*Método alternativo para remoção, pois um método get do TAD retorna um NO_P*, não NO_P**, e usar &no não funcionaria */
void no_p_remover_ponteiro(NO_P *no) {
    if (no != NULL) {
        no->valor = NULL;
        no->anterior = NULL;
        free(no);
    }
}

void* no_p_get_valor(NO_P* no){

    if(no != NULL){
        return no->valor;
    }

    return NULL;

}

void no_p_set_valor(NO_P* no, void* valor){
    if(no != NULL){
        no->valor = valor;
    }
}