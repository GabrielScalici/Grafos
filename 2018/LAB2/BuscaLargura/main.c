#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "fila.h"

int main (int argc, char *argv[]){
	char type = 'D';
	int num_verdex, num_edges;
	GRAPH_L *graph = NULL;

	int a, b;

	scanf("%d %d", &num_verdex, &num_edges);

	/* TAD Lista */
	graph = create_Graph_L(num_verdex);
	graph = fill_Graph_L(graph, num_edges, type);

	// Busca de caminhos
	while(scanf("%d", &a) != EOF && scanf("%d", &b) != EOF){
		BFS(graph, a, b);
	}

	/* Liberação de Memória */
	free_Graph_L(graph);

	return 0;
}
