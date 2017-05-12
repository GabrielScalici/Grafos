#include <stdio.h>
#include <stdlib.h>

#define TAM 100

//struct definindo os atributos de um fila
typedef struct fila_estatica{
	int vector[TAM];
	int inicio;
	int fim;
	int total;

}FILA_ESTATICA;

//Criar a fila estatica circular
FILA_ESTATICA * criar_fila(){
	FILA_ESTATICA * fila = (FILA_ESTATICA*)malloc(sizeof(FILA_ESTATICA));

	if(fila != NULL){
		fila->fim = 0;
		fila->inicio = 0;
		fila->total = 0;
	} 

	return(fila);
}

//Verifica se a fila esta cheia
int cheia(FILA_ESTATICA * fila){
	return(fila->total == TAM);
}

//Verifica se a fila esta vazia
int vazia(FILA_ESTATICA * fila){
	return(fila->total == 0);
}

int tamanho(FILA_ESTATICA * fila){
	return(fila->total);
}

//Adiciona item na fila
int entra(FILA_ESTATICA * fila, int item){
	if(!cheia(fila)){
		fila->vector[fila->fim] = item;
		fila->fim = (fila->fim + 1) % TAM;
		fila->total++;
		return(1);
	}
	return(0);
}

//Remove um elemento da fila
int sai(FILA_ESTATICA * fila, ){
	if(!vazia(fila)){
		int *ret = fila->vector[fila->inicio];
		fila->inicio = (fila->inicio + 1) % TAM;
		fila->total--;
		return(ret);
	}
	return(NULL);
}
