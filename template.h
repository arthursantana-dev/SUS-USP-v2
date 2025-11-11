#ifndef TAD_H
#define TAD_H

typedef struct Tad TAD;

TAD* tad_criar();

void tad_remover(TAD **tad);

void tad_imprimir(const TAD *tad);

#endif