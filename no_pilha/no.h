#ifndef NO_P_PILHA_H
#define NO_P_PILHA_H

typedef struct No NO_P;

NO_P* no_p_criar(void* valor, NO_P* anterior);

NO_P* no_p_get_anterior(NO_P* no);

void no_p_set_anterior(NO_P* no, NO_P* anterior);

void* no_p_get_valor(NO_P* no);

void no_p_set_valor(NO_P* no, void* valor);

void no_p_remover(NO_P **no);

void no_p_remover_ponteiro(NO_P *no);

#endif