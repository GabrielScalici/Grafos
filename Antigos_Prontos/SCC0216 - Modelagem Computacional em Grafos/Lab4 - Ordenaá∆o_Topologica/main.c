#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo_d_l.h"

void grafo_d_l(int V, int A){
	GRAFO_D_L *grafo = criar_grafo_d_l(V, A);
	
	dsf_grafo_d_l(grafo);
	return;
}


int main(){
	int V, A;
	scanf("%d %d", &V, &A);

	grafo_d_l(V, A);

	return 0;
}
