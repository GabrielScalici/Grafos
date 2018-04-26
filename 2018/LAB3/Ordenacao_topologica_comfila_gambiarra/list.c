
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "list.h"
#include "fila.h"

typedef struct list{
	NODE *node;
} LIST;

typedef struct graph_l{
	int n_verdex;
	LIST *list;
} GRAPH_L;

/*
 Função para alocação e criação do nó
*/
NODE *create_Node(int id){
	NODE *node = (NODE *) malloc(sizeof(NODE));

	if(node != NULL){
		node->id = id;
		node->color = 0; // Nó não visitado
		node->dist = 0;
		node->fim = 0;
		node->pre = NULL;
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
		graph->n_verdex = num;
		graph->list = (LIST *) malloc(sizeof(LIST) * num);
		int i;

		for(i = 0; i < num; i++){
			graph->list[i].node = (NODE *) malloc(sizeof(NODE));
			graph->list[i].node->id = i;
			graph->list[i].node->dist = 0;
			graph->list[i].node->fim = 0;
			graph->list[i].node->color = 0;
			graph->list[i].node->pre = NULL;
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
	for(i = 0; i < graph->n_verdex; i++){
		NODE *aux = graph->list[i].node->next;
		while(aux != NULL){
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
 Função para preenchimento do Grafo, por sua vez, preenchimento da lista
*/
GRAPH_L *fill_Graph_L(GRAPH_L *graph, int num_edges, char type){
	int a, b, i;

	for(i = 0; i < num_edges; i++){
		scanf("%d %d", &a, &b);
		NODE *aux = graph->list[a].node;
		NODE *pre = graph->list[a].node;
		NODE *pnext = NULL, *pnovo = NULL;
		while(aux->next != NULL && aux->next->id < b){
			aux = aux->next;
		}
		if(aux->next != NULL){
			pnext = aux->next;
		}
		pnovo = create_Node(b);
		pnovo->pre = pre;
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
				//gaux->next->weight = w;
			} else{
				if(gaux->next != NULL){
					gpnext = gaux->next;
				}
				gpnovo = create_Node(a);
				gaux->next = gpnovo;
				gpnovo->next = gpnext;
			}
		}

	return graph;
}

void print_Way(NODE *origin, NODE *verdex){
	if(verdex != NULL){
	if(origin->id == verdex->id){
		printf("%d teta", origin->id);
	} else{
		print_Way(origin, verdex->pre);
		printf("%d teta", verdex->id);
	}
	}
}

/*
 Função para encontrar menor caminho
*/
void BFS(GRAPH_L *graph, int a, int b){
	NODE *origin = graph->list[a].node;
	NODE *aux = origin->next;
	int i = 0, j, *vet = NULL;

	if(a == b){ // Caso a origem e destino sejam o mesmo
		printf("%d\n", a);
		return;
	}

	if(aux == NULL){ // Não há caminho
		printf("\n");
		return;
	}

	// Modo de busca BFS
	for(i = 0; i < graph->n_verdex; i++){
		graph->list[i].node->color = 0;
		graph->list[i].node->dist = 0;
		graph->list[i].node->pre = NULL;
	}

	origin->color = -1; // Visitado
	origin->dist = 0;
	origin->pre = NULL;

	FILA *fila = criar_fila();

	enfileirar(fila, origin);

	vet = (int *) malloc(sizeof(int) * graph->n_verdex);

	while(!vazia(fila)){
		aux = desenfileirar(fila);
		NODE *find = graph->list[aux->id].node->next;
		while(find != NULL){
			if(graph->list[find->id].node->color == 0){ // Não visitado
				graph->list[find->id].node->color = -1; // Visitado
				graph->list[find->id].node->dist = find->dist + 1;
				graph->list[find->id].node->pre = find->pre;
				enfileirar(fila, graph->list[find->id].node);
			}
			find = find->next;
		}
		graph->list[aux->id].node->color = 1;
	}

	print_Way(origin, graph->list[b].node);
	printf("\n");
}

void DFS_visit(GRAPH_L *graph, NODE *aux, int *t, int *ptr, int* i_aux){
	aux->color = -1; // Visitado
	(*t)++;
	aux->dist = *t;
	NODE *visit = aux->next;
	while(visit != NULL){
		if(graph->list[visit->id].node->color == 0){
			graph->list[visit->id].node->pre = aux;
			DFS_visit(graph, graph->list[visit->id].node, t, ptr, i_aux);
		}
		visit = visit->next;
	}
	aux->color = 1; // Processado
	//printf("%d ", aux->id);
	ptr[*(i_aux)] = aux->id;
	*(i_aux) += 1;

	aux->fim = *t = *t + 1;
}

GRAPH_L *DFS(GRAPH_L *graph, int n){
	int i, j;
	int* ptr = malloc(n * sizeof(int));
	int* i_aux = calloc(1,sizeof(int));


	for(i = 0; i < graph->n_verdex; i++){
		graph->list[i].node->color = 0; // Não visitado
		graph->list[i].node->pre = NULL;
	}

	int t = 0;

	for(i = 0; i < graph->n_verdex; i++){
		if(graph->list[i].node->color == 0){ // Não visitado
			DFS_visit(graph, graph->list[i].node, &t, ptr, i_aux);
		}
	}
	//Imprimindo ordem inversa
	for(j = *(i_aux)-1; j >= 0; j-- ){

			printf("%d ", ptr[j]);
	}

	free(ptr);
	return graph;
}

/*
 Função para adição de arestas
*/
GRAPH_L *add_Edge_L(GRAPH_L *graph, char type){
	int a, b;
	scanf("%d %d", &a, &b);

	NODE *aux = graph->list[a].node;
	NODE *pnext = NULL, *pnovo = NULL;
	while(aux->next != NULL && aux->next->id < b){
		aux = aux->next;
	}
	if(aux->next != NULL && aux->next->id == b){
		//aux->next->weight = w;
	} else{
		if(aux->next != NULL){
			pnext = aux->next;
		}
		pnovo = create_Node(b);
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
			//gaux->next->weight = w;
		} else{
			if(gaux->next != NULL){
				gpnext = gaux->next;
			}
			gpnovo = create_Node(a);
			gaux->next = gpnovo;
			gpnovo->next = gpnext;
		}
	}
	return graph;
}

/*
 Função para remoção de arestas
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
 Função para impressão do Grafo
*/
void print_Graph_L(GRAPH_L *graph){
	if(graph != NULL){
		int i;
		/* É necessário percorrer toda a lista para listar todos os vértices e arestas presentes no Grafo */
		for(i = 0; i < graph->n_verdex; i++){
			NODE *aux = graph->list[i].node;
			if(aux != NULL){
				printf("%d. ", i);
				while(aux->next != NULL){
					printf("%d ", aux->next->id);
					aux = aux->next;
				}
				printf("\n");
			}
		}
	}
}

/*
 Função para impressão do Grafo Transposto
*/
void print_TransGraph_L(GRAPH_L *graph, char type){
	/* A impressão do Transposto só é feita quando o grafo é um Dígrafo */
	if(type == 'D'){
		/* A impressão é dada após percorrer a lista de modo a procurar pela existência de cada vértice na Lista de Adjacências dos outros */
		int i, j;
		for(i = 0; i < graph->n_verdex; i++){
			printf("%d. ", i); /* Vértice a ser buscado */
			for(j = 0; j < graph->n_verdex; j++){
				NODE *aux = graph->list[j].node;
				while(aux->next != NULL && aux->next->id < i){
					aux = aux->next;
				}
				if(aux->next != NULL && aux->next->id == i){
					printf("%d ", j); /* Vértice adjacente e o peso da aresta */
				}
			}
			printf("\n");
		}
	}
}

/*
 Função para impressão dos vértices adjacenteces ao vértice solicitado
*/
void print_AdjVerdex_L(GRAPH_L *graph){
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
