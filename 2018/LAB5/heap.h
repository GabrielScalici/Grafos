#ifndef _HEAP_H_
#define _HEAP_H_

/* Struct representativa da heap */
typedef struct heap {
	int *vector;
	int *id;
	int size;
} HEAP;

/* Funções para criar a heap, preencher e liberar a memória alocada */
HEAP *initialize_heap(int);
void insert(HEAP *, int , int);
void free_heap(HEAP *);

/* Funções para manipularem a heap, usufruindo de suas funcionalidades */
void min_heapify(int *, int , int, int *);
void build_min_heap(HEAP *);
int heap_extract_min(HEAP *);
int empty_heap(HEAP *heap);

#endif
