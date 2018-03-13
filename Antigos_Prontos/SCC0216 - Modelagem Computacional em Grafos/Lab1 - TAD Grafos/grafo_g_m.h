#ifndef _GRAFO_G_M_H_
#define _GRAFO_G_M_H_

typedef struct grafo_g_m GRAFO_G_M;

GRAFO_G_M *criar_grafo_g_m(int V, int A);
void apagar_grafo_g_m(GRAFO_G_M **grafo);
void imprimir_grafo_g_m(GRAFO_G_M *grafo);
void vertices_adjacentes_grafo_g_m(GRAFO_G_M *grafo, int x);
void adicionar_aresta_grafo_g_m(GRAFO_G_M *grafo, int V1, int V2, int PESO);
void remover_aresta_grafo_g_m(GRAFO_G_M *grafo, int V1, int V2);
void menor_peso_grafo_g_m(GRAFO_G_M *grafo);


#endif /*_GRAFO_G_M_H_*/
