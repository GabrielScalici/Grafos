#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "definicoes.h"
#include "fila.h"
#include "pilha.h"
#include "grafo_d_l.h"

#define NIL -1
#define WHITE 0
#define GRAY 1
#define BLACK 2


GRAFO_D_L *criar_grafo_d_l(int V, int A){  //cria o grafo vazio, ou seja, com inicio e fim das listas iguais a nulo;

	if (V<=0 || A<=0) return NULL;

	GRAFO_D_L *grafo = (GRAFO_D_L*)malloc(sizeof(GRAFO_D_L));

	if (grafo == NULL) return NULL;

	grafo->num_vertices = V;
	grafo->num_arestas = A;

	grafo->vertices = (VERT*)malloc(sizeof(VERT)*(grafo->num_vertices));

	if(grafo->vertices == NULL) return NULL;

	int i, V1, V2, PESO = 1;

	for(i=0;i<grafo->num_vertices;i++){
		grafo->vertices[i].lista_inicio = NULL;
		grafo->vertices[i].lista_fim = NULL;
	}

	for(i=0;i<grafo->num_arestas;i++){  //laço que adiciona as arestas representadas nas entradas do usuário;
		scanf("%d %d", &V1, &V2);
		inserir_celula_d_l(grafo, V1, V2, PESO);
	}

	return grafo;
}

void apagar_grafo_d_l(GRAFO_D_L **grafo){  //função que desaloca toda a memória utilizada pelo grafo;
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

void imprimir_grafo_d_l(GRAFO_D_L *grafo){  //percorre todo o grafo imprimindo todas as arestas de acordo com a representação;
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){
		printf("%d. ", i);
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){
			printf("%d ", paux->V);
			paux = paux->prox;
		}
		printf("\n");
	}
}

void vertices_adjacentes_grafo_d_l(GRAFO_D_L *grafo, int x){  //imprime os vertices adjacentes ao vertice x, se este estiver no grafo;
	if(grafo == NULL || grafo->vertices == NULL) return;

	if (x < 0 || x >= grafo->num_vertices) return;

	CELL *paux = grafo->vertices[x].lista_inicio;

	while(paux != NULL){
		printf("%d ", paux->V);
		paux = paux->prox;
	}
	printf("\n");
}

void adicionar_aresta_grafo_d_l(GRAFO_D_L *grafo, int V1, int V2, int PESO){  //adiciona a aresta necessária se os requisitos forem atendidos (ambos os vertices existem, e o peso da aresta é maior ou igual a 0);
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices || PESO <= 0) return;

	inserir_celula_d_l(grafo, V1, V2, PESO);
}

void remover_aresta_grafo_d_l(GRAFO_D_L *grafo, int V1, int V2){  //remove a aresta necessária se os requisitos forem atendidos (ambos os vertices existem, e o peso da aresta é maior ou igual a 0);
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices) return;

	remover_celula_d_l(grafo, V1, V2);
}

void menor_peso_grafo_d_l(GRAFO_D_L *grafo){  //imprime a aresta de menor peso do grafo;
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i, V1, V2, menor_peso = INT_MAX;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){  //laço que percorre o vetor de vertices;
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){  //laço que percorre as listas de vertices de cada vertice do vertor principal;
			if(paux->PESO < menor_peso){
				menor_peso = paux->PESO;  //atualiza o menor peso até o momento;
				V1 = i;
				V2 = paux->V;
			}
		paux = paux->prox;
		}
	}
	printf("%d %d\n", V1, V2);
}

void imprimir_transposto_grafo_d_l(GRAFO_D_L *grafo){  //imprime o transposto do grafo;
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i, j;
	CELL *paux;

	for(j=0;j<grafo->num_vertices;j++){  //j define qual vertice esta sendo transposta;
		printf("%d. ", j);
		for(i=0;i<grafo->num_vertices;i++){  //percorre o vetor de vertices;
			paux = grafo->vertices[i].lista_inicio;
			while(paux != NULL){  //percorre as listas procurando os vertices iguais a j;
				if(paux->V == j)
					printf("%d(%d) ", i, paux->PESO);
				paux = paux->prox;
			}
		}
		printf("\n");
	}
}


void bsf_grafo_d_l(GRAFO_D_L *grafo, int V1, int V2){

    int i, x;
    int *cor = (int *)malloc(sizeof(int)*(grafo->num_vertices));
    int *p = (int *)malloc(sizeof(int)*(grafo->num_vertices));
    int u;
    CELL *aux = NULL;


    for(i=0;i<grafo->num_vertices;i++){
        if(i == V1){
        	cor[i] = GRAY;
    		p[i] = NIL;
        }
        else{
            cor[i] = WHITE;
            p[i] = NIL;
        }
    }

    FILA *fila = criar_fila();

    if(fila == NULL) return;

    enfileirar(fila, V1);

    while(!vazia_fila(fila)){
    	u = desenfileirar(fila);
    	aux = grafo->vertices[u].lista_inicio;
    	while(aux != NULL){
    		if(cor[aux->V] == WHITE){
    			cor[aux->V] = GRAY;
    			p[aux->V] = u;
    			enfileirar(fila, aux->V);
    		}
    		cor[u] = BLACK;
    		aux = aux->prox;
    	}
    }

    apagar_fila(&fila);

    if(p[V2] == NIL){
    	if(cor[V2] == WHITE);
    	else if(cor[V2] == BLACK){
    		printf("%d ", V2);
    	}
    }

    else{

    	PILHA *pilha = criar_pilha();

    	x = V2;
    	while(x != NIL){
    		empilhar(pilha, x);
    		x = p[x];
    	}

    	while(!vazia_pilha(pilha)){
    		x = desempilhar(pilha);
   		 	printf("%d ", x);
 	   }

 	   apagar_pilha(&pilha);
	}
    
    free(cor);
    free(p);
    printf("\n");
}
