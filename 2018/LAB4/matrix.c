#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "matrix.h"

/*
 Struct base para o grafo com a TAD Matrix
*/
typedef struct graph_m{
	int **matrix;
	int n_verdex;
} GRAPH_M;

typedef struct node NODE;
struct node{
	int id;
	int color;
	int weight;
	int pre;
};

/*
 Função para alocação e criação da matriz
*/
int **create_Matrix(int lin, int col){
	int **matrix = NULL;
	int i, j;

	matrix = (int **) malloc(sizeof(int *) * lin);

	for(i = 0; i < lin; i++){
		matrix[i] = (int *) malloc(sizeof(int) * col);
		for(j = 0; j < col; j++) matrix[i][j] = -1;
	}

	return matrix;
}

/*
 Função para liberação de memória ocupada pelo Grafo
*/
void free_Graph_M(GRAPH_M *graph){
	if(graph != NULL && graph->matrix != NULL){
		int i;
		for(i = 0; i < graph->n_verdex; i++){
			free(graph->matrix[i]);
		}
		free(graph->matrix);
		free(graph);
	}
}

/*
 Função para criação do Grafo
*/
GRAPH_M *create_Graph_M(int num){
	GRAPH_M *graph = (GRAPH_M *) malloc(sizeof(GRAPH_M));

	if(graph != NULL){
		graph->matrix = create_Matrix(num, num);
		graph->n_verdex = num;
	}
	return graph;
}

/*
 Função para preenchimento do Grafo, por sua vez, preenchimento da matriz
*/
GRAPH_M *fill_Graph_M(GRAPH_M *graph, int edges, char type){
	if(graph != NULL && graph->matrix != NULL){
		int i;
		int a, b, w;
		if(type == 'G'){
			for(i = 0; i < edges; i++){
				scanf("%d %d %d", &a, &b, &w);
				graph->matrix[a][b] = w;
				graph->matrix[b][a] = w;
			}
		} else{
			for(i = 0; i < edges; i++){
				scanf("%d %d %d", &a, &b, &w);
				graph->matrix[a][b] = w;
			}
		}
	}
	return graph;
}

/*
 Função para geração da Minimum Spanning Tree a partir do grafo passado por parametro
*/
void Prim_MST(GRAPH_M *graph){
	int i, j, k, count, pre, pos, aux;
	NODE *list = (NODE *) malloc(sizeof(NODE) * graph->n_verdex);

	// Vetor de nós para marcação de visitação
	for(i = 0; i < graph->n_verdex; i++){
		list[i].id = i;
		list[i].color = 0; // Não visitado
		list[i].pre = -1;
	}

	list[0].color = 1; // Primeiro nó a ser inserido na árvore
	for(i = 0; i < graph->n_verdex - 1; i++){
		aux = INT_MAX;
		for(j = 0; j < graph->n_verdex; j++){ // Busca pelos vértices do grafo
			if(list[j].color == 1){ // Caso já pertença à árvore
				for(k = 0; k < graph->n_verdex; k++){ // Busca pelos vértices vizinhos aos vértices pertecentes à árvore
					if(aux > graph->matrix[j][k] && graph->matrix[j][k] != -1 && list[k].color == 0){ // Menor caminho - (-1) Não existe ligação - Não visitado
						aux = graph->matrix[j][k]; // Recebe o menor peso
						pre = j; // O pré é correpondente ao valor da linha
						pos = k; // O pós é correpondente ao valor da coluna
					}
				}
			}
		}
		// Seta-se o predecessor
		list[pos].pre = pre;
		// Torna visitado o vértice extremo a aresta de menor peso
		list[pos].color = 1;
		//Impressão ordenada
		if(pre > pos){
			printf("(%d,%d) ", pos, pre);
		} else{
			printf("(%d,%d) ", pre, pos);
		}
	}
	printf("\n");
	free(list);
}

/*
 Função para adição de arestas
*/
GRAPH_M *add_Edge_M(GRAPH_M *graph, char type){
	if(graph != NULL && graph->matrix != NULL){
		int a, b, w;
		if(type == 'G'){
			scanf("%d %d %d", &a, &b, &w);
			graph->matrix[a][b] = w;
			graph->matrix[b][a] = w;
		} else{
			scanf("%d %d %d", &a, &b, &w);
			graph->matrix[a][b] = w;
		}
	}
	return graph;
}

/*
 Função para remoção de arestas
*/
GRAPH_M *remove_Edge_M(GRAPH_M *graph, char type){
	if(graph != NULL && graph->matrix != NULL){
		int a, b;
		if(type == 'G'){
			scanf("%d %d", &a, &b);
			graph->matrix[a][b] = -1;
			graph->matrix[b][a] = -1;
		} else{
			scanf("%d %d", &a, &b);
			graph->matrix[a][b] = -1;
		}
	}
	return graph;
}

/*
 Função para impressão do Grafo
*/
void print_Graph_M(GRAPH_M *graph){
	if(graph != NULL && graph->matrix != NULL){
		int i, j;

		for(i = 0; i < graph->n_verdex; i++){
			for(j = 0; j < graph->n_verdex; j++){
				if(graph->matrix[i][j] == -1){
					printf(". ");
				} else{
					printf("%d ", graph->matrix[i][j]);
				}
			}
			printf("\n");
		}
	}
}

/*
 Função para impressão do Grafo Transposto
*/
void print_TransGraph_M(GRAPH_M *graph, char type){
	if(graph != NULL && graph->matrix != NULL){
		/* A impressão só é feita se corresponde a um Dígrafo, sendo assim a matriz não é obrigatoriamente simétrica */
		if(type == 'D'){
			int i, j;

			for(j = 0; j < graph->n_verdex; j++){
				for(i = 0; i < graph->n_verdex; i++){
					if(graph->matrix[i][j] == -1){
						printf(". ");
					} else{
						printf("%d ", graph->matrix[i][j]);
					}
				}
				printf("\n");
			}
		}
	}
}

/*
 Função para impressão dos vértices adjacenteces ao vértice solicitado
*/
void print_AdjVerdex_M(GRAPH_M *graph){
	if(graph != NULL && graph->matrix != NULL){
		int i, v;
		scanf("%d", &v);

		for(i = 0; i < graph->n_verdex; i++){
			if(graph->matrix[v][i] != -1) printf("%d ", i);
		}
		printf("\n");
	}
}

/*
 Função para impressão da aresta com menor peso
*/
void print_LighterEdge_M(GRAPH_M *graph){
	if(graph != NULL && graph->matrix != NULL){
		int max = INT_MAX;
		int i, j;

		for(i = 0; i < graph->n_verdex; i++){
			for(j = 0; j < graph->n_verdex; j++){
				if(graph->matrix[i][j] < max && graph->matrix[i][j] != -1){
					max = graph->matrix[i][j];
				}
			}
		}
		for(i = 0; i < graph->n_verdex; i++){
			for(j = 0; j < graph->n_verdex; j++){
				if(graph->matrix[i][j] == max){
					printf("%d %d\n", i, j);
					return;
				}
			}
		}
	}
}
