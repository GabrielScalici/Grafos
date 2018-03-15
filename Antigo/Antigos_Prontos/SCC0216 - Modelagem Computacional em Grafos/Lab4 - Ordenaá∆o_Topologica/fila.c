#include "definicoes.h"
#include "fila.h"
#include <stdlib.h>

typedef struct no{
    int V;
    struct no *prox;
} NO;

struct fila{
    NO *inicio;
};

FILA *criar_fila(){
    FILA *fila = (FILA*)malloc(sizeof(fila));

    if(fila==NULL) return NULL;

    fila->inicio = NULL;
}

void apagar_fila(FILA **fila){
    NO *paux = (*fila)->inicio;
    NO *prem = NULL;

    while(paux != NULL) {
        prem = paux;
        paux = paux->prox;
        free(prem);
    }

    free(*fila);
    *fila == NULL;
}

int vazia_fila(FILA *fila){
    return(fila->inicio == NULL);
}

void enfileirar(FILA *fila, int V){
    NO *paux = fila->inicio;
    NO *novo = (NO*)malloc(sizeof(NO));

    novo->V = V;
    novo->prox = NULL;

    if(novo == NULL) return;

    if(fila->inicio == NULL){
        fila->inicio = novo;
    }

    else{
        while(paux->prox != NULL){
            paux = paux->prox;
        }

        paux->prox = novo;
    }
}
int desenfileirar(FILA *fila){
    NO *prem = fila->inicio;
    int ret;

    fila->inicio = prem->prox;

    prem->prox = NULL;
    ret = prem->V;

    free(prem);

    return ret;
}
