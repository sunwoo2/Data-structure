#include "avl.h"

int main(){
	int a[1000];

	AVL_TREE* a1 = create_avl();

	AVL_add(a1, 10);
	AVL_add(a1, 15);
	AVL_add(a1, 5);
	AVL_add(a1, 2);
	AVL_add(a1, 7);
	AVL_add(a1, 17);
	AVL_add(a1, 12);
	AVL_add(a1, 8);
	AVL_add(a1, 1);
	AVL_add(a1, 6);
	AVL_add(a1, 9);

	AVL_del(a1, 7);

	printf("a1's root_data : %d\n", a1->root->data);
	printf("a1's Hmax : %d\n", find_Hmax(a1->root));
	printf("a1's Hmin : %d\n", find_Hmin(a1->root));
	printf("a1's root_balance : %d\n", a1->root->balance);

	preorder(a1->root); printf("\n");
	inorder(a1->root); printf("\n");

	return 0;
}
