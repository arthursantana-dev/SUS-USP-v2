#ifndef NO_H
#define NO_H

typedef struct No NO;

NO* no_criar(void* valor, NO* esquerda, NO* direita, int altura, int fator_balanceamento);

NO* no_get_esquerda(NO* no);

NO* no_set_esquerda(NO* no, NO* esquerda);

NO* no_get_direita(NO* no);

NO* no_set_direita(NO* no, NO* direita);

int no_get_altura(NO* no);

int no_get_fator_balanceamento(NO* no);

int no_calcular_fator_balanceamento(NO* no);

void* no_get_valor(NO* no);

void no_set_altura(NO* no, int altura);

void no_set_valor(NO* no, void* valor);

void no_remover(NO **no);

void no_remover_ponteiro(NO *no);

void no_atualizar_altura(NO* no);

#endif