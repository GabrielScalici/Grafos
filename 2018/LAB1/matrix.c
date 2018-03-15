#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
 TAD Matrix
*/
typedef struct g_m{
	int **matrix;
	int n_vertex;
} GRAPH_M;

/*
 Criacao da Matriz
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
 Liberar memoria
*/
void free_Graph_M(GRAPH_M *g){
	if(g != NULL && g->matrix != NULL){
		int i;
		for(i = 0; i < g->n_vertex; i++){
			free(g->matrix[i]);
		}
		free(g->matrix);
		free(g);
	}
}

/*
 Criar Grafo
*/
GRAPH_M *create_Graph_M(int num){
	GRAPH_M *g = (GRAPH_M *) malloc(sizeof(GRAPH_M));

	if(g != NULL){
		g->matrix = create_Matrix(num, num);
		g->n_vertex = num;
	}
	return g;
}

/*
 Função para preenchimento da matriz que compoe o grafo
*/
GRAPH_M *fill_Graph_M(GRAPH_M *g, int edges, char type){
	if(g != NULL && g->matrix != NULL){
		int i;
		int a, b, w;
		if(type == 'G'){
			for(i = 0; i < edges; i++){
				scanf("%d %d %d", &a, &b, &w);
				g->matrix[a][b] = w;
				g->matrix[b][a] = w;
			}
		} else{
			for(i = 0; i < edges; i++){
				scanf("%d %d %d", &a, &b, &w);
				g->matrix[a][b] = w;
			}
		}
	}
	return g;
}

/*
 Adicionar arestas de arestas
*/
GRAPH_M *add_Edge_M(GRAPH_M *g, char type){
	if(g != NULL && g->matrix != NULL){
		int a, b, w;
		if(type == 'G'){
			scanf("%d %d %d", &a, &b, &w);
			g->matrix[a][b] = w;
			g->matrix[b][a] = w;
		} else{
			scanf("%d %d %d", &a, &b, &w);
			g->matrix[a][b] = w;
		}
	}
	return g;
}

/*
 Remover arestas
*/
GRAPH_M *remove_Edge_M(GRAPH_M *g, char type){
	if(g != NULL && g->matrix != NULL){
		int a, b;
		if(type == 'G'){
			scanf("%d %d", &a, &b);
			g->matrix[a][b] = -1;
			g->matrix[b][a] = -1;
		} else{
			scanf("%d %d", &a, &b);
			g->matrix[a][b] = -1;
		}
	}
	return g;
}

/*
 Printar o grafo
*/
void print_Graph_M(GRAPH_M *g){
	if(g != NULL && g->matrix != NULL){
		int i, j;

		for(i = 0; i < g->n_vertex; i++){
			for(j = 0; j < g->n_vertex; j++){
				if(g->matrix[i][j] == -1){
					printf(". ");
				} else{
					printf("%d ", g->matrix[i][j]);
				}
			}
			printf("\n");
		}
	}
}

/*
 Printar Grafo Transposto
*/
void print_TransGraph_M(GRAPH_M *g, char type){
	if(g != NULL && g->matrix != NULL){
		/* A impressão só é feita se corresponde a um Dígrafo, sendo assim a matriz não é obrigatoriamente simétrica */
		if(type == 'D'){
			int i, j;

			for(j = 0; j < g->n_vertex; j++){
				for(i = 0; i < g->n_vertex; i++){
					if(g->matrix[i][j] == -1){
						printf(". ");
					} else{
						printf("%d ", g->matrix[i][j]);
					}
				}
				printf("\n");
			}
		}
	}
}

/*
 Printar vértices adjacenteces ao vértice solicitado
*/
void print_AdjVertex_M(GRAPH_M *g){
	if(g != NULL && g->matrix != NULL){
		int i, v;
		scanf("%d", &v);

		for(i = 0; i < g->n_vertex; i++){
			if(g->matrix[v][i] != -1) printf("%d ", i);
		}
		printf("\n");
	}
}

/*
 Printar aresta com menor peso
*/
void print_LighterEdge_M(GRAPH_M *g){
	if(g != NULL && g->matrix != NULL){
		int max = INT_MAX;
		int i, j;

		for(i = 0; i < g->n_vertex; i++){
			for(j = 0; j < g->n_vertex; j++){
				if(g->matrix[i][j] < max && g->matrix[i][j] != -1){
					max = g->matrix[i][j];
				}
			}
		}
		for(i = 0; i < g->n_vertex; i++){
			for(j = 0; j < g->n_vertex; j++){
				if(g->matrix[i][j] == max){
					printf("%d %d\n", i, j);
					return;
				}
			}
		}
	}
}
