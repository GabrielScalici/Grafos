#ifndef TAD_MATRIX_H_
#define TAD_MATRIX_H_

typedef struct graph_m GRAPH_M; /* Struct representativa do grafo */

/* Funções para criar o grafo, preencher e liberar a memória alocada */
GRAPH_M *create_Graph_M(int);
void free_Graph_M(GRAPH_M *);
GRAPH_M *fill_Graph_M(GRAPH_M *, int, char);

/* Funções para adição e remoção de arestas */
GRAPH_M *add_Edge_M(GRAPH_M *, char);
GRAPH_M *remove_Edge_M(GRAPH_M *, char);

/* Função para geração da Minimum Spanning Tree */
void Prim_MST(GRAPH_M *);

/* Funções para impressão solicitadas pelo usuario */
void print_Graph_M(GRAPH_M *);
void print_TransGraph_M(GRAPH_M *, char);
void print_AdjVerdex_M(GRAPH_M *);
void print_LighterEdge_M(GRAPH_M *);

#endif
