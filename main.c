#include "avl/avl.h"
#include "no/no.h"
#include <stdio.h>
#include <stdlib.h>
#include "avl_pacientes/avl_pacientes.h"
#include "paciente/paciente.h"
// #include "heap/heap.h"
#include "fila_espera/fila_espera.h"

int comparar_inteiros(int a, int b)
{
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

void imprimir_inteiro(void *a)
{
    printf("\t%d\n", *(int *)a);
}

void apagar_inteiro(void* a)
{
}

int get_inteiro(void *a)
{
    int value = *(int *)a;
    return value;
}

int main()
{
    // AVL *avl = avl_criar(comparar_inteiros, imprimir_inteiro, apagar_inteiro, get_inteiro);

    AVL_PACIENTES *ap = avl_pacientes_criar();

    // // FILA_ESPERA *fe = fila_criar(100);

    PACIENTE *p1 = paciente_criar("Alice", 5, 2, true);
    PACIENTE *p2 = paciente_criar("Bob", 6, 1, false);
    PACIENTE *p3 = paciente_criar("Charlie", 6, 5, true);

    // // fila_inserir(fe, p1);
    // // fila_inserir(fe, p2);

    avl_pacientes_inserir(ap, p1);
    avl_pacientes_inserir(ap, p2);
    avl_pacientes_inserir(ap, p3);

    // fila_imprimir(fe);

    // printf("saiu\n");

    // // fila_remover(fe);
    // // fila_remover(fe);

    // paciente_remover_ponteiro(p1);
    // paciente_remover_ponteiro(p2);

    // fila_apagar(&fe);

    avl_pacientes_imprimir(ap);

    avl_pacientes_apagar(&ap);

    // printf("Removendo paciente com ID 5:\n");
    // int id_busca = 5;
    // avl_pacientes_remover(ap, id_busca);

    // avl_pacientes_buscar(ap, 5);

    // avl_pacientes_apagar(&ap);
    // // Declaração das variáveis
    // int v1 = 50;
    // int v2 = 25;
    // int v3 = 75;
    // int v4 = 12;
    // int v5 = 37;
    // int v6 = 60;
    // int v7 = 90;
    // int v8 = 6;
    // int v9 = 18;
    // int v10 = 43;
    // int v11 = 80;
    // int v12 = 100;
    // int v13 = 31;
    // int v14 = 65;
    // int v15 = 85;
    // int v16 = 33;

    // // // Chamadas para forçar todas as rotações (Simples Direita, Dupla E-D, Simples Esquerda, Dupla D-E)
    // avl_inserir(avl, &v1);
    // avl_inserir(avl, &v2);
    // avl_inserir(avl, &v3);
    // avl_inserir(avl, &v4);
    // avl_inserir(avl, &v5);
    // avl_inserir(avl, &v6);
    // avl_inserir(avl, &v7);
    // avl_inserir(avl, &v8); // Força Rotação Simples à Direita (no nó 12)
    // avl_inserir(avl, &v9);
    // avl_inserir(avl, &v10);
    // avl_inserir(avl, &v11);
    // avl_inserir(avl, &v12);
    // avl_inserir(avl, &v13); // Força Rotação Dupla Esquerda-Direita (no nó 37)
    // avl_inserir(avl, &v14); // Força Rotação Simples à Esquerda (no nó 75)
    // avl_inserir(avl, &v15);
    // avl_inserir(avl, &v16); // Força Rotação Dupla Direita-Esquerda (no nó 31)

    // avl_remover(avl, &v16);

    // printf("Elementos da AVL em ordem crescente:\n");

    // avl_imprimir(avl);

    // avl_apagar(&avl);

}
