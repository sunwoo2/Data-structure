#include "avl.h"

int main(){
	int b = 5;

	AVL_TREE* t1 = create_avl();
	
	add_avl(t1, 15);
	add_avl(t1, 7);
	add_avl(t1, 20);
	add_avl(t1, 3);
	add_avl(t1, 17);
	add_avl(t1, 10);
	add_avl(t1, 25);
	add_avl(t1, 1);
	add_avl(t1, 5);
	add_avl(t1, 8);
	add_avl(t1, 13);
	add_avl(t1, 16);
	add_avl(t1, 18);
	add_avl(t1, 23);
	add_avl(t1, 27);
	add_avl(t1, 4);
	add_avl(t1, 30);
	add_avl(t1, 24);

	del_avl(t1, 10);
	del_avl(t1, 25);

	printf("t1's size: %d\n", t1->count);
	preorder(t1->root); printf("\n");
	preorder_BF(t1->root); printf("\n");

	return 0;
}
