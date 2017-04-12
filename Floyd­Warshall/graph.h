#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct vertice Vertice;

typedef struct aresta Aresta;

typedef struct grafo Grafo;

struct vertice {

    int used;

    int custo;

	int value;

	int cont;

	Vertice* prox;

	Vertice* ant;

	Vertice** lista;

};

struct aresta {

    int used;

    int value;
    
    Vertice* v1;

    Vertice* v2;

    double custo;

    Aresta* ant;

    Aresta* prox;

};

struct grafo{

	Aresta* aresta;

	Vertice* vertice;

	int q_ver;

	int q_are;

};


Grafo* criarGrafo();

void insertVertex(Grafo* g, int o);

void insertEdge(Grafo* g, double o, int a, int b);

int vertexValue(Grafo* g, int v);

double edgeValue(Grafo* g, int e);

int numVertex(Grafo* g);

int numEdge(Grafo* g);

int areAdjacent(Grafo* g, int v, int w);

void endVertices(Grafo* g, int e, Vertice** v, Vertice** w);

Vertice* opposite(Grafo* g, int v, int e);

void replaceVertex(Grafo* g, int v, int o);

void replaceEdge(Grafo* g, int e, double o);

double removeEdge(Grafo* g, int e);

int removeVertex(Grafo* g, int v);

void printGraph(Grafo* g);

#endif 
