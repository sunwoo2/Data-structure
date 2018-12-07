#include "avl.h"

AVL_TREE* create_avl(){
	AVL_TREE* tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if(!tree) return false;

	tree->count = 0;
	tree->root = NULL;
	
	return tree;
}

int find_Hmax(T_NODE* root){			// 루트 기준 가장큰 Height 찾기
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

int find_Hmin(T_NODE* root){			// 루트 기준 가장작은 Height 찾기
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

bool check_avl(T_NODE* root){			// 루트 기준 AVL_TREE 구조를 만족하는지 체크
	if(root == NULL)
		return true;
	
	int HL, HR;

	HL = find_Hmax(root->left);
	HR = find_Hmax(root->right);

	if(abs(HL-HR) <= 1)
		return ( check_avl(root->left) && check_avl(root->right) );	
	else
		return false;
}

void BF_update(T_NODE* root){					// 루트노드의 BF 업데이트
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
		
		if(!check_avl(root)){					// Invalid AVL!
			if(root->left->BF == LH)				// case1) LH-LH
				root = rotate_right(root);
			else{							// case2) LH-RH
				root->left = rotate_left(root->left);
				root = rotate_right(root);
			}
		}

		*success = true;
		return root;
	}else{
		root->right = add_node(root->right, data, success);
		BF_update(root);
		
		if(!check_avl(root)){					// Invalid AVL!
			if(root->right->BF == RH)				// case3) RH-RH
				root = rotate_left(root);	
			else{							// case4) RH-LH
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
	
	if(root == NULL){				// We cannot found data in this tree!
		printf("there is no data!\n");
		return NULL;
	}

	if(data < root->data){
		root->left = del_node(root->left, data, success);
		BF_update(root);
		
		if(!check_avl(root)){					// Invalid AVL!, 삭제하고나서 AVL구조를 벗어난경우 다시 설정해주기
			if(root->right->BF == RH)				// case3) RH-RH
				root = rotate_left(root);
			else{							// case4) RH-LH
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}
		}

		*success = true;
		return root;
	}else if(data > root->data){
		root->right = del_node(root->right, data, success);
		BF_update(root);

		if(!check_avl(root)){					// Invalid AVL!
			if(root->left->BF == LH)				// case1) LH-LH
				root = rotate_right(root);
			else{							// case2) LH-RH
				root->left = rotate_left(root->left);
				root = rotate_right(root);
			}
		}
	
		*success = true;
		return root;
	}else{							// match!
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
		}else{						// left,right all exist!
			T_NODE* search;
			if(root->BF == LH){			// 삭제할 데이터노드의 left Height가 더 큰경우
				search = root->left;
				while(search->right != NULL)
					search = search->right;
				root->data = search->data;
				root->left = del_node(root->left, search->data, success);

				BF_update(root);
				*success = true;
				return root;
			}else{					// right Height가 큰경우와 EH인 경우(leaf node일 경우 까지 포함)
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

void preorder_BF(T_NODE* root){				// AVL_Tree 확인 하는 과정에서 사용할려고 만듬
	if(root != NULL){
		printf("%d ", root->BF);
		preorder_BF(root->left);
		preorder_BF(root->right);
	}
}
