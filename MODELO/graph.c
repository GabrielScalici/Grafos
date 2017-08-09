#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX_VERTICES 20
#define MAX_EDGES 100

#define FALSE 0
#define TRUE 1

/* Vertex */
struct vertex {
    /* marcador que indica se o vértice está sendo usado (used == TRUE) ou não
    ** (used==FALSE) */
    int used;
    
    /* objeto armazenado pelo vértice */
	int value;
};

/* Edge */
struct edge {
    /* marcador que indica se a aresta está sendo usada (used == TRUE) ou não
    ** (used == FALSE) */
    int used;
    
    /* primeiro vértice da aresta */
    int v1;
    
    /* segundo vértice da aresta */
    int v2;
    
    /* objeto armazenado pela aresta */
    int value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    /* vetor estático que armazena os vértices */
    Vertex vertices[MAX_VERTICES];
    
    /* vetor estático que armazena as arestas */
    Edge edges[MAX_EDGES];
    
    /* armazena o número de vértices e o número de arestas do grafo*/
    int n_vertices, n_edges;
};

Graph* createGraph(void) {
    int i, j;
    Graph* g;
    
    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (Graph*) malloc(sizeof(Graph));

    /* Marca todos os vértices como livres (i.e., não utilizadas) */
    for (i = 0; i < MAX_VERTICES; i++) { g->vertices[i].used = FALSE; }
    
    /* Marca todas as arestas como livres (i.e., não utilizadas) */
    for (j = 0; j < MAX_EDGES; j++) { g->edges[j].used = FALSE; }
    
    g->n_vertices = 0;
    g->n_edges = 0;
    
    return g;
}

/* Apaga um grafo */
void eraseGraph(Graph* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo */
void insertVertex(Graph* g, int o) {
    int i;
    
    for (
    	i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == FALSE) break;
    }
    
    if (i < MAX_VERTICES) {
        g->n_vertices++;
        g->vertices[i].value = o;
        g->vertices[i].used = TRUE;
    }
}

/* Função para adicionar uma aresta ao grafo */
void insertEdge(Graph* g, int v, int w, int o)  {
    
    int i;
    /* IMPLEMENTAR! */
    //Atualizando o contador
 	for(i = 0; i < MAX_EDGES; i++){
 		if(g->edges[i].used == FALSE) break;
 	}

 	//Verificando se anda tem espaço para colocar arestas
 	if (i < MAX_EDGES){
 		//Caso esteja correto, inserir a aresta
 		g->n_edges++;
 		g->edges[i].value = o;
 		g->edges[i].used = TRUE;
 		g->edges[i].v1 = v;
 		g->edges[i].v2 = w;
  	}else{
  		printf("ERRO, Nao ha espaco suficiente");
  	}

}

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o) {
    g->vertices[v].value = o;
}

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o) {
    g->edges[e].value = o;
    
}

/* Função para remover um vértice do grafo */
void removeVertex(Graph* g, int v) {
    int i;

    g->vertices[v].used = FALSE;
    g->n_vertices--;

    //Removendo a aresta que antes ligava esse vértice
    for(i = 0; i < MAX_EDGES; i++){	
    	if(g->edges[i].used == TRUE){
    		if(g->edges[i].v2 == v || g->edges[i].v1 == v){
    			removeEdge(g, i);
   			 }
    	}
   	}
}

/* Função para remover uma aresta do grafo */
void removeEdge(Graph* g, int e) {
    g->edges[e].used = FALSE;
    g->n_edges--;
}


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g) {
    return g->n_vertices;
    
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g) {
    return g->n_edges;
}

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v) {
    
    int i, d = 0;

    //Analisar todas as arestas para ver quais tem par com o vertice desejado
   	for(i = 0; i < MAX_EDGES; i++){
    	//Verificando se esta sendo usado
    	if(g->edges[i].used == TRUE){
    		//DOis if pois pode ser um loop
    		//Verificando quantas arestas tem o vertice
    		if(g->edges[i].v1 == v){
    			//Aumentando o grau
    			d++;
    		}else if(g->edges[i].v2 == v){
    			//Aumentando o grau
    			d++;
    		}
    	}
    }

    return d;
    
}

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w) {
    int i;

    //Analisar todas as arestas para ver quais tem par com o vertice desejado
    for(i = 0; i < MAX_EDGES; i ++){
    	//Verificando se esta sendo usado
    	if(g->edges[i].used == TRUE){
    		//Verificando se a aresta liga os dois vertices desejados
    		if(g->edges[i].v1 == v && g->edges[i].v2 == w || g->edges[i].v1 == w && g->edges[i].v2 == v){
    				return TRUE;
    		}
    	}
    }
    
    return FALSE;
}


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
void printVertices(Graph* g) {
    int i, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
}

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
void printEdges(Graph* g) {
    int j, num_edges;
    
    num_edges = numEdges(g);
    printf("%d\n", num_edges);
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime o grafo */
void printGraph(Graph* g) {
    int i, j, num_vertices, num_edges;
    
    num_edges = numEdges(g);
    num_vertices = numVertices(g);
    printf("%d\n%d\n", num_vertices, num_edges);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime uma lista contendo o grau de cada vértice */
void printDegree(Graph* g) {
    int i, dg, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE) {
            dg = degree(g, i);
            printf("%d %d\n", i, dg);
        }
    }
}

/* Imprime TRUE se dois vértices são adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w) {
    if (areAdjacent(g, v, w)) printf("TRUE\n");
    else printf("FALSE\n");
}

