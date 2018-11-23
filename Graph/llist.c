#include "graph.h"

LLIST* create_list(){
	LLIST* list = (LLIST*)malloc(sizeof(LLIST));
	if(!list) return NULL;

	list->count = 0;
	list->front = NULL;
	list->rear= NULL;
	list->pos= NULL;

	return list;
}

bool add_node_at(LLIST* list, unsigned int index, void* data){
	if(list->count < index){
		printf("input index small than list's count\n");
		return false;
	}
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if(!new_node) return false;

	new_node->data_ptr = data;
	new_node->next = NULL;

	if(list->count == 0){
		list->front = new_node;
		list->rear = new_node;
		printf("add_node at %d\n", index);
		list->count++;
		printf("list's size: %d\n", list->count);
		return true;
	}
	if(index == 0){
		new_node->next = list->front;
		list->front = new_node;
		printf("add_node at %d\n", index);
		list->count++;
		printf("list's size: %d\n", list->count);
		return true;
	} 
	
	int iter=1;
	list->pos = list->front;
	while( index != iter ){
		list->pos = list->pos->next;
		iter++;
	}
	if(iter == list->count){
		list->pos->next = new_node;
		list->rear = new_node;
		printf("add_node at %d\n", index);
		list->count++;
		printf("list's size: %d\n", list->count);
		return true;
	} 
	new_node->next = list->pos->next;
	list->pos->next = new_node;
	list->pos = NULL;
		
	printf("add_node at %d\n", index);
	list->count++;
	printf("list's size: %d\n", list->count);
	return true;
}

bool add_vertex_at(V_LIST* list, unsigned int index, VERTEX* new_node){
	if(list->count < index){
		printf("input index small than list's count\n");
		return false;
	}

	if(list->count == 0){
		list->front = new_node;
		list->rear = new_node;
		list->count++;
		return true;
	}
	if(index == 0){
		new_node->next = list->front;
		list->front = new_node;
		list->count++;
		return true;
	} 
	
	int iter=1;
	list->pos = list->front;
	while( index != iter ){
		list->pos = list->pos->next;
		iter++;
	}
	if(iter == list->count){
		list->pos->next = new_node;
		list->rear = new_node;
		list->count++;
		return true;
	} 
	new_node->next = list->pos->next;
	list->pos->next = new_node;
	list->pos = NULL;
		
	list->count++;
	return true;
}

bool add_arc_at(A_LIST* list, unsigned int index, ARC* new_node){
	if(list->count < index){
		printf("input index small than list's count\n");
		return false;
	}

	if(list->count == 0){
		list->front = new_node;
		list->rear = new_node;
		list->count++;
		return true;
	}
	if(index == 0){
		new_node->next = list->front;
		list->front = new_node;
		list->count++;
		return true;
	} 
	
	int iter=1;
	list->pos = list->front;
	while( index != iter ){
		list->pos = list->pos->next;
		iter++;
	}
	if(iter == list->count){
		list->pos->next = new_node;
		list->rear = new_node;
		list->count++;
		return true;
	} 
	new_node->next = list->pos->next;
	list->pos->next = new_node;
	list->pos = NULL;
		
	list->count++;
	return true;
}

bool del_node_at(LLIST* list, unsigned int index) {
	if(list->count == 0) return false;
	if(list->count-1 < index){
		printf("input index small than (list's count-1)\n");
		return false;
	}
	if(index == 0){
		if(list->count == 1) {
			free(list->front);
			list->front = NULL;
			list->rear = NULL;
		} else {
		list->pos = list->front;
		list->front = list->front->next;
		free(list->pos);
		list->pos = NULL;
		}
	} else{
		NODE* pre;
		list->pos = list->front;
		int iter=0;
		while(iter != index){
			pre = list->pos;
			list->pos = list->pos->next;
			iter++;
		}
		if(iter == list->count-1){
			list->rear = pre;
			list->rear->next = NULL;
			free(list->pos);
			list->pos = NULL;
		} else{
			pre->next = list->pos->next;
			free(list->pos);
			list->pos = NULL;
		}
	}	
	printf("del_node at %d\n", index);
	list->count--;
	printf("list's size: %d\n", list->count);
	return true;
}

bool del_vertex_at(V_LIST* list, char data) {
	if(list->count == 0) return false;
	if(list->front->data == data){
		if(list->count == 1) {
			free(list->front);
			list->front = NULL;
			list->rear = NULL;
		} else {
		list->pos = list->front;
		list->front = list->front->next;
		free(list->pos);
		list->pos = NULL;
		}
	} else{
		VERTEX* pre;
		list->pos = list->front;
		while(list->pos->data != data){
			pre = list->pos;
			list->pos = list->pos->next;
		}
		if(list->rear->data == data){
			list->rear = pre;
			list->rear->next = NULL;
			free(list->pos);
			list->pos = NULL;
		} else{
			pre->next = list->pos->next;
			free(list->pos);
			list->pos = NULL;
		}
	}	
	list->count--;
	return true;
}

bool del_arc_at(A_LIST* list, char data) {
	if(list->count == 0) return false;

	if(list->front->destination->data == data){
		if(list->count == 1) {
			free(list->front);
			list->front->destination = NULL;
			list->front->next = NULL;
			list->front = NULL;
			list->rear = NULL;
		} else {
		list->pos = list->front;
		list->front = list->front->next;
		free(list->pos);
		list->pos->destination = NULL;
		list->pos->next = NULL;
		list->pos = NULL;
		}
	} else{
		ARC* pre;
		list->pos = list->front;
		while(list->pos->destination->data != data){
			pre = list->pos;
			list->pos = list->pos->next;
		}
		if(list->rear->destination->data == data){
			list->rear = pre;
			list->rear->next = NULL;
			free(list->pos);
			list->pos->destination = NULL;
			list->pos->next = NULL;
			list->pos = NULL;
		} else{
			pre->next = list->pos->next;
			free(list->pos);
			list->pos->destination = NULL;
			list->pos->next = NULL;
			list->pos = NULL;
		}
	}	
	list->count--;
	return true;
}

void* read_node_at(LLIST* list, unsigned int index) {
	if(list->count-1 < index) return false;
	void* data_out;
	if(index == 0){
		data_out = list->front->data_ptr;
	} else{
		int i;
		list->pos = list->front;
		for(i=0; i<index; i++){
			list->pos = list->pos->next;
		}
		data_out = list->pos->data_ptr;
		list->pos = NULL;
	}
	printf("read at index %d\n", index);
	return data_out;
}
