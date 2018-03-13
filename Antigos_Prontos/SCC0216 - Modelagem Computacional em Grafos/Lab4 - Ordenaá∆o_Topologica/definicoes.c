#include <stdio.h>
#include <stdlib.h>

#include "definicoes.h"

void inserir_celula_d_l(GRAFO_D_L *grafo, int Vi, int Vj, int PESO){
	CELL *nova_celula = (CELL*)malloc(sizeof(CELL));
		nova_celula->V = Vj;
		nova_celula->PESO = 1;
		nova_celula->prox = NULL;
		CELL *paux = grafo->vertices[Vi].lista_inicio;  //ponteiro que aponta para o proximo elemento ao que deverá ser inserido;
		CELL *pant = nova_celula;  //ponteiro que aponta para o elemento anterior ao que será inserido;

		if(grafo->vertices[Vi].lista_inicio == NULL){
			grafo->vertices[Vi].lista_inicio = nova_celula;
			grafo->vertices[Vi].lista_fim = nova_celula;
		}else{
			while(paux != NULL && paux->V < Vj){  //laço que percorre com 'paux' e 'pant' a lista até a posição de inserção da nova célula;
				pant = paux;
				paux = paux->prox;
			}

			//os ponteiros 'prox' de cada celula são trocados para inserir a nova célula a lista;

			if(pant == nova_celula)
				grafo->vertices[Vi].lista_inicio = nova_celula;

			pant->prox = nova_celula;
			nova_celula->prox = paux;

			if(paux == NULL)
				grafo->vertices[Vi].lista_fim = nova_celula;
		}
}

void remover_celula_d_l(GRAFO_D_L *grafo, int Vi, int Vj){
	CELL *prem = grafo->vertices[Vi].lista_inicio;  //ponteiro que aponta para o elemento a ser removido;
  	CELL *pant = NULL;  //ponteiro que aponta para o elemento anterior ao elemento que deve ser removido;

	while(prem != NULL && prem->V != Vj) { //percorre a lista até achar a célula a ser removida;
  	 	pant = prem;
   		prem = prem->prox;
    }

    //as trocas dos poneiros 'prox' são devidamente realizadas;

  	if(prem != NULL) {
    	if(prem == grafo->vertices[Vi].lista_inicio) {
      		grafo->vertices[Vi].lista_inicio = prem->prox;
    	} else {
     	 	pant->prox = prem->prox;
    	}

    if(prem == grafo->vertices[Vi].lista_fim) {
      grafo->vertices[Vi].lista_fim = pant;
    }

    free(prem);
  	}
}
