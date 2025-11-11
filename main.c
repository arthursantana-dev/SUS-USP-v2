#include "avl/avl.h"
#include "no/no.h"
#include <stdio.h>
#include <stdlib.h>

int comparar_inteiros(void *a, void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

int main()
{
    AVL *avl = avl_criar(comparar_inteiros);

    // Declaração das variáveis
    int v1 = 50;
    int v2 = 25;
    int v3 = 75;
    int v4 = 12;
    int v5 = 37;
    int v6 = 60;
    int v7 = 90;
    int v8 = 6;
    int v9 = 18;
    int v10 = 43;
    int v11 = 80;
    int v12 = 100;
    int v13 = 31;
    int v14 = 65;
    int v15 = 85;
    int v16 = 33;

    // Chamadas para forçar todas as rotações (Simples Direita, Dupla E-D, Simples Esquerda, Dupla D-E)
    avl_inserir(avl, &v1);
    avl_inserir(avl, &v2);
    avl_inserir(avl, &v3);
    avl_inserir(avl, &v4);
    avl_inserir(avl, &v5);
    avl_inserir(avl, &v6);
    avl_inserir(avl, &v7);
    avl_inserir(avl, &v8); // Força Rotação Simples à Direita (no nó 12)
    avl_inserir(avl, &v9);
    avl_inserir(avl, &v10);
    avl_inserir(avl, &v11);
    avl_inserir(avl, &v12);
    avl_inserir(avl, &v13); // Força Rotação Dupla Esquerda-Direita (no nó 37)
    avl_inserir(avl, &v14); // Força Rotação Simples à Esquerda (no nó 75)
    avl_inserir(avl, &v15);
    avl_inserir(avl, &v16); // Força Rotação Dupla Direita-Esquerda (no nó 31)

    printf("Elementos da AVL em ordem crescente:\n");

    avl_imprimir(avl);
}
