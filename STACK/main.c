#include "stack.h"

int main(){
	int a=5, b=10, c= 12;

	STACK* s1 = create_stack();

	push(s1, &a);
	push(s1, &b);
	push(s1, &c);

	int* temp = (int*)pop(s1);
	printf("s1's data: %d\n", *temp);
	temp = (int*)pop(s1);
	printf("s1's data: %d\n", *temp);
	temp = (int*)pop(s1);
	printf("s1's data: %d\n", *temp);

	return 0;
}
