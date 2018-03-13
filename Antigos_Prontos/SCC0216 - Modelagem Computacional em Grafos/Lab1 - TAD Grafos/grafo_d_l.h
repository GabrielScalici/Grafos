#ifndef _GRAFO_D_L_
#define _GRAFO_D_L_

typedef struct grafo_d_l GRAFO_D_L;

GRAFO_D_L *criar_grafo_d_l(int V, int A);
void apagar_grafo_d_l(GRAFO_D_L **grafo);
void imprimir_grafo_d_l(GRAFO_D_L *grafo);
void vertices_adjacentes_grafo_d_l(GRAFO_D_L *grafo, int x);
void adicionar_aresta_grafo_d_l(GRAFO_D_L *grafo, int V1, int V2, int PESO);
void remover_aresta_grafo_d_l(GRAFO_D_L *grafo, int V1, int V2);
void menor_peso_grafo_d_l(GRAFO_D_L *grafo);
void imprimir_transposto_grafo_d_l(GRAFO_D_L *grafo);

#endif /*_GRAFO_D_L_*/
