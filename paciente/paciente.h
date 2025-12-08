#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdbool.h>
#include "../historico/historico.h"

typedef struct Paciente PACIENTE;

/*
 * Cria um novo paciente alocando memória dinamicamente.
 * Copia a string 'nome' para um buffer interno e inicializa o histórico vazio.
 * Retorna: Ponteiro para o novo PACIENTE ou NULL em caso de erro.
 */
PACIENTE *paciente_criar(char *nome, int id, int risco, bool esta_em_triagem);

/* Retorna o ponteiro para a string do nome (não deve ser liberada externamente). */
char *paciente_get_nome(PACIENTE *paciente);

/* Retorna o ID único do paciente. */
int paciente_get_id(PACIENTE *paciente);

/* Retorna o nível de risco (1 a 5). */
int paciente_get_risco(PACIENTE *paciente);

/*
 * Destrói o paciente e libera toda a memória associada.
 * Inclui: Nome, Struct Paciente e o Histórico (e seus itens).
 */
void paciente_remover_ponteiro(PACIENTE* paciente);

/*
 * Similar a remover_ponteiro, mas recebe um ponteiro duplo para
 * setar a variável original como NULL após a liberação.
 */
void paciente_remover(PACIENTE **paciente);

/* Retorna true se o paciente ainda está aguardando na fila/triagem. */
bool get_esta_em_triagem(PACIENTE* paciente);

/* Atualiza o status de triagem do paciente. */
void set_esta_em_triagem(PACIENTE* paciente, bool status);

/*
 * Compara dois pacientes.
 * Retorna true se IDs e Nomes forem idênticos.
 */
bool comparar_pacientes(void *p1, void *p2);

/*
 * Adiciona uma nova entrada (string) ao histórico do paciente.
 * A string é duplicada internamente.
 */
bool paciente_adicionar_procedimento(PACIENTE *paciente, char *procedimento);

/* Remove a última entrada do histórico (desempilha). */
bool paciente_remover_procedimento(PACIENTE *paciente);

/*
 * Imprime no console todos os procedimentos do histórico.
 * Recupera a string formatada e libera a memória temporária usada para exibição.
 */
void paciente_listar_procedimentos(PACIENTE *paciente);

/* Retorna o ponteiro para a estrutura de histórico do paciente. */
HISTORICO *paciente_get_historico(PACIENTE *paciente);

#endif