#include "list.h"

int main(){
	int a=5, b=10, c=12;

	LLIST* l1 = create_list();

	add_node_at(l1, 0, &a);
	add_node_at(l1, 0, &b);
	add_node_at(l1, 1, &c);

	int* temp;
	temp = (int*)read_node_at(l1, 0);
	printf("l1's data_index 0 : %d\n", *temp);
	temp = (int*)read_node_at(l1, 1);
	printf("l1's data_index 1 : %d\n", *temp);
	temp = (int*)read_node_at(l1, 2);
	printf("l1's data_index 2 : %d\n", *temp);

	del_node_at(l1, 0);
	del_node_at(l1, 0);
	del_node_at(l1, 0);

	printf("l1's size: %d\n", l1->count);

	return 0;
}
