#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	void* data_ptr;
	struct node* next;
} STACK_NODE;

typedef struct {
	int count;
	STACK_NODE* top;
} STACK;

STACK* create_stack();
bool push(STACK* stack, void* in);
void* pop(STACK* stack);
