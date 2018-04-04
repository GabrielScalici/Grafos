#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "fila.h"

#define TAM 100

typedef struct fila{
	NODE *vector[TAM];
	int inicio;
	int fim;
}FILA;

FILA *criar_fila(){
	FILA *fila = malloc(sizeof(FILA));

	if(fila != NULL){
		fila->inicio = 0;
		fila->fim = 0;
		return fila;
	}

	return NULL;
}

int enfileirar(FILA *fila, NODE *item){
	if(!cheia(fila) && fila != NULL && item != NULL){
		int i;
		for(i = 0; i < TAM; i++){
			if(fila->vector[i] != NULL){
				if(fila->vector[i]->id == item->id) return 0;
			}
		}
		fila->vector[fila->fim] = item;
		fila->fim = (fila->fim + 1) % TAM;
		return 1;
	}
	return 0;
}

NODE *desenfileirar(FILA *fila){
	if(!vazia(fila) && fila != NULL){
		NODE *prem = fila->vector[fila->inicio];
		fila->inicio = (fila->inicio + 1) % TAM;
		return prem;
	}
	return NULL;
}

NODE *inicio(FILA *fila){
    if(fila != NULL){
    	return fila->vector[fila->inicio];
    } else return NULL;
}

int tamanho(FILA *fila){
	if(fila != NULL){
		if(fila->fim > fila->inicio) return fila->fim - fila->inicio;
		else return TAM - fila->inicio + fila->fim;
	}
	else return -1;
}

int cheia(FILA *fila){
	if(fila != NULL){
		return((fila->fim + 1) % TAM == fila->inicio);
	} else return 0;
}

int vazia(FILA *fila){
	if(fila != NULL){
		return (fila->inicio == fila->fim);
	} else return 1;
}

/*
void imprimir_fila(FILA *fila){
	if(!vazia(fila)){
		int i, j;
		j = fila->fim;

		for(i = fila->inicio; i != fila->fim; i = (i + 1) % TAM){
			printf("%d\n", fila->vector[i]->id);
		}
	}
}
*/
