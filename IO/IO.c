#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../paciente/paciente.h"
#include "../historico/historico.h"
#include "../pilha/pilha.h"

static void salvar_paciente_individual(void *dado, void *args)
{
    PACIENTE *p = (PACIENTE *)dado;
    FILE *arquivo = (FILE *)args;

    if (p == NULL || arquivo == NULL)
        return;

    int id = paciente_get_id(p);
    int risco = paciente_get_risco(p);
    bool em_triagem = get_esta_em_triagem(p);
    char *nome = paciente_get_nome(p);
    char *historico = (p != NULL && paciente_get_historico(p) != NULL) ? historico_listar(paciente_get_historico(p)) : NULL;
    
    int tam_nome = (nome != NULL) ? (int)strlen(nome) + 1 : 0;
    int tam_hist = (historico != NULL) ? (int)strlen(historico) : 0;

    fwrite(&id, sizeof(int), 1, arquivo);
    fwrite(&risco, sizeof(int), 1, arquivo);
    fwrite(&em_triagem, sizeof(bool), 1, arquivo);
    fwrite(&tam_nome, sizeof(int), 1, arquivo);

    if (tam_nome > 0)
    {
        fwrite(nome, sizeof(char), tam_nome, arquivo);
    }

    fwrite(&tam_hist, sizeof(int), 1, arquivo);

    if (tam_hist > 0) {
        fwrite(historico, sizeof(char), tam_hist, arquivo);
        free(historico);
    }
}

void IO_SAVE(AVL_PACIENTES *avl, const char *nome_arquivo)
{
    if (avl == NULL || nome_arquivo == NULL)
    {
        printf("Erro: AVL ou nome de arquivo invalidos para salvar.\n");
        return;
    }

    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao criar/abrir arquivo %s para escrita.\n", nome_arquivo);
        return;
    }

    avl_pacientes_percorrer(avl, salvar_paciente_individual, arquivo);

    fclose(arquivo);
    printf("Dados salvos com sucesso em '%s'.\n", nome_arquivo);
}

void IO_LOAD(AVL_PACIENTES *avl, FILA_ESPERA *fila, const char *nome_arquivo)
{
    if (avl == NULL || fila == NULL || nome_arquivo == NULL)
    {
        printf("Erro: Estruturas invalidas para carregar.\n");
        return;
    }

    FILE *arquivo = fopen(nome_arquivo, "rb"); // Read Binary
    if (arquivo == NULL)
    {
        printf("Arquivo %s nao encontrado. Iniciando base vazia.\n", nome_arquivo);
        return;
    }

    int id, risco, tam_nome;
    bool em_triagem;

    // Loop de leitura: Tenta ler o primeiro campo (ID). Se conseguir (retorno == 1), continua.
    while (fread(&id, sizeof(int), 1, arquivo) == 1)
    {
        // Lê o restante dos campos fixos
        fread(&risco, sizeof(int), 1, arquivo);
        fread(&em_triagem, sizeof(bool), 1, arquivo);
        fread(&tam_nome, sizeof(int), 1, arquivo);

        char *nome_buffer = NULL;
        if (tam_nome > 0)
        {
            nome_buffer = (char *)malloc(tam_nome * sizeof(char));
            if (nome_buffer != NULL)
            {
                fread(nome_buffer, sizeof(char), tam_nome, arquivo);
            }
        }

        PACIENTE *novo_paciente = paciente_criar(
            (nome_buffer != NULL) ? nome_buffer : "", 
            id, 
            risco, 
            em_triagem
        );

        int tam_hist = 0;
        if (fread(&tam_hist, sizeof(int), 1, arquivo) == 1 && tam_hist > 0) {
            
            char *buffer_hist = (char *)malloc(tam_hist + 1);

            if (buffer_hist != NULL) {
                fread(buffer_hist, sizeof(char), tam_hist, arquivo);
                buffer_hist[tam_hist] = '\0';

                PILHA *pilha_aux = pilha_criar();
                
                char *token = strtok(buffer_hist, "\n");
                while (token != NULL) {
                    pilha_empilhar(pilha_aux, token);
                    token = strtok(NULL, "\n");
                }

                while (!pilha_vazia(pilha_aux)) {
                    char *proc = (char *)pilha_desempilhar(pilha_aux);
                    paciente_adicionar_procedimento(novo_paciente, proc);
                }

                pilha_apagar(&pilha_aux);
                free(buffer_hist);
            }
        }

        if (novo_paciente != NULL)
        {
            avl_pacientes_inserir(avl, novo_paciente);

            if (em_triagem)
            {
                fila_inserir(fila, novo_paciente);
            }
        }

        if (nome_buffer != NULL)
        {
            free(nome_buffer);
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso de '%s'.\n", nome_arquivo);
}