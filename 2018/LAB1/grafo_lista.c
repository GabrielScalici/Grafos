#include <stdio.h>


struct vertex {
  int used;
	int value;
};

struct edge {
    int used;
    int v1;
    int v2;
    int value;
};

struct graph {
    Vertex vertices[];
    Edge edges[];
    int n_vertices, n_edges;
};





/*
 *
 *    GRAFO - LISTA DE ADJACENCIA
 *
 */


//Imprimir Grafo -- lista

//Imprimir vertices adjacentes (crescente) -- Lista

//Adicionar nova aresta com peso entre dois vertices -- lista

//remover aresta entre dois vertices -- lista

//imprimir transposto -- Lista

//imprimir aresta com o menor peso -- lista


/*
 *
 *    DIGRAFO - LISTA DE ADJACENCIA
 *
 */


//Imprimir Grafo -- lista

//Imprimir vertices adjacentes (crescente) -- Lista

//Adicionar nova aresta com peso entre dois vertices -- lista

//remover aresta entre dois vertices -- lista

//imprimir transposto -- Lista

//imprimir aresta com o menor peso -- lista
