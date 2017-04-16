#ifndef _GRAPH_H_
#define _GRAPH_H_

#ifdef __cplusplus
extern "C" {
#endif

//FILA DE PRIORIDADE

typedef struct elemento ELEMENTO;

//struct definindo os atributos de um fila
typedef struct fila_estatica FILA_ESTATICA;

//Criar a fila estatica circular
FILA_ESTATICA * criar_fila();

//Verifica se a fila esta cheia
int cheia(FILA_ESTATICA * fila);

//Verifica se a fila esta vazia
int vazia(FILA_ESTATICA * fila);

int tamanho(FILA_ESTATICA * fila);

//Adiciona item na fila
int entra(FILA_ESTATICA * fila, int item, double dist);

//Remove um elemento da fila
int sai(FILA_ESTATICA * fila);

//Ordena a fila para ela ter prioridade
void ordenar(FILA_ESTATICA * fila);

//FUncao para usar no dijkstra
void replaceKey(FILA_ESTATICA * fila, int id, double dist_mudada);

/* GRAFO */
/* Vertex */
typedef struct vertex Vertex;

/* Edge */
typedef struct edge Edge;

/* Graph */
typedef struct graph Graph;


/* MÉTODOS QUE MODIFICAM O GRAFO */
/* Cria um grafo */
Graph* createGraph(void);

/* Apaga um grafo */
void eraseGraph(Graph* g);

/* Função para adicionar um vértice ao grafo */
int insertVertex(Graph* g, int o);

/* Função para adicionar uma aresta não direcionada ao grafo */
int insertEdge(Graph* g, int v, int w, double o);

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o);

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o);

/* Função para remover um vértice do grafo */
int removeVertex(Graph* g, int v);

/* Função para remover uma aresta do grafo */
int removeEdge(Graph* g, int e);


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g);

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g);

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v);

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w);


/* MÉTODOS DE IMPRESSÃO */

/* ATENÇÃO: Caso o grafo não seja direcionado, as funções de impressão das
   arestas ordenará de forma ascendente os identificadores dos vértices. */

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada vértice contendo os valores
   armazenados nestes, i.e., imprime os pares ordenados (identificador(v), valor(v))*/
void printVertices(Graph* g);

/* Imprime a quantidade de arestas de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada aresta contendo as tuplas
   (identificador(e), identificador(v1), identificador(v2), valor(e)), onde os
   identificadores de v1 e v2 também são ordenados de forma ascendente caso o
   grafo não seja direcionado */
void printEdges(Graph* g);

/* Imprime a quantidade de vértices, a quantidade de arestas, a lista de vértices
   e a lista de arestas de um grafo */
void printGraph(Graph* g);

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada de
   forma ascendente pelo identificador de cada vértice contendo o grau deste, i.e.,
   imprime os pares ordenados (identificador(v), grau(v))*/
void printDegree(Graph* g);

/* Imprime TRUE caso os dois vértices sejam adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w);

//Algortimo de caminho minimo
void dijkstra(Graph * g, int s);


#ifdef __cplusplus
}
#endif

#endif /*_GRAPH_H_*/

