#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grafo_g_l.h"

#define menor(a, b) ((a < b) ? a : b)  //macro que retorna o menor de dois inteiros;
#define maior(a, b) ((a > b) ? a : b)  //macro que retorna o maior de dois inteiros;

typedef struct cell {  //define cada celula das listas de vertices;
	int V;  //vertice ao qual o vertice cabeça da lista esta ligado;
	int PESO;  //peso da aresta;
	struct cell *prox;  //ponteiro para a proxima celula, se esta for a ultima, o ponteiro recebe valor nulo;
} CELL;

typedef struct vert {  //define a cabeça de cada lista, ou seja, cada vertice do grafo;
	CELL *lista_fim;  //ponteiro para o ultimo elemento da lista de vertices;
	CELL *lista_inicio;  //ponteiro para o prieiro elemento da lista de vertices;
} VERT;

struct grafo_g_l {
	VERT *vertices;  //ponteiro para o vetor de vertices;
	int num_vertices;  //numero de vertices do grafo;
	int num_arestas;  //numero de arestas do grafo;
};

void inserir_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj, int PESO){  //função genérica que adciona uma celula a lista cuja cabeça é o vertice Vi, colocando a em ordem crescente de acordo com o vertice(V);
		CELL *nova_celula = (CELL*)malloc(sizeof(CELL));
		nova_celula->V = Vj;
		nova_celula->PESO = PESO;
		nova_celula->prox = NULL;
		CELL *paux = grafo->vertices[Vi].lista_inicio;  //ponteiro que aponta para o proximo elemento ao que deverá ser inserido;
		CELL *pant = nova_celula;  //ponteiro que aponta para o elemento anterior ao que será inserido;

		if(grafo->vertices[Vi].lista_inicio == NULL){
			grafo->vertices[Vi].lista_inicio = nova_celula;
			grafo->vertices[Vi].lista_fim = nova_celula;
		}else{
			while(paux != NULL && paux->V < Vj){  //laço que percorre com 'paux' e 'pant' a lista até a posição de inserção da nova célula;
				pant = paux;
				paux = paux->prox;
			}

			//os ponteiros 'prox' de cada celula são trocados para inserir a nova célula a lista;

			if(pant == nova_celula)
				grafo->vertices[Vi].lista_inicio = nova_celula;

			pant->prox = nova_celula;
			nova_celula->prox = paux;

			if(paux == NULL)
				grafo->vertices[Vi].lista_fim = nova_celula;
		}
}

void remover_celula_g_l(GRAFO_G_L *grafo, int Vi, int Vj){  //função genérica que remove uma celula qualquer da lista cuja a cabeça é o vertice Vi;
	CELL *prem = grafo->vertices[Vi].lista_inicio;  //ponteiro que aponta para o elemento a ser removido;
  	CELL *pant = NULL;  //ponteiro que aponta para o elemento anterior ao elemento que deve ser removido;

	while(prem != NULL && prem->V != Vj) {  //percorre a lista até achar a célula a ser removida;
  	 	pant = prem;
   		prem = prem->prox;
    }

    //as trocas dos poneiros 'prox' são devidamente realizadas;
  
  	if(prem != NULL) {
    	if(prem == grafo->vertices[Vi].lista_inicio) {
      		grafo->vertices[Vi].lista_inicio = prem->prox;
    	} else {
     	 	pant->prox = prem->prox;
    	} 

    if(prem == grafo->vertices[Vi].lista_fim) {
      grafo->vertices[Vi].lista_fim = pant;
    }

    free(prem);
  	}  
 }

