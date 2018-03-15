#ifndef _PILHA_H_
#define	_PILHA_H_

#include "definicoes.h"

typedef struct pilha PILHA;

PILHA *criar_pilha();
void apagar_pilha(PILHA **pilha);

void empilhar(PILHA *pilha, int V);
int desempilhar(PILHA *pilha);

int vazia_pilha(PILHA *pilha);

#endif	/* _PILHA_H_ */
