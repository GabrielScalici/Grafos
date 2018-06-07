#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "heap.h"

int main (int argc, char *argv[]){
	char type;
	int num_verdex, num_edges;

	type = 'D';

	scanf("%d %d", &num_verdex, &num_edges);

	GRAPH_M *graph = create_Graph_M(num_verdex);
	graph = fill_Graph_M(graph, num_edges, type);
	int a, b;

	while(scanf("%d", &a) != EOF){
		scanf("%d", &b);
		dijkstra(graph, a, b);
	}

	/* Liberação de Memória */
	free_Graph_M(graph);

	return 0;
}
