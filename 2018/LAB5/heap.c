#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define TOP 0
#define get_parent(id) (id-1)/2
#define get_left_child(id) (id*2)+1
#define get_right_child(id) (id*2)+2

/*
 Função para inicializar a heap com n posições
*/
HEAP *initialize_heap(int n) {
	HEAP *heap = NULL;

	heap = (HEAP *) malloc(sizeof(HEAP));

	if(heap != NULL){
		heap->vector = (int *) malloc(sizeof(int)*n); // Vetor principal
		heap->id = (int *) malloc(sizeof(int)*n); // Vetor auxiliar
		heap->size = 0;
	}
	return heap;
}

/*
 Função para ordenar a heap
*/
void min_heapify(int *vector, int n, int index, int *id) {
	int left_id = get_left_child(index);
	int right_id = get_right_child(index);
	int minimum_id = index;
	int aux;

	if (left_id < n && vector[left_id] < vector[minimum_id])
		minimum_id = left_id;
	if (right_id < n && vector[right_id] < vector[minimum_id])
		minimum_id = right_id;

	if (minimum_id != index) {
		aux = vector[index];
		vector[index] = vector[minimum_id];
		vector[minimum_id] = aux;

		aux = id[index];
		id[index] = id[minimum_id];
		id[minimum_id] = aux;

		min_heapify(vector, n, minimum_id, id);
	}
}

/*
 Função para possibilitar a construção da heap de maneira completa
*/
void build_min_heap(HEAP *heap) {
	int index;

	for (index = get_parent(heap->size-1); index >= 0; index--) {
		min_heapify(heap->vector, heap->size, index, heap->id);
	}
}

/*
 Função para inserir um valor na heap
*/
void insert(HEAP *heap, int key, int id) {
	int i = 0;
	for(i = 0; i < heap->size; i++){
		if(heap->id[i] == id){
			heap->vector[i] = key;
			return;
		}
	}
	heap->vector[heap->size] = key;
	heap->id[heap->size++] = id;
}

/*
 Função para verificar se a heap está vazia
*/
int empty_heap(HEAP *heap) {
	return (heap->size == 0);
}

/*
 Função para extrair o menor valor da heap
*/
int heap_extract_min(HEAP *heap) {
	int min;

	if(heap->size < 1) {
		printf("Erro: heap underflow\n");
		return -1;
	}

	min = heap->id[0];
	heap->vector[0] = heap->vector[heap->size-1];
	heap->id[0] = heap->id[heap->size-1];
	min_heapify(heap->vector, 0, (heap->size--)-1, heap->id);
	build_min_heap(heap);

	return min;
}

/*
 Função para liberar a heap
*/
void free_heap(HEAP *heap) {
	free(heap->vector);
	free(heap->id);
	free(heap);
}
