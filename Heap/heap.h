#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int last;
	int size;
	int* array;
	int max_size;
} HEAP;

HEAP* create_heap(int max);
bool reheapUp (HEAP* heap, int newNode);	// newNode is index
bool reheapDown (HEAP* heap, int root);		// root is index
bool insertHeap (HEAP* heap, int data);
bool deleteHeap (HEAP* heap, int root);		// root is index
