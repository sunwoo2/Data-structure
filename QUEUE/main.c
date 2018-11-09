#include "queue.h"

int main(){
	int a=5, b=10, c=12;

	QUEUE* q1 = create_queue();

	if(!enqueue(q1, &a)) printf("error\n");
	if(!enqueue(q1, &b)) printf("error\n");
	if(!enqueue(q1, &c)) printf("error\n");
	
	int* temp;
	temp = (int*)dequeue(q1);
	printf("q1's data: %d\n", *temp);
	temp = (int*)dequeue(q1);
	printf("q1's data: %d\n", *temp);
	temp = (int*)dequeue(q1);
	printf("q1's data: %d\n", *temp);
	
	return 0;
}
