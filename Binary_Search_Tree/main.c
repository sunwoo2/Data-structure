#include "bst.h"

int main(){
	int a[6] = {0,1,2,4,5,6}; int i=3, b=0;
	BST_TREE* t1 = create_bst();	
	BST_insert(t1, i);
	bool success;

	BST_insert(t1, 10);
	BST_insert(t1, 15);
	BST_insert(t1, 5);
	BST_insert(t1, 2);
	BST_insert(t1, 7);
	BST_insert(t1, 1);
	BST_insert(t1, 3);
	BST_insert(t1, 6);
	BST_insert(t1, 8);

	BST_del(t1, 5);

	int smallest, largest, key;
	T_NODE* temp = find_smallest_node(t1->root);
	smallest = temp->data;	
	printf("t1's smallest_node_data: %d\n", smallest);
	printf("t1's largest_node_data: %d\n", find_largest_node(t1->root)->data);
	printf("t1's size: %d\n", t1->count);
	
	inorder(t1->root);printf("\n");
	preorder(t1->root);printf("\n");
	postorder(t1->root);printf("\n");

	return 0;
}
