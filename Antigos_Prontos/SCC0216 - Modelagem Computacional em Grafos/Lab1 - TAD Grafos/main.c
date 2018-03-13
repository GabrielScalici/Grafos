#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo_d_m.h"
#include "grafo_g_m.h"
#include "grafo_d_l.h"
#include "grafo_g_l.h"

void grafo_d_m(int V, int A, char *comando){
	GRAFO_D_M *grafo = criar_grafo_d_m(V, A);

	while(scanf("%s ", comando) != EOF){
		if(strcmp(comando, "IG") == 0){
			imprimir_grafo_d_m(grafo);
		}else if(strcmp(comando, "VA") == 0){
			int x;
			scanf(" %d", &x);
			vertices_adjacentes_grafo_d_m(grafo, x);
		}else if(strcmp(comando, "AA") == 0){
			int V1, V2, PESO;
			scanf(" %d %d %d", &V1, &V2, &PESO);
			adicionar_aresta_grafo_d_m(grafo, V1, V2, PESO);
		}else if(strcmp(comando, "RA") == 0){
			int V1, V2;
			scanf(" %d %d", &V1, &V2);
			remover_aresta_grafo_d_m(grafo, V1, V2);
		}else if(strcmp(comando, "IT") == 0){
			imprimir_transposto_grafo_d_m(grafo);
		}else if(strcmp(comando, "MP") == 0){
			menor_peso_grafo_d_m(grafo);
		}
	}
}
void grafo_d_l(int V, int A, char *comando){
	GRAFO_D_L *grafo = criar_grafo_d_l(V, A);

	while(scanf("%s ", comando) != EOF){
		if(strcmp(comando, "IG") == 0){
			imprimir_grafo_d_l(grafo);
		}else if(strcmp(comando, "VA") == 0){
			int x;
			scanf(" %d", &x);
			vertices_adjacentes_grafo_d_l(grafo, x);
		}else if(strcmp(comando, "AA") == 0){
			int V1, V2, PESO;
			scanf(" %d %d %d", &V1, &V2, &PESO);
			adicionar_aresta_grafo_d_l(grafo, V1, V2, PESO);
		}else if(strcmp(comando, "RA") == 0){
			int V1, V2;
			scanf(" %d %d", &V1, &V2);
			remover_aresta_grafo_d_l(grafo, V1, V2);
		}else if(strcmp(comando, "IT") == 0){
			imprimir_transposto_grafo_d_l(grafo);
		}else if(strcmp(comando, "MP") == 0){
			menor_peso_grafo_d_l(grafo);
		}
	}
}
void grafo_g_m(int V, int A, char *comando){
	GRAFO_G_M *grafo = criar_grafo_g_m(V, A);

	while(scanf("%s ", comando) != EOF){
		if(strcmp(comando, "IG") == 0){
			imprimir_grafo_g_m(grafo);
		}else if(strcmp(comando, "VA") == 0){
			int x;
			scanf(" %d", &x);
			vertices_adjacentes_grafo_g_m(grafo, x);
		}else if(strcmp(comando, "AA") == 0){
			int V1, V2, PESO;
			scanf(" %d %d %d", &V1, &V2, &PESO);
			adicionar_aresta_grafo_g_m(grafo, V1, V2, PESO);
		}else if(strcmp(comando, "RA") == 0){
			int V1, V2;
			scanf(" %d %d", &V1, &V2);
			remover_aresta_grafo_g_m(grafo, V1, V2);
		}else if(strcmp(comando, "IT") == 0){
		}else if(strcmp(comando, "MP") == 0){
			menor_peso_grafo_g_m(grafo);
		}
	}
}
void grafo_g_l(int V, int A, char *comando){
	GRAFO_G_L *grafo = criar_grafo_g_l(V, A);

	while(scanf("%s ", comando) != EOF){
		if(strcmp(comando, "IG") == 0){
			imprimir_grafo_g_l(grafo);
		}else if(strcmp(comando, "VA") == 0){
			int x;
			scanf(" %d", &x);
			vertices_adjacentes_grafo_g_l(grafo, x);
		}else if(strcmp(comando, "AA") == 0){
			int V1, V2, PESO;
			scanf(" %d %d %d", &V1, &V2, &PESO);
			adicionar_aresta_grafo_g_l(grafo, V1, V2, PESO);
		}else if(strcmp(comando, "RA") == 0){
			int V1, V2;
			scanf(" %d %d", &V1, &V2);
			remover_aresta_grafo_g_l(grafo, V1, V2);
		}else if(strcmp(comando, "IT") == 0){
		}else if(strcmp(comando, "MP") == 0){
			menor_peso_grafo_g_l(grafo);
		}
	}
}

int main(){
	char tipo1, tipo2, comando[2];
	int V, A;
	scanf("%c %c %d %d", &tipo1, &tipo2, &V, &A);

	if(tipo1 == 'D'){
		if(tipo2 == 'M')
			grafo_d_m(V, A, comando);
		if(tipo2 == 'L')
			grafo_d_l(V, A, comando);
	}
	if(tipo1 == 'G'){
		if(tipo2 == 'M')
			grafo_g_m(V, A, comando);
		if(tipo2 == 'L')
			grafo_g_l(V, A, comando);
	}

	return 0;
}
