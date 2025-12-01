#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

/* Estrutura interna da Heap [cite: 436, 440] */
struct heap {
    NO** vetor;                     // Vetor dinâmico de ponteiros para nós
    int tamanho;                    // Quantidade atual de elementos
    int capacidade;                 // Capacidade total do vetor
    FUNCAO_GET_PRIORIDADE get_prio; // Ponteiro para a função de prioridade genérica
};

/* Funções Auxiliares de Navegação nos Índices (Baseado nos slides [cite: 340, 341]) */
static int indice_pai(int i) {
    return (i - 1) / 2;
}

static int indice_filho_esq(int i) {
    return (2 * i) + 1;
}

static int indice_filho_dir(int i) {
    return (2 * i) + 2;
}

/* Função auxiliar para trocar dois elementos no vetor [cite: 487] */
static void swap(HEAP* h, int i, int j) {
    NO* temp = h->vetor[i];
    h->vetor[i] = h->vetor[j];
    h->vetor[j] = temp;
}

HEAP* heap_criar(int capacidade_inicial, FUNCAO_GET_PRIORIDADE get_prioridade) {
    HEAP* h = (HEAP*) malloc(sizeof(HEAP));
    if (h != NULL) {
        h->vetor = (NO**) malloc(sizeof(NO*) * capacidade_inicial);
        if (h->vetor == NULL) {
            free(h);
            return NULL;
        }
        h->tamanho = 0;
        h->capacidade = capacidade_inicial;
        h->get_prio = get_prioridade; // Registra a função genérica
    }
    return h;
}

/* Método genérico para obter prioridade de um nó */
int heap_get_prioridade_no(HEAP* heap, NO* no) {
    if (heap == NULL || no == NULL) return -1;
    // Usa a função registrada para ler o dado genérico dentro do nó
    return heap->get_prio(no_get_valor(no));
}

/* Sobe o elemento (fix_up) para restaurar a propriedade da Heap [cite: 144, 512] */
static void fix_up(HEAP* h, int i) {
    // Enquanto não for a raiz e a prioridade do atual for maior que a do pai
    while (i > 0) {
        int pai = indice_pai(i);
        
        int prio_atual = heap_get_prioridade_no(h, h->vetor[i]);
        int prio_pai = heap_get_prioridade_no(h, h->vetor[pai]);

        if (prio_atual > prio_pai) {
            swap(h, i, pai);
            i = pai; // Sobe para o índice do pai
        } else {
            break; // Propriedade satisfeita
        }
    }
}

/* Desce o elemento (fix_down) para restaurar a propriedade da Heap [cite: 223, 262] */
static void fix_down(HEAP* h, int i) {
    int esq = indice_filho_esq(i);
    int dir = indice_filho_dir(i);
    int maior = i;

    // Verifica se filho esquerdo existe e é maior que o atual
    if (esq < h->tamanho) {
        int prio_esq = heap_get_prioridade_no(h, h->vetor[esq]);
        int prio_maior = heap_get_prioridade_no(h, h->vetor[maior]);
        
        if (prio_esq > prio_maior) {
            maior = esq;
        }
    }

    // Verifica se filho direito existe e é maior que o "maior" encontrado até agora
    if (dir < h->tamanho) {
        int prio_dir = heap_get_prioridade_no(h, h->vetor[dir]);
        int prio_maior = heap_get_prioridade_no(h, h->vetor[maior]);

        if (prio_dir > prio_maior) {
            maior = dir;
        }
    }

    // Se o maior não é o pai, troca e continua descendo
    if (maior != i) {
        swap(h, i, maior);
        fix_down(h, maior);
    }
}

void heap_inserir(HEAP* h, NO* no) {
    if (h == NULL || h->tamanho >= h->capacidade) return; // Heap cheia ou inválida

    // 1. Insere no final do vetor [cite: 127]
    h->vetor[h->tamanho] = no;
    
    // 2. Restaura a ordem subindo o elemento [cite: 138, 161]
    fix_up(h, h->tamanho);
    
    h->tamanho++;
}

NO* heap_remover(HEAP* h) {
    if (h == NULL || h->tamanho == 0) return NULL;

    // 1. Guarda a raiz para retornar [cite: 206]
    NO* raiz = h->vetor[0];

    // 2. Substitui a raiz pelo último elemento [cite: 206]
    h->vetor[0] = h->vetor[h->tamanho - 1];
    h->tamanho--;

    // 3. Restaura a ordem descendo a nova raiz [cite: 207, 248]
    if (h->tamanho > 0) {
        fix_down(h, 0);
    }

    return raiz;
}

NO* heap_topo(HEAP* h) {
    if (h == NULL || h->tamanho == 0) return NULL;
    return h->vetor[0];
}

int heap_tamanho(HEAP* h) {
    return (h != NULL) ? h->tamanho : 0;
}

int heap_get_capacidade(HEAP* heap){
    if(heap == NULL) return 0;

    return heap->capacidade;
}

int heap_vazia(HEAP* h) {
    return (h != NULL) ? (h->tamanho == 0) : 1;
}

int heap_cheia(HEAP* h) {
    return (h != NULL) ? (h->tamanho == h->capacidade) : 1;
}

void heap_apagar(HEAP** heap) {
    if (heap != NULL && *heap != NULL) {
        free((*heap)->vetor); // Libera o vetor de ponteiros
        free(*heap);          // Libera a estrutura
        *heap = NULL;
    }
}