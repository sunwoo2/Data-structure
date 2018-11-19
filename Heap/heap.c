#include "heap.h"

HEAP* create_heap(int max){
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	heap->last = -1;
	heap->size = 0;
	heap->max_size = max;
	heap->array = (int*)malloc(sizeof(int)*max);

	return heap;
}

bool reheapUp (HEAP* heap, int newNode){
	if(heap->array+newNode == heap->array) return false;
	
	int parent = (newNode-1)/2;			// check index!	  // 부모노드 찾아주기(Heap 구조 부모와 자식노드간의 관계!!!)
	if( heap->array[newNode] > heap->array[parent] ){		// 자식노드가 더 크면 swap하는 원리
		int temp;
		temp = heap->array[newNode];
		heap->array[newNode] = heap->array[parent];
		heap->array[parent] = temp;
		reheapUp(heap, parent);				// recursively!!
	}
	return true;
}

bool insertHeap (HEAP* heap, int data){
	if(heap->size == heap->max_size) return false;

	heap->last++;
	heap->array[heap->last] = data;			// Heap에서 삽입은 그냥 맨끝 빈자리에 삽입해주고, 그다음 Reheap 하는 알고리즘
	reheapUp(heap, heap->last);			// Heap구조 유지 시켜주기

	heap->size++;
	return true;
}

bool reheapDown (HEAP* heap, int root){
	int left, right, large, temp;
	left = root*2+1;			// 자식노드 두개 찾아주기
	right= root*2+2;	
	
	if(left > heap->last) return false;		// that's leafnode
	
	if(heap->array[left] > heap->array[right])		// find largeSubtree
		large = left;
	else
		large = right;
	
	if(heap->array[root] < heap->array[large]){			
		temp = heap->array[root];					// exchange root and largeSubtree
		heap->array[root] = heap->array[large];
		heap->array[large] = temp;
		reheapDown(heap, large);			// recursively!!
	}

	return true;
}

bool deleteHeap (HEAP* heap, int root){
	if(heap->size == 0) return false;		// there is no data!

	int temp;						// Replace root(lagest) with last node(small)
	temp = heap->array[heap->last];
	heap->array[heap->last] = heap->array[root];
	heap->array[root] = temp;

	heap->array[heap->last] = 0;
	heap->last--;					// delete last node
	heap->size--;

	reheapDown(heap, root);			// reheapDown

	return true;
}
