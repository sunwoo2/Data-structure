#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	void* data_ptr;
	struct node* next;
} NODE; 

typedef struct {
	int count;
	NODE* front;
	NODE* rear;
	NODE* pos;
} LLIST;

LLIST* create_list();
bool add_node_at(LLIST* list, unsigned int index, void* in);
bool del_node_at(LLIST* list, unsigned int index);
void* read_node_at(LLIST* list, unsigned int index);