GRAFO_G_L *criar_grafo_g_l(int V, int A){  //cria o grafo vazio, ou seja, com inicio e fim das listas iguais a nulo;

	if (V<=0 || A<=0) return NULL;

	GRAFO_G_L *grafo = (GRAFO_G_L*)malloc(sizeof(GRAFO_G_L));

	if (grafo == NULL) return NULL;

	grafo->num_vertices = V;
	grafo->num_arestas = A;

	grafo->vertices = (VERT*)malloc(sizeof(VERT)*(grafo->num_vertices)); 

	if(grafo->vertices == NULL) return NULL;

	int i, V1, V2, PESO;

	for(i=0;i<grafo->num_vertices;i++){  
		grafo->vertices[i].lista_inicio = NULL;
		grafo->vertices[i].lista_fim = NULL;
	}

	for(i=0;i<grafo->num_arestas;i++){  //laço que adiciona as arestas representadas nas entradas do usuário;
		scanf("%d %d %d", &V1, &V2, &PESO);
		if(V1 == V2)
			inserir_celula_g_l(grafo, V1, V2, PESO);
		else{ //adiciona a aresta nos dois sentidos, já que o grafo não é dígrafo;
			inserir_celula_g_l(grafo, V1, V2, PESO);
			inserir_celula_g_l(grafo, V2, V1, PESO);
		}
	}

	return grafo;
}

void apagar_grafo_g_l(GRAFO_G_L **grafo){  //função que desaloca toda a memória utilizada pelo grafo;
	int i;
	CELL *prem = NULL, *paux = NULL;

	for(i=0;i<(*grafo)->num_vertices;i++){
		paux = (*grafo)->vertices[i].lista_inicio;
		 while(paux != NULL) {
    		prem = paux;
    		paux = paux->prox;
    		free(prem);
  		}
	}

	free((*grafo)->vertices);
	free(*grafo);
	*grafo = NULL;
}

void imprimir_grafo_g_l(GRAFO_G_L *grafo){  //percorre todo o grafo imprimindo todas as arestas de acordo com a representação; 
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){
		printf("%d. ", i);
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){
			printf("%d(%d) ", paux->V, paux->PESO);
			paux = paux->prox;
		}
		printf("\n");
	}
}

void vertices_adjacentes_grafo_g_l(GRAFO_G_L *grafo, int x){  //imprime os vertices adjacentes ao vertice x, se este estiver no grafo;
	if(grafo == NULL || grafo->vertices == NULL) return;

	if (x < 0 || x >= grafo->num_vertices) return;

	CELL *paux = grafo->vertices[x].lista_inicio;

	while(paux != NULL){
			printf("%d ", paux->V);
			paux = paux->prox;
	}
	printf("\n");	
}

void adicionar_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2, int PESO){  //adiciona a aresta necessária se os requisitos forem atendidos (ambos os vertices existem, e o peso da aresta é maior ou igual a 0);
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices || PESO <= 0) return;

	if(V1 == V2)
			inserir_celula_g_l(grafo, V1, V2, PESO);
		else{ //adiciona a aresta nos dois sentidos, já que o grafo não é dígrafo;
			inserir_celula_g_l(grafo, V1, V2, PESO);
			inserir_celula_g_l(grafo, V2, V1, PESO);
		}
}

void remover_aresta_grafo_g_l(GRAFO_G_L *grafo, int V1, int V2){  //remove a aresta necessária se os requisitos forem atendidos (ambos os vertices existem, e o peso da aresta é maior ou igual a 0);
	if(grafo == NULL || grafo->vertices == NULL) return;

	if(V1 < 0 || V2 < 0 || V1 >= grafo->num_vertices || V2 >= grafo->num_vertices) return;

	//remove a aresta nos dois sentidos, já que o grafo não é dígrafo;

	remover_celula_g_l(grafo, V1, V2);
	remover_celula_g_l(grafo, V2, V1);
}

void menor_peso_grafo_g_l(GRAFO_G_L *grafo){  //imprime a aresta de menor peso do grafo;
	if(grafo == NULL || grafo->vertices == NULL) return;

	int i, V1, V2, menor_peso = INT_MAX;
	CELL *paux;

	for(i=0;i<grafo->num_vertices;i++){  //laço que percorre o vetor de vertices;
		paux = grafo->vertices[i].lista_inicio;
		while(paux != NULL){  //laço que percorre as listas de vertices de cada vertice do vertor principal;
			if(paux->PESO < menor_peso){
				menor_peso = paux->PESO;  //atualiza o menor peso até o momento;
				V1 = menor(i, paux->V);
				V2 = maior(i, paux->V);
			}
		}
	}
	printf("%d %d\n", V1, V2);
}
