#include "avl.h"

AVL_TREE* create_avl(){
	AVL_TREE* tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if(!tree) return false;

	tree->count = 0;
	tree->root = NULL;
	
	return tree;
}

int find_Hmax(T_NODE* root){
	int Hmax=0;
	
	while(root != NULL){
		if(root->BF == LH){
			root = root->left;
			Hmax++;
		}else {
			root = root->right;
			Hmax++;
		}
	}
	
	return Hmax;
}

int find_Hmin(T_NODE* root){
	int Hmin=0;
	
	while(root != NULL){
		if(root->BF == LH){
			root = root->right;
			Hmin++;
		}else {
			root = root->left;
			Hmin++;
		}
	}
	
	return Hmin;
}

bool check_avl(T_NODE* root){
	int HL, HR;

	HL = find_Hmax(root->left);
	HR = find_Hmax(root->right);

	if(abs(HL-HR) <= 1)
		return true;	
	else
		return false;
}

void BF_update(T_NODE* root){
	if(find_Hmax(root->left) > find_Hmax(root->right))
		root->BF = LH;
	else if(find_Hmax(root->left) < find_Hmax(root->right))
		root->BF = RH;
	else
		root->BF = EH;
}

T_NODE* rotate_right(T_NODE* root){
	T_NODE* newroot;
	newroot = root->left;
	root->left = newroot->right;
	newroot->right = root;

	BF_update(newroot);
	BF_update(root);

	return newroot;
}

T_NODE* rotate_left(T_NODE* root){
	T_NODE* newroot;
	newroot = root->right;
	root->right = newroot->left;
	newroot->left = root;
	
	BF_update(newroot);
	BF_update(root);
	
	return newroot;
}

bool add_avl(AVL_TREE* tree, int data){
	T_NODE* newroot;
	bool success;

	newroot = add_node(tree->root, data, &success);

	if(success){
		tree->root = newroot;
		tree->count++;
	}
	return success;
}

T_NODE* add_node(T_NODE* root, int data, bool* success){
	*success = false;

	if(root == NULL){
		T_NODE* new_node = (T_NODE*)malloc(sizeof(T_NODE));
		if(!new_node) return false;

		new_node->data = data;
		new_node->left = NULL;
		new_node->right= NULL;
		new_node->BF	= EH;

		*success = true;
		return new_node;
	}else if(data < root->data){
		root->left = add_node(root->left, data, success);
		BF_update(root);
		
		if(!check_avl(root)){		// Invalid AVL!
			if(root->left->BF == LH)		// case1) LH-LH
				root = rotate_right(root);
			else{					// case2) LH-RH
				root->left = rotate_left(root->left);
				root = rotate_right(root);
			}
		}

		*success = true;
		return root;
	}else{
		root->right = add_node(root->right, data, success);
		BF_update(root);
		
		if(!check_avl(root)){		// Invalid AVL!
			if(root->right->BF == RH)		// case3) RH-RH
				root = rotate_left(root);
			else{					// case4) RH-LH
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}
		}

		*success = true;
		return root;
	}
}

bool del_avl(AVL_TREE* tree, int data){
	if(tree->count == 0){
		printf("there is no data!\n");
		return false;
	}
	
	T_NODE* newroot;
	bool success;

	newroot = del_node(tree->root, data, &success);

	if(success){
		tree->root = newroot;
		tree->count--;
	}
	return success;
}

T_NODE* del_node(T_NODE* root, int data, bool* success){
	*success = false;
	
	if(root == NULL){		// We cannot found data in this tree!
		printf("there is no data!\n");
		return NULL;
	}

	if(data < root->data){
		root->left = del_node(root->left, data, success);
		BF_update(root);
		
		if(!check_avl(root)){		// Invalid AVL!
			if(root->right->BF == RH)		// case3) RH-RH
				root = rotate_left(root);
			else{					// case4) RH-LH
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}
		}

		*success = true;
		return root;
	}else if(data > root->data){
		root->right = del_node(root->right, data, success);
		BF_update(root);

		if(!check_avl(root)){		// Invalid AVL!
			if(root->left->BF == LH)		// case1) LH-LH
				root = rotate_right(root);
			else{					// case2) LH-RH
				root->left = rotate_left(root->left);
				root = rotate_right(root);
			}
		}
	
		*success = true;
		return root;
	}else{			// match!
		T_NODE* temp = root;
		if(root->left == NULL){
			root = root->right;
			free(temp);

			*success = true;
			return root;
		}else if(root->right == NULL){
			root = root->left;
			free(temp);

			*success = true;
			return root;
		}else{		// left,right all exist!
			T_NODE* search;
			if(root->BF == LH){
				search = root->left;
				while(search->right != NULL)
					search = search->right;
				root->data = search->data;
				root->left = del_node(root->left, search->data, success);

				BF_update(root);
				*success = true;
				return root;
			}else{		// RH or EH (including EH is no problem!)
				search = root->right;
				while(search->left != NULL)
					search = search->left;
				root->data = search->data;
				root->right = del_node(root->right, search->data, success);

				BF_update(root);
				*success = true;
				return root;
			}
		}
	}
}

void preorder(T_NODE* root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(T_NODE* root){
	if(root != NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void postorder(T_NODE* root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

void preorder_BF(T_NODE* root){
	if(root != NULL){
		printf("%d ", root->BF);
		preorder_BF(root->left);
		preorder_BF(root->right);
	}
}
