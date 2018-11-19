#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int last;			// Heap_tree의 마지막 배열(노드)의 인덱스 (배열이므로 인덱스는 0부터 시작)
	int size;			// Heap_tree의 데이터 개수
	int* array;			// Heap_tree는 다른 데이터구조들과 달리 array로 구현 하였습니다. (실질적인 tree가 아니라)
	int max_size;			// Heap의 max_size
} HEAP;

HEAP* create_heap(int max);			// Heap의 최대 데이터 개수를 인수로 받습니다.
bool reheapUp (HEAP* heap, int newNode);	// newNode is index  -> 데이터값이 아닌 배열의 인덱스를 말합니다.
bool reheapDown (HEAP* heap, int root);		// root is index
bool insertHeap (HEAP* heap, int data);		// 여기의 data는 실제 data값을 말합니다.
bool deleteHeap (HEAP* heap, int root);		// root is index
