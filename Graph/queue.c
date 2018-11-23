#include "graph.h"

QUEUE* create_queue(){
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	if(!queue) return NULL;
	else{
		queue->front = NULL;
		queue->rear = NULL;
		queue->count = 0;
		return queue;
	}
}

bool
enqueue(
	QUEUE* queue, // target queue
	void* in      // data
) {
	QUEUE_NODE* new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if(!new_node) return false;

	new_node->data_ptr = in;
	new_node->next = NULL;

	if(queue->count == 0){
		queue->front = new_node;
	}
	else{
		queue->rear->next = new_node;
	}

	queue->rear = new_node;
	queue->count++;
	
	return true;	
}

void*
dequeue(
	QUEUE* queue
) {
	if(queue->count == 0) return false;
	void* data_out = queue->front->data_ptr;
	QUEUE_NODE* temp = queue->front;
	if(queue->count == 1) {
		queue->rear = NULL;
		queue->front = NULL;
	} else{
		queue->front = queue->front->next;
	}
	free(temp);
	queue->count--;
	return data_out;
}
