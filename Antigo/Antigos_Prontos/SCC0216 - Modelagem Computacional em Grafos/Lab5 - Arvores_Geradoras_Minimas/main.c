#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo_g_l.h"

void grafo_g_l(int V, int A){
	GRAFO_G_L *grafo = criar_grafo_g_l(V, A);
	
	MST_grafo_g_l(grafo);
	
	return;
}


int main(){
	int V, A;
	scanf("%d %d", &V, &A);

	grafo_g_l(V, A);

	return 0;
}
