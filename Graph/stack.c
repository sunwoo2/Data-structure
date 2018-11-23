#include "graph.h" 
	
STACK* create_stack() {
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if( !stack )
		return 0;
	stack->count = 0;	
	stack->top = 0;  
	return stack;	
}

int push(STACK* stack, void* in) {
	STACK_NODE* node = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if(!node)
		return 0;
	node->data_ptr = in;
	node->link = stack->top; // my next become old boss
	stack->top = node; // I am a new boss	
	stack->count++;

	return 1;
}

void* pop(STACK* stack) {
	STACK_NODE* temp;
	if(stack->count == 0)
		return 0;
	else{
		temp = stack->top;
		void* data_out = stack->top->data_ptr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
		return data_out;
	}	
}

