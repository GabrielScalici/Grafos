#ifndef FILA_H_
#define FILA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct fila FILA;

FILA *criar_fila();

int enfileirar(FILA *, NODE *);
NODE *desenfileirar(FILA *);

NODE *inicio(FILA *);

int tamanho(FILA *);
int cheia(FILA *);
int vazia(FILA *);

void imprimir_fila(FILA *);

#endif
