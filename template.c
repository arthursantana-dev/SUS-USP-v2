#include "template.h"
#include <stdio.h>
#include <stdlib.h>

struct Tad {
    int valor;
};

TAD* tad_criar() {
    TAD *tad = (TAD*) malloc(sizeof(TAD));
    if (tad != NULL) {
        tad->valor = 0;
    }
    return tad;
}

void tad_remover(TAD **tad) {
    if (*tad != NULL) {
        free(*tad);
        *tad = NULL;
    }
}

void tad_imprimir(const TAD *tad) {
    if (tad != NULL) {
        printf("Valor: %d\n", tad->valor);
    }
}