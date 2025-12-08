#ifndef _PILHA_H
#define _PILHA_H

  #include "../no_pilha/no.h"
  #include <stdbool.h>
  #include <string.h>

  typedef struct pilha PILHA;

  PILHA* pilha_criar(void);
  void pilha_apagar(PILHA** pilha);
  bool pilha_vazia(PILHA* pilha);
  bool pilha_cheia(PILHA* pilha);
  int pilha_tamanho(PILHA* pilha);
  NO_P* pilha_topo(PILHA* pilha);
  bool pilha_empilhar(PILHA* pilha, void* valor);
  void* pilha_desempilhar(PILHA* pilha);
  

#endif 
