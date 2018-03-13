#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "definicoes_grafo_g_l.h"
#include "grafo_g_l.h"

#define menor(a, b) ((a < b) ? a : b)
#define maior(a, b) ((a > b) ? a : b)

void ordenar_arestas(GRAFO_G_L *grafo){
	int i, j;
	ARESTA *temp;

	for(i=0;i<grafo->num_arestas;i++){
		for(j=i+1;j<grafo->num_arestas;j++){
			if(grafo->arestas[j]->PESO < grafo->arestas[i]->PESO){
				temp = grafo->arestas[i];
				grafo->arestas[i] = grafo->arestas[j];
				grafo->arestas[j] = temp;
			}
		}
	}
}

GRAFO_G_L *criar_grafo_g_l(int V, int A){

	if (V<=0 || A<=0) return NULL;

	GRAFO_G_L *grafo = (GRAFO_G_L*)malloc(sizeof(GRAFO_G_L));

	if (grafo == NULL) return NULL;

	grafo->num_vertices = V;
	grafo->num_arestas = A;
	grafo->soma_pesos = 0;

	grafo->vertices = (VERT*)malloc(sizeof(VERT)*(grafo->num_vertices)); 

	if(grafo->vertices == NULL) return NULL;

	int i, V1, V2, PESO;

	for(i=0;i<grafo->num_vertices;i++){
		grafo->vertices[i].lista_inicio = NULL;
		grafo->vertices[i].lista_fim = NULL;
		grafo->vertices[i].conjunto = i;
	}

	grafo->arestas = (ARESTA**)malloc(sizeof(ARESTA*)*(grafo->num_arestas));

	for(i=0;i<grafo->num_arestas;i++){
		scanf("%d %d %d", &V1, &V2, &PESO);
		inserir_celula_g_l(grafo, V1, V2, PESO);
		inserir_celula_g_l(grafo, V2, V1, PESO);
		grafo->arestas[i] = (ARESTA*)malloc(sizeof(ARESTA));
		grafo->arestas[i]->V1 = V1;
		grafo->arestas[i]->V2 = V2;
		grafo->arestas[i]->PESO = PESO;
		grafo->soma_pesos += PESO;
	}

	ordenar_arestas(grafo);

	return grafo;
}

void apagar_grafo_g_l(GRAFO_G_L **grafo){
	int i;
	CELL *prem = NULL, *paux = NULL;

	for(i=0;i<(*grafo)->num_vertices;i++){
		paux = (*grafo)->vertices[i].lista_inicio;
		 while(paux != NULL) {
    		prem = paux;
    		paux = paux->prox;
    		free(prem);
  		}
	}

	free((*grafo)->vertices);
	free(*grafo);
	*grafo = NULL;
}

void imprimir_grafo_g_l(GRAFO_G_L *grafo){
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){
		printf("%d. ", i);
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){
			printf("%d(%d) ", paux->V, paux->PESO);
			paux = paux->prox;
		}
		printf("\n");
	}
}

void vertices_adjacentes_grafo_g_l(GRAFO_G_L *grafo, int x){
	if(grafo == NULL || grafo->vertices == NULL) return;

	if (x < 0 || x >= grafo->num_vertices) return;

	CELL *paux = grafo->vertices[x].lista_inicio;

	while(paux != NULL){
			printf("%d ", paux->V);
			paux = paux->prox;
		}	
}

void adicionar_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2, int PESO){
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices || PESO <= 0) return;

	inserir_celula_g_l(grafo, V1, V2, PESO);
	inserir_celula_g_l(grafo, V2, V1, PESO);
}

void remover_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2){
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices) return;

	remover_celula_g_l(grafo, V1, V2);
	remover_celula_g_l(grafo, V2, V1);
}

void menor_peso_grafo_g_l(GRAFO_G_L *grafo){
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i, V1, V2, menor_peso = INT_MAX;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){
			if(paux->PESO < menor_peso){
				V1 = menor(i, paux->V);
				V2 = maior(i, paux->V);
			}
		}
	}
	printf("%d %d", V1, V2);
}


void MST_grafo_g_l(GRAFO_G_L *grafo){
	int i, j, k, mst_soma = 0, conjunto;

	for(i=0;i<grafo->num_arestas;i++){
		if(grafo->vertices[grafo->arestas[i]->V1].conjunto != grafo->vertices[grafo->arestas[i]->V2].conjunto){
			conjunto = grafo->vertices[grafo->arestas[i]->V2].conjunto;
			for(j=0;j<grafo->num_vertices;j++){
				if(grafo->vertices[j].conjunto == conjunto){
					grafo->vertices[j].conjunto = grafo->vertices[grafo->arestas[i]->V1].conjunto;
				}
			}
			mst_soma += grafo->arestas[i]->PESO;
		}
	}

	printf("%d %d\n", grafo->soma_pesos, mst_soma);

}