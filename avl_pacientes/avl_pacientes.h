#ifndef AVL_PACIENTES_H
#define AVL_PACIENTES_H

#include "../paciente/paciente.h"

typedef struct Avl_Pacientes AVL_PACIENTES;

/*
 * Cria a estrutura controladora da AVL específica para Pacientes.
 * Configura as funções de comparação por ID.
 */
AVL_PACIENTES* avl_pacientes_criar();

/* Insere um paciente na árvore ordenado pelo ID. */
void avl_pacientes_inserir(AVL_PACIENTES *avl_pacientes, PACIENTE *paciente);

/*
 * Destrói a árvore e remove todos os pacientes nela contidos.
 * Libera a memória de cada paciente (nome, histórico, struct).
 */
void avl_pacientes_apagar(AVL_PACIENTES **avl_pacientes);

/*
 * Busca se existe um paciente com o ID informado.
 * Imprime mensagem de sucesso ou falha no console.
 */
bool avl_pacientes_buscar(AVL_PACIENTES *avl_pacientes, int id);

/* Remove o paciente da árvore baseado no ID e libera sua memória. */
bool avl_pacientes_remover(AVL_PACIENTES* avl_pacientes, int id);

/* Imprime a árvore formatada (debug/visualização). */
void avl_pacientes_imprimir(const AVL_PACIENTES *avl_pacientes);

/* Percorre a árvore (em ordem) executando a função passada para cada paciente. */
void avl_pacientes_percorrer(AVL_PACIENTES *avl_pacientes, void (*funcao)(void *paciente, void *args), void *args);

/* Busca paciente por ID e adiciona procedimento ao seu histórico. */
bool avl_pacientes_adicionar_procedimento(AVL_PACIENTES *avl_pacientes, int id, char *procedimento);

/* Busca paciente por ID e remove o último procedimento do histórico. */
bool avl_pacientes_remover_procedimento(AVL_PACIENTES *avl_pacientes, int id);

/* Busca paciente por ID e lista seus procedimentos no console. */
void avl_pacientes_listar_procedimentos(AVL_PACIENTES *avl_pacientes, int id);

/* Recupera o ponteiro do paciente pelo ID (sem remover da árvore). */
PACIENTE* avl_pacientes_recuperar(AVL_PACIENTES *avl_pacientes, int id);

#endif