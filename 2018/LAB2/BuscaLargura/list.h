#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct node NODE;
struct node{
	int id;
	int color;
	int dist;
	int fim;
	NODE *pre;
	NODE *next;
};

typedef struct graph_l GRAPH_L;

/* Funções para criar o grafo, preencher e liberar a memória alocada */
GRAPH_L *create_Graph_L(int);
void free_Graph_L(GRAPH_L *);
GRAPH_L *fill_Graph_L(GRAPH_L *, int, char);

/* Funções para adição e remoção de arestas */
GRAPH_L *add_Edge_L(GRAPH_L *, char);
GRAPH_L *remove_Edge_L(GRAPH_L *, char);
void BFS(GRAPH_L *, int, int);

/* Funções para impressão solicitadas pelo usuario */
void print_Graph_L(GRAPH_L *);
void print_TransGraph_L(GRAPH_L *, char);
void print_AdjVerdex_L(GRAPH_L *);
void print_LighterEdge_L(GRAPH_L *);

#endif
