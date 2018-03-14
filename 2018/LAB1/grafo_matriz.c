#include <stdio.h>
#include <stdlib.h>

//Usando Matriz de adjacencia
struct grafo_didrafo_matriz {
	int **matriz;
	int vertices;
	int arestas;
} typedef GRAFO_M;


/*
 *
 *    GRAFO - MATRIZ DE ADJACENCIA
 *
 */

//Criar grafo_didrafo_matriz
GRAFO_M* criar_grafo_matriz(int vertices, int arestas){
  int i = 0, j = 0;

  if(vertices > 0 || arestas > 0){
    GRAFO_M *d = (GRAFO_M*)malloc(sizeof(GRAFO_M));

    d->vertices = vertices;
    d->arestas = arestas;

    //Criando a matriz e atribuindo -1 para cada posicao
    d->matriz = (int**)malloc(sizeof(int*)*vertices);
    for(i = 0 ;i < vertices; i++){
      d->matriz[i] = (int*)malloc(sizeof(int)*vertices);
      //Atribuindo os valores iniciais
      for(j = 0; j < vertices; j++){
			     d->matriz[i][j] = -1;
		  }
    }

    return d;

  }else{
    return NULL;
  }
}

GRAFO_M* inserir_valores_digrafo(GRAFO_M *d, int v1, int v2, int peso){
  //Verificando se são valores válidos
  if(v1 > d->vertices || v2 > d->vertices){
    return NULL;
  }
  //Atribuindo na matriz
  d->matriz[v1][v2] = peso;

  return d;
}

GRAFO_M* inserir_valores_grafo(GRAFO_M *g, int v1, int v2, int peso){
  //Verificando se são valores válidos
  if(v1 > g->vertices || v2 > g->vertices){
    return NULL;
  }
  //Atribuindo na matriz
  g->matriz[v1][v2] = peso;
  g->matriz[v2][v1] = peso;
  return g;
}

//Imprimir Grafo -- matriz
void imprimir_matriz(GRAFO_M *g){
	int i, j;

	for(i=0;i<g->vertices;i++){
		for(j=0;j<g->vertices;j++){
			if(g->matriz[i][j] == -1) printf(". ");
			else{
				printf("%d ", g->matriz[i][j]);
			}
		}
		printf("\n");
	}
}

//Imprimir vertices adjacentes (crescente) -- matriz

//Adicionar nova aresta com peso entre dois vertices -- matriz

//remover aresta entre dois vertices -- matriz

//imprimir transposto -- matriz

//imprimir aresta com o menor peso -- matriz



/*
 *
 *    DIGRAFO - MATRIZ DE ADJACENCIA
 *
 */


//Criar grafo_didrafo_matriz

//Imprimir Grafo -- matriz

//Imprimir vertices adjacentes (crescente) -- matriz

//Adicionar nova aresta com peso entre dois vertices -- matriz

//remover aresta entre dois vertices -- matriz

//imprimir transposto -- matriz

//imprimir aresta com o menor peso -- matriz
