#include "list.h"					// linked_list는 queue에서 순서(index)만 넣어주면 됌

LLIST* create_list(){
	LLIST* list = (LLIST*)malloc(sizeof(LLIST));
	if(!list) return false;

	list->count = 0;
	list->front = NULL;
	list->rear  = NULL;
	list->pos	  = NULL;

	return list;
}

bool add_node_at(LLIST* list, unsigned int index, void* in){			// index맞춰서 삽입
	if(list->count < index) return false;

	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if(!new_node) return false;

	new_node->data_ptr = in;
	new_node->next = NULL;

	if(list->count == 0){
		list->front = new_node;
		list->rear  = new_node;
		list->count++;
		return true;
	}
	if(index == 0){
		new_node->next = list->front;
		list->front = new_node;
		list->count++;
		return true;
	}else if(index == list->count){
		list->rear->next = new_node;
		list->rear = new_node;
		list->count++;
		return true;
	}else{
		list->pos = list->front;
		int iter=1;
		while(iter != index){
			list->pos = list->pos->next;
			iter++;
		}
		new_node->next = list->pos->next;
		list->pos->next = new_node;
		list->count++;
		return true;
	}
}

bool del_node_at(LLIST* list, unsigned int index){			// index맞춰서 삭제
	if(list->count == 0) return false;
	if(list->count-1 < index) return false;

	NODE* temp;

	if(list->count == 1){
		free(list->front);
		list->front = NULL;
		list->rear  = NULL;
		list->count--;
		return true;
	}
	if(index == 0){
		temp = list->front;
		list->front = list->front->next;
		free(temp);
		list->count--;
		return true;
	}

	NODE* pre = list->front;			// index 찾기위해 출발
	list->pos = list->front->next;
	int iter = 1;
	while(iter != index){
		pre = list->pos;
		list->pos = list->pos->next;
		iter++;
	}
	if(iter == list->count-1){
		temp = list->pos;
		list->rear = pre;
		free(temp);
		list->pos = NULL;
		list->count--;
		return true;
	}else{
		temp = list->pos;
		pre->next = list->pos->next;
		free(temp);
		list->pos = NULL;
		list->count--;
		return true;
	}

}

void* read_node_at(LLIST* list, unsigned int index){			// index에 해당하는 data 읽기
	if(list->count == 0) return false;
	if(index > list->count-1) return false;

	void* data_out;

	if(index == 0){
		data_out = list->front->data_ptr;
		return data_out;
	}else if(index == list->count-1){
		data_out = list->rear->data_ptr;
		return data_out;
	}else{
		list->pos = list->front;
		int iter=0;
		while(iter != index){
			list->pos = list->pos->next;
			iter++;
		}
		data_out = list->pos->data_ptr;
		return data_out;
	}
}
