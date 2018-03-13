#ifndef _DEFINICOES_GRAFO_D_L_H_
#define _DEFINICOES_GRAFO_D_L_H_

typedef struct cell {  //define cada celula das listas de vertices;
	int V;  //vertice ao qual o vertice cabeça da lista esta ligado;
	int PESO;
	struct cell *prox;	//ponteiro para a proxima celula, se esta for a ultima, o ponteiro recebe valor nulo;
} CELL;

typedef struct vert { //define a cabeça de cada lista, ou seja, cada vertice do grafo;
	CELL *lista_fim;  //ponteiro para o ultimo elemento da lista de vertices;
	CELL *lista_inicio;  //ponteiro para o prieiro elemento da lista de vertices;
} VERT;

typedef struct grafo_d_l {
	VERT *vertices;	 //ponteiro para o vetor de vertices;
	int num_vertices;  //numero de vertices do grafo;
	int num_arestas;  //numero de arestas do grafo;
} GRAFO_D_L;

void inserir_celula_d_l(GRAFO_D_L *grafo, int Vi, int Vj, int PESO);
void remover_celula_d_l(GRAFO_D_L *grafo, int Vi, int Vj);

#endif /*_DEFINICOES_GRAFO_D_L_H_*/
