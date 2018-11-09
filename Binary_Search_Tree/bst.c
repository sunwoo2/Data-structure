#include "bst.h"

BST_TREE*
create_bst(){
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if(!tree) return false;

	tree->root = NULL;
	tree->count = 0;

	return tree;
}

T_NODE*
find_smallest_node
(T_NODE* root)
{
	if(root->left == NULL)
		return root;
	else
		return find_smallest_node(root->left);
}

T_NODE*
find_largest_node
(T_NODE* root)
{
	if(root->right == NULL)
		return root;
	else
		return find_largest_node(root->right);
}

T_NODE*
search_bst
(T_NODE* root, int key)
{
	if(root->data == key) // we found!
		return root;
	else if(key < root->data)
		return search_bst(root->left, key);
	else
		return search_bst(root->right, key);
	if(root == NULL){ // Not found!
		printf("Not found!\n");
		return NULL;
	}
}

T_NODE*	// Recursive!!!
add_bst
(T_NODE* root, int data)
{
	if(root == NULL){ //leaf
		T_NODE* newPtr = (T_NODE*)malloc(sizeof(T_NODE));
		if(!newPtr) return false;
		newPtr->left = NULL;
		newPtr->right= NULL;
		newPtr->data = data; // realy data insert
		return newPtr; //newby
	}
	if(data < root->data){
		root->left = add_bst(root->left, data);
		return root;
	} else{	// if, data == root->data?? -> nomally added 
		root->right = add_bst(root->right, data);
		return root;
	}
}

void
preorder
(T_NODE* root)
{
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void
inorder
(T_NODE* root)
{
	if(root != NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void
postorder
(T_NODE* root)
{
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

bool 
BST_insert
(BST_TREE* tree, int data)
{
	T_NODE* newRoot = add_bst(tree->root, data);
	if(newRoot == NULL) return false;
	else {
		tree->root = newRoot;
		tree->count++;
		return tree;
	}
}

T_NODE*
del_bst		// it's mine
(T_NODE* root, int data, bool* success)
{
	if(root == NULL){		// there is no delete_data
		*success = false;
		return NULL;
	}
	
	if(data < root->data){
		root->left = del_bst(root->left, data, success);
		return root;
	} else if(data > root->data){
		root->right = del_bst(root->right, data, success);
		return root;
	} else{		// matched!!
		T_NODE* del_node;
		if(root->left == NULL){
			del_node = root;
			root = root->right;
			free(del_node);
			*success = true;
			return root;
		} else if(root->right == NULL){
			del_node = root;
			root = root->left;
			free(del_node);
			*success = true;
			return root;
		} else{
			T_NODE* search;
			search = find_largest_node(root->left);		
//			search = root->left;					// when there is no find_ function 
//			while (search->right != NULL)
//				search = search->right;		
			root->data = search->data;
			root->left = del_bst(root->left, search->data, success);
			*success = true;
			return root;
		}
	}
}

bool
BST_del
(BST_TREE* tree, int data)
{
	bool success;
	T_NODE* newRoot;

	newRoot = del_bst(tree->root, data, &success);

	if(success){
		tree->root = newRoot;
		tree->count--;
		if(tree->count==0)
			tree->root = NULL;
	}
	return success;	
}

T_NODE*
delete_bst		// this class method
(T_NODE* root, int data, bool* success)
{
	if(root == NULL){		// there is no delete_data
		*success = false;
		return NULL;
	}
	
	if(data < root->data){
		root->left = del_bst(root->left, data, success);
	} else if(data > root->data){
		root->right = del_bst(root->right, data, success);
	} else{		// matched!!
		T_NODE* del_node = root;
		T_NODE* newRoot;
		if(root->left == NULL){
			newRoot = root->right;
			free(del_node);
			*success = true;
			return newRoot;
		} else if(root->right == NULL){
			newRoot = root->left;
			free(del_node);
			*success = true;
			return newRoot;
		} else{
			T_NODE* search;
			search = find_largest_node(root->left);
//			search = root;					// when there is no find_ function 
//			while (search->right != NULL)
//				search = search->right;		
			root->data = search->data;
			free(search);
			*success = true;
		}
	}
	return root;
}
