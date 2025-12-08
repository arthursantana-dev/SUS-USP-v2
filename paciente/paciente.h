#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdbool.h>
#include "../historico/historico.h"

typedef struct Paciente PACIENTE;

PACIENTE *paciente_criar(char *nome, int id, int risco, bool esta_em_triagem);

char *paciente_get_nome(PACIENTE *paciente);

int paciente_get_id(PACIENTE *paciente);

int paciente_get_risco(PACIENTE *paciente);

void paciente_remover_ponteiro(PACIENTE* paciente);

bool get_esta_em_triagem(PACIENTE* paciente);

void set_esta_em_triagem(PACIENTE* paciente, bool status);

void paciente_remover(PACIENTE **paciente);

bool comparar_pacientes(void *p1, void *p2);

bool paciente_adicionar_procedimento(PACIENTE *paciente, char *procedimento);

bool paciente_remover_procedimento(PACIENTE *paciente);

void paciente_listar_procedimentos(PACIENTE *paciente);

HISTORICO *paciente_get_historico(PACIENTE *paciente);

#endif