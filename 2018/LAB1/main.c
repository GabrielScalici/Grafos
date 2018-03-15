#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "list.h"

//Usar a forma de armazenando matriz
void graph_matrix(int num_vertices, int num_arestas, char type, char* operacao){
	GRAPH_M *g = create_Graph_M(num_vertices);
	g = fill_Graph_M(g, num_arestas, type);
	getchar();
	while(scanf("%s", operacao) != EOF){
		//Imprimir grafo
		if(strcmp(operacao, "IG") == 0){
			print_Graph_M(g);
		}
		//Imprimir Adj
		if(strcmp(operacao, "VA") == 0){
			print_AdjVertex_M(g);
		}
		//Imprimir Aresta
		if(strcmp(operacao, "AA") == 0){
			g = add_Edge_M(g, type);
		}
		//Remover Aresta
		if(strcmp(operacao, "RA") == 0){
			g = remove_Edge_M(g, type);
		}
		//Imprimir Transposto
		if(strcmp(operacao, "IT") == 0){
			print_TransGraph_M(g, type);
		}
		//Imprimir mais leve
		if(strcmp(operacao, "MP") == 0){
			print_LighterEdge_M(g);
		}
	}
	free_Graph_M(g);
}

//Usar a forma de armazenamento lista de adj
//OBS: Exatamente igual o funcionamento da funcao para matrix,
//     com a diferença do _l no lugar _m nas funcoes
void graph_list(int num_vertices, int num_arestas, char type, char* operacao){
	GRAPH_L *g = create_Graph_L(num_vertices);
	g = fill_Graph_L(g, num_arestas, type);
	getchar();
	while(scanf("%s", operacao) != EOF){
		if(strcmp(operacao, "IG") == 0){
			print_Graph_L(g);
		}
		if(strcmp(operacao, "VA") == 0){
			print_AdjVertex_L(g);
		}
		if(strcmp(operacao, "AA") == 0){
			g = add_Edge_L(g, type);
		}
		if(strcmp(operacao, "RA") == 0){
			g = remove_Edge_L(g, type);
		}
		if(strcmp(operacao, "IT") == 0){
			print_TransGraph_L(g, type);
		}
		if(strcmp(operacao, "MP") == 0){
			print_LighterEdge_L(g);
		}
	}
	free_Graph_L(g);
}

int main (int argc, char *argv[]){
	char operacao[2];
	char type, TAD;
	int num_vertices, num_arestas;
	GRAPH_L *g;

	//Pegando os valores do tipo de grafo
	scanf("%c %c", &type, &TAD);
	getchar();

	scanf("%d %d", &num_vertices, &num_arestas);

	//USANDO MATRIZ DE AJD
	if(TAD == 'M'){
		graph_matrix(num_vertices, num_arestas, type, operacao);
		//USANDO LISTA DE ADJ
	} else{
		graph_list(num_vertices, num_arestas, type, operacao);
	}

	return 0;
}
