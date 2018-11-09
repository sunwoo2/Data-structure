#include "stack.h"

STACK* create_stack(){
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if(!stack) return false;

	stack->count = 0;
	stack->top = NULL;

	return stack;
}

bool push(STACK* stack, void* in){
	STACK_NODE* new_node = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if(!new_node) return false;

	new_node->data_ptr = in;
	new_node->next = NULL;

	if(stack->count == 0){
		stack->top = new_node;
		stack->count++;
		return stack;
	} else{
		new_node->next = stack->top;
		stack->top = new_node;
		stack->count++;
		return stack;
	}
}

void* pop(STACK* stack){
	if(stack->count == 0) return false;

	STACK_NODE* temp;
	void* data_out;

	temp = stack->top;
	data_out = stack->top->data_ptr;
	stack->top = stack->top->next;
	free(temp);
	stack->count--;
	return data_out;
}
