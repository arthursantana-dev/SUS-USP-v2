#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_pacientes/avl_pacientes.h"
#include "fila_espera/fila_espera.h"
#include "paciente/paciente.h"
#include "IO/IO.h"

#define ARQUIVO_DADOS "dados_pacientes.dat"
#define CAPACIDADE_FILA 100

// --- Funções Auxiliares de Interface ---

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar_tela() {
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();
}

void ler_string(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

// --- Funções do Menu ---

void menu_registrar_paciente(AVL_PACIENTES *avl, FILA_ESPERA *fila) {
    char nome[100];
    int id, risco;

    printf("\n--- Registrar Paciente ---\n");
    
    printf("Nome: ");
    limpar_buffer();
    ler_string(nome, 100);

    printf("ID (Inteiro unico): ");
    scanf("%d", &id);

    bool ja_existe = avl_pacientes_buscar(avl, id);

    if(ja_existe) {
        printf("Erro: Ja existe um paciente cadastrado com o ID %d.\n", id);
        return;
    }

    printf("Risco (1-Emergencia ... 5-Nao Urgente): ");
    scanf("%d", &risco);

    // Validação básica do risco
    if (risco < 1 || risco > 5) {
        printf("Risco invalido. Atribuindo 5 (Nao Urgente).\n");
        risco = 5;
    }

    PACIENTE *p = paciente_criar(nome, id, risco, true);

    if (p != NULL) {
        avl_pacientes_inserir(avl, p);
        
        bool inseriu_fila = fila_inserir(fila, p);
        
        if (inseriu_fila) {
            printf("Paciente cadastrado e inserido na fila com sucesso!\n");
        } else {
            printf("Paciente cadastrado, mas a fila de espera esta cheia!\n");
        }
    } else {
        printf("Erro de memoria ao criar paciente.\n");
    }
}

void menu_remover_paciente(AVL_PACIENTES *avl) {
    int id;
    printf("\n--- Remover Paciente ---\n");
    printf("Informe o ID do paciente a ser removido: ");
    scanf("%d", &id);

    bool removeu = avl_pacientes_remover(avl, id);
    if (removeu) {
        printf("Paciente removido do sistema.\n");
    } else {
        printf("Paciente nao encontrado ou erro na remocao.\n");
    }
}

void menu_buscar_paciente(AVL_PACIENTES *avl) {
    int id;
    printf("\n--- Buscar Paciente ---\n");
    printf("Informe o ID: ");
    scanf("%d", &id);
    
    avl_pacientes_buscar(avl, id);
}

void menu_dar_alta(FILA_ESPERA *fila) {
    printf("\n--- Dar Alta (Atender Proximo) ---\n");
    
    if (fila_tamanho(fila) == 0) {
        printf("A fila esta vazia. Ninguem para atender.\n");
        return;
    }

    PACIENTE *p = fila_remover(fila);
    
    if (p != NULL) {
        // Atualiza status: não está mais em triagem
        set_esta_em_triagem(p, false);
        
        printf("Atendendo paciente:\n");
        printf(" -> Nome: %s\n", paciente_get_nome(p));
        printf(" -> ID: %d\n", paciente_get_id(p));
        printf(" -> Risco Original: %d\n", paciente_get_risco(p));
        printf("Status atualizado: Alta medica / Atendido.\n");
        // Nota: O paciente continua salvo na AVL (Histórico), apenas saiu da Fila.
    }
}

void menu_adicionar_procedimento(AVL_PACIENTES *avl) {
    int id;
    char procedimento[200];

    printf("\n--- Adicionar Procedimento Medico ---\n");
    printf("Informe o ID do paciente: ");
    scanf("%d", &id);
    limpar_buffer();

    printf("Descricao do procedimento: ");
    ler_string(procedimento, 200);

    bool sucesso = avl_pacientes_adicionar_procedimento(avl, id, procedimento);
    
    if (sucesso) {
        printf("Procedimento registrado com sucesso.\n");
    } else {
        printf("Falha ao registrar procedimento (Verifique ID ou Memoria).\n");
    }
}


void menu_remover_procedimento(AVL_PACIENTES *avl) {
    int id;
    printf("\n--- Remover Ultimo Procedimento ---\n");
    printf("Informe o ID do paciente: ");
    scanf("%d", &id);
    limpar_buffer();

    bool sucesso = avl_pacientes_remover_procedimento(avl, id);

    if (sucesso) {
        printf("Ultimo procedimento removido do historico.\n");
    } else {
        printf("Nao foi possivel remover (Historico vazio ou ID invalido).\n");
    }
}

void menu_listar_procedimentos(AVL_PACIENTES *avl) {
    int id;
    printf("\n--- Listar Historico do Paciente ---\n");
    printf("Informe o ID do paciente: ");
    scanf("%d", &id);
    limpar_buffer();

    avl_pacientes_listar_procedimentos(avl, id);
}


// --- Main ---

int main() {
    AVL_PACIENTES *hospital = avl_pacientes_criar();
    FILA_ESPERA *fila = fila_criar(CAPACIDADE_FILA);

    if (hospital == NULL || fila == NULL) {
        printf("Erro critico: Falha ao alocar memoria para as estruturas.\n");
        return 1;
    }

    printf("Carregando base de dados...\n");
    IO_LOAD(hospital, fila, ARQUIVO_DADOS);

    int opcao = 0;
    do {
        printf("\n======================================\n");
        printf("      SISTEMA PRONTO SOCORRO SUS      \n");
        printf("======================================\n");
        printf("1. Registrar paciente\n");
        printf("2. Remover paciente\n");
        printf("3. Listar pacientes (Base Geral)\n");
        printf("4. Buscar paciente por ID\n");
        printf("5. Mostrar fila de espera (Prioridade)\n");
        printf("6. Dar alta ao paciente (Atender)\n");
        printf("--------------------------------------\n");
        printf("7. Adicionar Procedimento (Historico)\n");
        printf("8. Remover Procedimento (Historico)\n");
        printf("9. Listar Procedimentos (Historico)\n");
        printf("--------------------------------------\n");
        printf("0. Sair (Salvar e Encerrar)\n");
        printf("======================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menu_registrar_paciente(hospital, fila);
                break;
            case 2:
                menu_remover_paciente(hospital);
                break;
            case 3:
                printf("\n--- Lista Geral de Pacientes (AVL) ---\n");
                avl_pacientes_imprimir(hospital);
                break;
            case 4:
                menu_buscar_paciente(hospital);
                break;
            case 5:
                printf("\n--- Fila de Espera (Prioridade) ---\n");
                fila_imprimir(fila);
                break;
            case 6:
                menu_dar_alta(fila);
                break;
            case 7:
                menu_adicionar_procedimento(hospital);
                break;
            case 8:
                menu_remover_procedimento(hospital);
                break;
            case 9:
                menu_listar_procedimentos(hospital);
                break;
            case 0:
                printf("\nSalvando dados e encerrando...\n");
                IO_SAVE(hospital, ARQUIVO_DADOS);                
                fila_apagar(&fila);
                avl_pacientes_apagar(&hospital);
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        if (opcao != 0) {
            pausar_tela();
        }

    } while (opcao != 0);

    printf("Sistema encerrado com sucesso.\n");
    return 0;
}