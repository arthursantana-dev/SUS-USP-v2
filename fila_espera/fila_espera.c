#include "fila_espera.h"
#include "../heap/heap.h"
#include "../no/no.h"
#include <stdlib.h>
#include <stdio.h>

struct fila_espera
{
    HEAP *heap;
};

/* * Função Callback para o Heap Genérico.
 * Lógica: O PDF define 1 como Emergência (Máximo) e 5 como Não Urgente.
 * O Heap Maximo prioriza o maior inteiro.
 * * Fórmula: (Constante * (6 - Risco)) - ID
 * * Explicação:
 * 1. (6 - Risco): Inverte a escala. Risco 1 vira 5. Risco 5 vira 1.
 * 2. Multiplicação por 1.000.000: Cria "faixas" de prioridade muito distantes.
 * 3. Subtração do ID: Serve como critério de desempate (Ordem de chegada).
 * IDs menores (chegaram antes) resultam em um número total maior dentro da mesma faixa de risco.
 * * Exemplo:
 * Paciente A (Risco 1, ID 10) -> (5 * 1M) - 10 = 4.999.990 (Topo)
 * Paciente B (Risco 1, ID 20) -> (5 * 1M) - 20 = 4.999.980 (Segundo)
 * Paciente C (Risco 2, ID 01) -> (4 * 1M) - 1  = 3.999.999 (Terceiro)
 */
int fila_obter_prioridade_paciente(void *dado)
{
    if (dado == NULL)
        return -1;

    PACIENTE *p = (PACIENTE *)dado;
    int risco = paciente_get_risco(p);
    int id = paciente_get_id(p);

    // Garante que risco inválido não quebre a lógica, tratando como prioridade mínima
    if (risco < 1 || risco > 5)
        risco = 5;

    // Peso alto para o risco dominar a conta
    long long peso_risco = (6 - risco) * 1000000;

    // Subtrai ID para que IDs menores tenham valor final maior (Max Heap)
    return (int)(peso_risco - id);
}

static void imprimir_paciente(PACIENTE *paciente){
    if (paciente != NULL)
    {
        printf("Paciente ID: %d, Nome: %s, Risco: %d\n", paciente_get_id(paciente), paciente_get_nome(paciente), paciente_get_risco(paciente));
    }
}

FILA_ESPERA *fila_criar(int capacidade)
{
    FILA_ESPERA *f = (FILA_ESPERA *)malloc(sizeof(FILA_ESPERA));
    if (f != NULL)
    {
        // Passa a função de prioridade criada acima para o Heap Genérico
        f->heap = heap_criar(capacidade, fila_obter_prioridade_paciente);

        if (f->heap == NULL)
        {
            free(f);
            return NULL;
        }
    }
    return f;
}

bool fila_inserir(FILA_ESPERA *f, PACIENTE *paciente)
{
    if (f == NULL || paciente == NULL || heap_cheia(f->heap))
    {
        return false;
    }

    // Cria um Nó genérico contendo o Paciente
    // Configura esquerda/direita como NULL e altura/balanceamento padrão (não usados no Heap vetor)
    NO *novo_no = no_criar(paciente, NULL, NULL, 0, 0);

    if (novo_no == NULL)
        return false;

    heap_inserir(f->heap, novo_no);
    return true;
}

PACIENTE *fila_remover(FILA_ESPERA *f)
{
    if (f == NULL || heap_vazia(f->heap))
    {
        return NULL;
    }

    // O Heap retorna o NÓ (estrutura invólucro)
    NO *no_removido = heap_remover(f->heap);

    if (no_removido == NULL)
        return NULL;

    // Extraímos o Paciente de dentro do Nó
    PACIENTE *p = (PACIENTE *)no_get_valor(no_removido);

    // Liberamos apenas a estrutura do NÓ, mantendo o Paciente intacto
    // Usamos no_remover_ponteiro pois no_remover espera NO**
    no_remover_ponteiro(no_removido);

    return p;
}

PACIENTE *fila_consultar_proximo(FILA_ESPERA *f)
{
    if (f == NULL || heap_vazia(f->heap))
    {
        return NULL;
    }

    NO *topo = heap_topo(f->heap);
    return (PACIENTE *)no_get_valor(topo);
}

void fila_imprimir(FILA_ESPERA *f)
{
    if(f == NULL || fila_tamanho(f) == 0) return;

    FILA_ESPERA *fila_auxiliar = fila_criar(heap_get_capacidade(f->heap));

    while (fila_tamanho(f) != 0)
    {
        PACIENTE *p = fila_remover(f);
        imprimir_paciente(p);
        fila_inserir(fila_auxiliar, p);
    }

    while (fila_tamanho(fila_auxiliar) != 0)
    {
        PACIENTE *p = fila_remover(fila_auxiliar);
        fila_inserir(f, p);
    }

    fila_apagar(&fila_auxiliar);

}

int fila_tamanho(FILA_ESPERA *f)
{
    if (f == NULL)
        return 0;
    return heap_tamanho(f->heap);
}

void fila_apagar(FILA_ESPERA **f)
{
    if (f != NULL && *f != NULL)
    {
        // Esvazia a fila, caso não tenha sido esvaziada.
        while(fila_tamanho(*f) != 0) fila_remover(*f);

        // Apaga a estrutura do heap (vetor), mas não os dados (pacientes)
        heap_apagar(&((*f)->heap));
        free(*f);
        *f = NULL;
    }
}