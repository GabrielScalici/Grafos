#ifndef _FILA_H_
#define	_FILA_H_

#include "definicoes.h"

typedef struct fila FILA;

FILA *criar_fila();
void apagar_fila(FILA **fila);

void enfileirar(FILA *fila, int V);
int desenfileirar(FILA *fila);

int vazia_fila(FILA *fila);

#endif	/* _FILA_H_ */
