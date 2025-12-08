# Sistema de Gerenciamento de Pronto Socorro (Simulação SUS)

Este projeto consiste em um sistema de gerenciamento hospitalar desenvolvido em **Linguagem C**. O objetivo é simular o fluxo de atendimento de um pronto-socorro, desde o cadastro e triagem de pacientes até o registro de procedimentos médicos e alta, utilizando estruturas de dados avançadas para garantia de eficiência.

## 📋 Funcionalidades Principais

  * **Cadastro de Pacientes:** Registro com ID único, nome e classificação de risco.
  * **Triagem Automática (Fila de Prioridade):** Pacientes são ordenados automaticamente na fila de espera baseados na gravidade do caso (Sistema de Triagem de Manchester simplificado).
  * **Histórico Médico:** Registro detalhado de procedimentos realizados em cada paciente.
  * **Busca Eficiente:** Localização rápida de pacientes pelo ID.
  * **Persistência de Dados:** Salvamento e carregamento automático da base de dados em arquivo binário (`.dat`), mantendo a consistência entre execuções.
  * **Gerenciamento de Memória:** Controle rigoroso de alocação e liberação de memória (sem vazamentos), verificado via Valgrind.

## 🛠️ Estruturas de Dados Utilizadas

O projeto foi construído sobre o conceito de **Tipos Abstratos de Dados (TADs)** para modularidade e encapsulamento:

1.  **Árvore AVL (`avl_pacientes`):**

      * Utilizada como o "Banco de Dados" principal dos pacientes.
      * Garante complexidade **O(log n)** para busca, inserção e remoção.
      * Mantém os registros ordenados por ID.

2.  **Heap Mínima / Fila de Prioridade (`fila_espera`):**

      * Gerencia a ordem de atendimento.
      * Prioriza pacientes com menor valor de risco (1 = Emergência, 5 = Não Urgente).
      * Garante que casos graves sejam atendidos primeiro.

3.  **Pilha (`historico`):**

      * Armazena o histórico de procedimentos médicos de cada paciente.
      * Segue a lógica LIFO (Last In, First Out), permitindo adicionar novos procedimentos e desfazer o último registrado se necessário.

## 📂 Estrutura de Arquivos

O projeto é modularizado nas seguintes pastas:

```text
/
├── makefile                # Script de automação de compilação
├── main.c                  # Ponto de entrada e menu do sistema
├── dados_pacientes.dat     # Arquivo de persistência (gerado automaticamente)
│
├── avl/                    # Implementação genérica da Árvore AVL
├── avl_pacientes/          # Adaptador da AVL para o contexto de Pacientes
├── fila_espera/            # Gerenciamento da Fila de Prioridade
├── heap/                   # Implementação genérica da Heap Binária
├── historico/              # Gerenciamento do histórico médico
├── IO/                     # Manipulação de arquivos (Save/Load)
├── no/                     # Nó genérico para árvores e heaps
├── no_pilha/               # Nó específico para pilhas encadeadas
├── paciente/               # TAD Paciente (Objeto principal)
└── pilha/                  # Implementação genérica de Pilha
```

## 🚀 Como Compilar e Executar

O projeto conta com um **Makefile** configurado para automatizar a compilação, gerenciar dependências e facilitar a execução.

### Pré-requisitos

  * **Compilador GCC** (GNU Compiler Collection).
  * **Make** (Padrão em ambientes Linux/Unix. No Windows, disponível via MinGW ou WSL).

### Comandos

Abra o terminal na pasta raiz do projeto e utilize os seguintes comandos:

**1. Compilar e Rodar (Recomendado)**
Compila todo o projeto e inicia o programa imediatamente.

```bash
make run
```

**2. Apenas Compilar**
Gera o executável `main` (ou `main.exe` no Windows) sem executá-lo.

```bash
make
```

**3. Limpar Arquivos Temporários**
Remove os arquivos objetos (`.o`), dependências (`.d`) e o executável gerado. Útil para forçar uma recompilação limpa.

```bash
make clean
```

*Nota: O Makefile está configurado com as flags `-Wall -Wextra -std=c11 -O2 -g`, garantindo avisos de boas práticas, padrão C11, otimização e símbolos de debug.*

## 📖 Guia de Uso

Ao iniciar o sistema, os dados anteriores são carregados automaticamente. O menu principal oferece as seguintes opções:

1.  **Registrar Paciente:** Insira Nome, ID e Risco (1 a 5). O paciente vai para a AVL e para a Fila de Espera.
2.  **Remover Paciente:** Remove da base de dados (e da fila, se estiver lá).
3.  **Listar (Base Geral):** Mostra todos os pacientes cadastrados (ordem de ID).
4.  **Buscar por ID:** Verifica se um paciente existe.
5.  **Mostrar Fila (Prioridade):** Exibe a ordem de atendimento atual.
6.  **Dar Alta (Atender):** Retira o próximo paciente da fila de prioridade.
7.  **Adicionar Procedimento:** Registra uma ação médica no histórico do paciente (por ID).
8.  **Remover Procedimento:** Desfaz a última ação registrada.
9.  **Listar Histórico:** Exibe todos os procedimentos de um paciente específico.
10. **Sair:** Salva todas as alterações no disco e encerra o programa limpando a memória.

## ⚙️ Detalhes Técnicos sobre Persistência

A função `IO_SAVE` e `IO_LOAD` utiliza serialização binária para armazenar:

  * Dados primitivos (int, bool).
  * Strings de tamanho variável (Nome, Histórico concatenado).
  * Reconstrução da estrutura de dados complexa (AVL e Fila) ao reiniciar o programa.
