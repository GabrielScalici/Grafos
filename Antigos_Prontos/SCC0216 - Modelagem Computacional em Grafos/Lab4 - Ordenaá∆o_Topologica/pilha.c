#include "definicoes.h"
#include "pilha.h"
#include <stdlib.h>

typedef struct no{
    int V;
    struct no *prox;
} NO;

struct pilha{
    NO *inicio;
};

PILHA *criar_pilha(){
    PILHA *pilha = (PILHA*)malloc(sizeof(PILHA));

    if(pilha==NULL) return NULL;

    pilha->inicio = NULL;
}

void apagar_pilha(PILHA **pilha){
    NO *paux = (*pilha)->inicio;
    NO *prem = NULL;

    while(paux != NULL) {
        prem = paux;
        paux = paux->prox;
        free(prem);
    }

    free(*pilha);
    *pilha == NULL;
}

int vazia_pilha(PILHA *pilha){
    return(pilha->inicio == NULL);
}

void empilhar(PILHA *pilha, int V){
    NO *paux = pilha->inicio;
    NO *novo = (NO*)malloc(sizeof(NO));

    novo->V = V;
    novo->prox = NULL;

    if(novo == NULL) return;

    if(pilha->inicio == NULL){
        pilha->inicio = novo;
    }

    else{
        while(paux->prox != NULL){
            paux = paux->prox;
        }

        paux->prox = novo;
    }
}
int desempilhar(PILHA *pilha){
    NO *prem = pilha->inicio;
    NO *ant = NULL;
    int ret;

    while(prem->prox != NULL){
        ant = prem;
        prem = prem->prox;
    }

    if(prem == pilha->inicio)
        pilha->inicio = NULL;

    else
        ant->prox = NULL;

    ret = prem->V;

    free(prem);

    return ret;
}
