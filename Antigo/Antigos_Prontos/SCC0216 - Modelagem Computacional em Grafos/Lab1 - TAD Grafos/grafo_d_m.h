#ifndef _GRAFO_D_M_H_
#define _GRAFO_D_M_H_

typedef struct grafo_d_m GRAFO_D_M;

GRAFO_D_M *criar_grafo_d_m(int V, int A);
void apagar_grafo_d_m(GRAFO_D_M **grafo);
void imprimir_grafo_d_m(GRAFO_D_M *grafo);
void vertices_adjacentes_grafo_d_m(GRAFO_D_M *grafo, int x);
void adicionar_aresta_grafo_d_m(GRAFO_D_M *grafo, int V1, int V2, int PESO);
void remover_aresta_grafo_d_m(GRAFO_D_M *grafo, int V1, int V2);
void menor_peso_grafo_d_m(GRAFO_D_M *grafo);
void imprimir_transposto_grafo_d_m(GRAFO_D_M *grafo);

#endif /*_GRAFO_D_M_H_*/
