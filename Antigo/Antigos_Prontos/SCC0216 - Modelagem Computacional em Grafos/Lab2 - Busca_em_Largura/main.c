#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo_d_l.h"

void grafo_d_l(int V, int A){
	GRAFO_D_L *grafo = criar_grafo_d_l(V, A);
	int V1, V2;


	while(scanf("%d %d", &V1, &V2) != EOF){
		bsf_grafo_d_l(grafo, V1, V2);
	}
}


int main(){
	int V, A;
	scanf("%d %d", &V, &A);

	grafo_d_l(V, A);

	return 0;
}
