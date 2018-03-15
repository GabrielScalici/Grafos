#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "list.h"

typedef struct node NODE;

struct node{
	int id;
	int weight;
	NODE *next;
};

typedef struct list{
	NODE *node;
} LIST;

typedef struct graph_l{
	int n_vertex;
	LIST *list;
} GRAPH_L;

/*
 Função para alocação e criação do nó
*/
NODE *create_Node(int id, int weight){
	NODE *node = (NODE *) malloc(sizeof(NODE));

	if(node != NULL){
		node->id = id;
		node->weight = weight;
		node->next = NULL;
	}

	return node;
}

/*
 Função para criação do Grafo
*/
GRAPH_L *create_Graph_L(int num){
	GRAPH_L *graph = (GRAPH_L *) malloc(sizeof(GRAPH_L));

	if(graph != NULL){
		graph->n_vertex = num;
		graph->list = (LIST *) malloc(sizeof(LIST) * num);
		int i;

		for(i = 0; i < num; i++){
			graph->list[i].node = (NODE *) malloc(sizeof(NODE));
			graph->list[i].node->id = i;
			graph->list[i].node->weight = -1;
			graph->list[i].node->next = NULL;
		}
	}

	return graph;
}

/*
 Função para liberação de memória ocupada pelo Grafo
*/
void free_Graph_L(GRAPH_L *graph){
	int i;
	for(i = 0; i < graph->n_vertex; i++){
		NODE *aux = graph->list[i].node->next;
		while(aux->next != NULL){
			NODE *prem = aux;
			aux = aux->next;
			free(prem);
		}
		free(aux);
		free(graph->list[i].node);
	}
	free(graph->list);
	free(graph);
}

/*
 Função para preenchimento da Lista
*/
GRAPH_L *fill_Graph_L(GRAPH_L *graph, int num_edges, char type){
	int a, b, w;
	int i;

	for(i = 0; i < num_edges; i++){
		scanf("%d %d %d", &a, &b, &w);
		NODE *aux = graph->list[a].node;
		NODE *pnext = NULL, *pnovo = NULL;
		while(aux->next != NULL && aux->next->id < b){
			aux = aux->next;
		}
		if(aux->next != NULL && aux->next->id == b){
			aux->next->weight = w;
		} else{
			if(aux->next != NULL){
				pnext = aux->next;
			}
			pnovo = create_Node(b, w);
			aux->next = pnovo;
			pnovo->next = pnext;
		}

		if(type == 'G'){
			NODE *gaux = graph->list[b].node;
			NODE *gpnext = NULL, *gpnovo = NULL;
			while(gaux->next != NULL && gaux->next->id < a){
				gaux = gaux->next;
			}
			if(gaux->next != NULL && gaux->next->id == a){
				gaux->next->weight = w;
			} else{
				if(gaux->next != NULL){
					gpnext = gaux->next;
				}
				gpnovo = create_Node(a, w);
				gaux->next = gpnovo;
				gpnovo->next = gpnext;
			}
		}
	}

	return graph;
}

/*
 Adicionar arestas
*/
GRAPH_L *add_Edge_L(GRAPH_L *graph, char type){
	int a, b, w;
	scanf("%d %d %d", &a, &b, &w);

	NODE *aux = graph->list[a].node;
	NODE *pnext = NULL, *pnovo = NULL;
	while(aux->next != NULL && aux->next->id < b){
		aux = aux->next;
	}
	if(aux->next != NULL && aux->next->id == b){
		aux->next->weight = w;
	} else{
		if(aux->next != NULL){
			pnext = aux->next;
		}
		pnovo = create_Node(b, w);
		aux->next = pnovo;
		pnovo->next = pnext;
	}

	if(type == 'G'){ /* Não direcional */
		NODE *gaux = graph->list[b].node;
		NODE *gpnext = NULL, *gpnovo = NULL;
		while(gaux->next != NULL && gaux->next->id < a){
			gaux = gaux->next;
		}
		if(gaux->next != NULL && gaux->next->id == a){
			gaux->next->weight = w;
		} else{
			if(gaux->next != NULL){
				gpnext = gaux->next;
			}
			gpnovo = create_Node(a, w);
			gaux->next = gpnovo;
			gpnovo->next = gpnext;
		}
	}
	return graph;
}

