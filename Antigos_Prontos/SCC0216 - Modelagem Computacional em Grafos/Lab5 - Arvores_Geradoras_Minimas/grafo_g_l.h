#ifndef _GRAFO_G_L_
#define _GRAFO_G_L_

#include "definicoes_grafo_g_l.h"

GRAFO_G_L *criar_grafo_g_l(int V, int A);
void apagar_grafo_g_l(GRAFO_G_L **grafo);
void imprimir_grafo_g_l(GRAFO_G_L *grafo);
void vertices_adjacentes_grafo_g_l(GRAFO_G_L *grafo, int x);
void adicionar_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2, int PESO);
void remover_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2);
void menor_peso_grafo_g_l(GRAFO_G_L *grafo);
void MST_grafo_g_l(GRAFO_G_L *grafo);

#endif /*_GRAFO_G_L_*/
