#include <stdlib.h>

#include "definicoes_grafo_g_l.h"

void inserir_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj, int PESO){
		CELL *nova_celula = (CELL*)malloc(sizeof(CELL));
		nova_celula->V = Vj;
		nova_celula->PESO = PESO;
		nova_celula->prox = NULL;
		CELL *paux = grafo->vertices[Vi].lista_inicio;
		CELL *pant = nova_celula;

		if(grafo->vertices[Vi].lista_inicio == NULL){
			grafo->vertices[Vi].lista_inicio = nova_celula;
			grafo->vertices[Vi].lista_fim = nova_celula;
		}else{
			while(paux != NULL && paux->V < Vj){
				pant = paux;
				paux = paux->prox;
			}

			if(pant == nova_celula)
				grafo->vertices[Vi].lista_inicio = nova_celula;

			pant->prox = nova_celula;
			nova_celula->prox = paux;

			if(paux == NULL)
				grafo->vertices[Vi].lista_fim = nova_celula;
		}
}

void remover_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj){
	CELL *prem = grafo->vertices[Vi].lista_inicio;
  	CELL *pant = NULL;

	while(prem != NULL && prem->V != Vj) {
  	 	pant = prem;
   		prem = prem->prox;
    }
  
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