/*
 Remover arestas
*/
GRAPH_L *remove_Edge_L(GRAPH_L *graph, char type){
	int a, b;
	scanf("%d %d", &a, &b);

	NODE *aux = graph->list[a].node;
	NODE *pnext = NULL;
	while(aux->next != NULL && aux->next->id != b){
		aux = aux->next;
	}
	if(aux->next != NULL){ /* Manipulação de Ponteiros para que não ocorra perda de nós */
		pnext = aux->next->next;
		aux->next->next = NULL;
		free(aux->next);
		aux->next = pnext;
	}

	if(type == 'G'){ /* Não direcional */
		NODE *gaux = graph->list[b].node;
		NODE *gpnext = NULL;
		while(gaux->next != NULL && gaux->next->id != a){
			gaux = gaux->next;
		}
		if(gaux->next != NULL){
			gpnext = gaux->next->next;
			gaux->next->next = NULL;
			free(gaux->next);
			gaux->next = gpnext;
		}
	}
	return graph;
}

/*
 Printar Grafo
*/
void print_Graph_L(GRAPH_L *graph){
	if(graph != NULL){
		int i;
		/* É necessário percorrer toda a lista para listar todos os vértices e arestas presentes no Grafo */
		for(i = 0; i < graph->n_vertex; i++){
			NODE *aux = graph->list[i].node;
			if(aux != NULL){
				printf("%d. ", i);
				while(aux->next != NULL){
					printf("%d(%d) ", aux->next->id, aux->next->weight);
					aux = aux->next;
				}
				printf("\n");
			}
		}
	}
}

/*
  	Printar Grafo Transposto
*/
void print_TransGraph_L(GRAPH_L *graph, char type){
	/* A impressão do Transposto só é feita quando o grafo é um Dígrafo */
	if(type == 'D'){
		/* A impressão é dada após percorrer a lista de modo a procurar pela
		 existência de cada vértice na Lista de Adjacências dos outros */
		int i, j;
		for(i = 0; i < graph->n_vertex; i++){
			printf("%d. ", i); /* Vértice a ser buscado */
			for(j = 0; j < graph->n_vertex; j++){
				NODE *aux = graph->list[j].node;
				while(aux->next != NULL && aux->next->id < i){
					aux = aux->next;
				}
				if(aux->next != NULL && aux->next->id == i){
					printf("%d(%d) ", j, aux->next->weight); /* Vértice adjacente e o peso da aresta */
				}
			}
			printf("\n");
		}
	}
}

/*
 Printar vértices adjacenteces ao vértice solicitado
*/
void print_AdjVertex_L(GRAPH_L *graph){
	int i;

	scanf("%d", &i); /* Vértice solicitado */

	NODE *paux = graph->list[i].node;

	/* Percurso da Lista de Adjacência */
	while(paux->next != NULL){
		printf("%d ", paux->next->id);
		paux = paux->next;
	}
	printf("\n");
}

/*
 Printar aresta com menor peso
*/
void print_LighterEdge_L(GRAPH_L *graph){
	int i, min = INT_MAX;
	NODE *paux = NULL;

	/* percorrer toda a lista para encontrar a aresta de menor peso */
	for(i = 0; i < graph->n_vertex; i++){
		paux = graph->list[i].node;
		while(paux->next != NULL){
			if(paux->next->weight < min) min = paux->next->weight;
			paux = paux->next;
		}
	}
	for(i = 0; i < graph->n_vertex; i++){
		paux = graph->list[i].node;
		while(paux->next != NULL){
			if(paux->next->weight == min){
				printf("%d %d\n", i, paux->next->id);
				return;
			}
			paux = paux->next;
		}
	}

}
