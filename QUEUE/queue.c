#include "queue.h"

QUEUE* create_queue(){
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	if(!queue) return false;

	queue->count = 0;			// 스택과 다르게 한쪽에서 데이터 삽입하고, 한쪽에서 나오는 구조
	queue->front = NULL;
	queue->rear  = NULL;

	return queue;
}

bool enqueue(QUEUE* queue, void* in){				// 데이터 삽입 
	QUEUE_NODE* new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if(!new_node) return false;

	new_node->data_ptr = in;
	new_node->next = NULL;

	if(queue->count == 0){
		queue->front= new_node;
		queue->rear = new_node;
		queue->count++;
		return true;
	} else { 
		queue->rear->next = new_node;
		queue->rear = new_node;
		queue->count++;
		return true;
	}
}

void* dequeue(QUEUE* queue){				// 데이터 
	if(queue->count == 0) return false;

	QUEUE_NODE* temp = queue->front;
	void* data_out = queue->front->data_ptr;

	if(queue->count == 1){	
		free(temp);
		queue->front = NULL;
		queue->rear  = NULL;
		queue->count--;
		return data_out;
	}else{
		queue->front = queue->front->next;
		free(temp);
		queue->count--;
		return data_out;
	}
}
