#include <stdlib.h>
#include <stdio.h>


typedef struct pilha_estatica {
    ITEM vetor[TAM];
    int topo;
}PILHA_ESTATICA;

PILHA_ESTATICA *criar_pilha(void) {
    PILHA_ESTATICA *pilha = (PILHA_ESTATICA *) malloc(sizeof (PILHA_ESTATICA));

    if (pilha != NULL) {
      pilha->topo = -1;
    }
    return (pilha);
 }

 int vazia(PILHA_ESTATICA *pilha) {
   return (pilha->topo == -1);
 }

 int cheia(PILHA_ESTATICA *pilha) {
   return (pilha->topo == TAM-1);
 }

 int tamanho(PILHA_ESTATICA *pilha) {
   return (pilha->topo+1);
 }

int topo(PILHA_ESTATICA *pilha) {
	if(!vazia(pilha))
		return (pilha->vetor[pilha->topo]);
	
	return (0);	
 }
 
int empilhar(PILHA_ESTATICA *pilha, ITEM item) {
    if (!cheia(pilha)) {
      pilha->topo++;
      pilha->vetor[pilha->topo] = item;
      return (1);
    }
    return (0);
 }

 ITEM desempilhar(PILHA_ESTATICA *pilha) {
   if (!vazia(pilha)) {
      ITEM i; 
      i = pilha->vetor[pilha->topo];
      pilha->topo--; 
      return (i);
   }
   return (0);
}

