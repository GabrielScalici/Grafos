#ifndef _DEFINICOES_GRAFO_G_L_H_
#define _DEFINICOES_GRAFO_G_L_H_

typedef struct cell {
	int V;
	int PESO;
	struct cell *prox;
} CELL;

typedef struct vert {
	CELL *lista_fim;
	CELL *lista_inicio;
	int conjunto;
} VERT;

typedef struct aresta {
	int V1;
	int V2;
	int PESO;
}ARESTA;

typedef struct grafo_g_l {
	VERT *vertices;
	ARESTA **arestas;
	int num_vertices;
	int num_arestas;
	int soma_pesos;
}GRAFO_G_L;

void inserir_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj, int PESO);

void remover_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj);

#endif /*_DEFINICOES_GRAFO_G_L_H_*/