#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grafo_g_m.h"

#define menor(a, b) ((a < b) ? a : b)  //macro que retorna o menor de dois inteiros;
#define maior(a, b) ((a > b) ? a : b)  //macro que retorna o maior de dois inteiros;

struct grafo_g_m {
	int **matriz;  //ponteiro para a matriz que será dinamicamente alocada;
	unsigned int num_vertices;  //numero de vertices do grafo;
	unsigned int num_arestas;  //numero de arestas do grafo;
};

GRAFO_G_M *criar_grafo_g_m(int V, int A){  //função para a criação da matriz que representa o grafo;

	if (V<=0 || A<=0) return NULL;

	GRAFO_G_M *grafo = (GRAFO_G_M*)malloc(sizeof(GRAFO_G_M));

	if(grafo == NULL) return NULL;

	grafo->num_vertices = V;
	grafo->num_arestas = A;

	int i, j;

	grafo->matriz = (int**)malloc(sizeof(int*)*(grafo->num_vertices));
	for(i=0;i<(grafo->num_vertices);i++){
		grafo->matriz[i] = (int*)malloc(sizeof(int)*(grafo->num_vertices));
	}

	if(grafo->matriz == NULL) return NULL;

	for(i=0;i<(grafo->num_vertices);i++){  //loop que "seta" todos os elementos da matriz com -1, o que indica que não existe aresta entre os dois vertices;
		for(j=0;j<(grafo->num_vertices);j++){
			grafo->matriz[i][j] = -1;
		}
	}

	int V1, V2, PESO;

	for(i=0;i<(grafo->num_arestas);i++){  //loop que recebe as arestas e modifica a matriz, que até o momento representa um grafo vazio;
		scanf("%d %d %d", &V1, &V2, &PESO);

		if(V1 < (grafo->num_vertices) && V2 < (grafo->num_vertices)){  //verifica se o vertice existe no grafo;
			grafo->matriz[V1][V2] = PESO;
			grafo->matriz[V2][V1] = PESO;
		}
	}

	return grafo;
}

void apagar_grafo_g_m(GRAFO_G_M **grafo){  //desaloca a matriz para não haver memory leaks;
	if(grafo == NULL || (*grafo) == NULL || (*grafo)->matriz == NULL) return;

	int i;

	for(i=0;i<((*grafo)->num_vertices);i++){
		free((*grafo)->matriz[i]);
	}

	free((*grafo)->matriz);
	free(*grafo);
	*grafo = NULL;
}

void imprimir_grafo_g_m(GRAFO_G_M *grafo){  //imprime a matriz
	if(grafo == NULL || grafo->matriz == NULL) return;

	int i, j;

	for(i=0;i<grafo->num_vertices;i++){  //percorre a matriz e imprime '.' se a aresta não existe, conforme a respresentação;
		for(j=0;j<grafo->num_vertices;j++){
			if(grafo->matriz[i][j] == -1) printf(". ");
			else{
				printf("%d ", grafo->matriz[i][j]);		
			}
		}
		printf("\n");
	}
}

void vertices_adjacentes_grafo_g_m(GRAFO_G_M *grafo, int x){
	if(grafo == NULL || grafo->matriz == NULL) return;

	if (x < 0 || x >= grafo->num_vertices) return;

	int i;

	for(i=0;i<(grafo->num_vertices);i++){  //percorre a linha da matriz e imprime aquelas que são diferentes de -1;
		if(grafo->matriz[x][i] != -1) printf("%d ", i);
	}
	printf("\n");
}

void adicionar_aresta_grafo_g_m(GRAFO_G_M *grafo, int V1, int V2, int PESO){  //troca o valor do elemento matriz[V1][V2] pelo peso inserido;
	if(grafo == NULL || grafo->matriz == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices || PESO <= 0) return;

	//adiciona a aresta nos dois sentidos ja que o grafo não é digrafo;

	grafo->matriz[V1][V2] = PESO;
	grafo->matriz[V2][V1] = PESO;
}

void remover_aresta_grafo_g_m(GRAFO_G_M *grafo, int V1, int V2){  //troca o valor do elemento matriz[V1][V2] por '-1';
	if(grafo == NULL || grafo->matriz == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices) return;

	//remove a aresta nos dois sentidos ja que o grafo não é digrafo;

	grafo->matriz[V1][V2] = -1;
	grafo->matriz[V2][V1] = -1;
}

void menor_peso_grafo_g_m(GRAFO_G_M *grafo){
	int i, j, menor_peso = INT_MAX, V1, V2;

	for(i=0;i<grafo->num_vertices;i++){  //percorre a matriz procurando o menor numero diferente de '-1' presente na matriz e imprime os vertices desta aresta;
		for(j=0;j<grafo->num_vertices;j++){
			if((grafo->matriz[i][j] != -1) && (grafo->matriz[i][j] < menor_peso)){
				menor_peso = grafo->matriz[i][j];
				V1 = menor(i, j);
				V2 = maior(i, j);
			}
		}
	}

	printf("%d %d\n", V1, V2);

}