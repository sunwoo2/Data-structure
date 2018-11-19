#include "heap.h"

int main(){							// 자유롭게 Heap을 구현해 
	int i;
	HEAP* h1 = create_heap(100);

	insertHeap(h1, 8);
	insertHeap(h1, 45);
	insertHeap(h1, 23);
	insertHeap(h1, 19);
	insertHeap(h1, 67);
	insertHeap(h1, 32);
	insertHeap(h1, 78);
	insertHeap(h1, 56);
	insertHeap(h1, 84);

	deleteHeap(h1, 0);
	deleteHeap(h1, 0);


	for(i=0; i<h1->size; i++){
		printf("%d ", h1->array[i]);
	}
	printf("\n");
	printf("h1's size: %d\n", h1->size);
	printf("h1's last: %d\n", h1->last);
	printf("h1's max_size: %d\n", h1->max_size);

	return 0;
}
