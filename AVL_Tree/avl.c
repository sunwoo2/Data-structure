#include "avl.h"

AVL_TREE* create_avl(){
	AVL_TREE* avl = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if(!avl) return false;

	avl->count = 0;
	avl->root  = NULL;

	return avl;
}

bool AVL_add(AVL_TREE* avl, int data){
	T_NODE* new_root;
	bool success;			// add_avl함수에서 bool타입 값 까지 반환 받기  

	new_root = add_avl(avl->root, data, &success);		// new_root는 새로운 노드가 추가된 루트로 지정

	if(success){
		avl->root = new_root;
		avl->count++;
	}
	return success;
}

T_NODE* add_avl(T_NODE* root ,int data, bool* success){			// 루트 최하단 leaf노드에 데이터(노드) 추가하기
	if(root == NULL){						// leaf노드 도착! 추가하고 return
		T_NODE* new_root = (T_NODE*)malloc(sizeof(T_NODE));
		if(!new_root){
			*success = false;
			return NULL;
		}

		new_root->data = data;
		new_root->left = NULL;
		new_root->right= NULL;
		new_root->balance = EH;

		*success = true;
		return new_root;
	}
	if(data < root->data){			
		root->left = add_avl(root->left, data, success);	//추가할 데이터가 나보다 작으면 left노드한테 recursive하게
		BF_update(root);					// left노드가 반환되고 balance_factor 업데이트
		if(find_Hmax(root) - find_Hmin(root) > 1){ 		// 노드 추가했는데 AVL구조 깨졋을경우 rotate통해 다시 맞추기
			if(root->left->balance == LH){				// case 1 LH-LH (BF에 따라서 경우 나뉜다)
				root = rotate_right(root);
			}else{							// case 3 LH-RH
				root->left = rotate_left(root->left);
				root = rotate_right(root);
			}
		}
		*success = true;
		return root;
	} else{
		root->right = add_avl(root->right, data, success);
		BF_update(root); 	// update root_BF
		if(find_Hmax(root) - find_Hmin(root) > 1){ 		// Invalid AVL!!
			if(root->right->balance == RH){				// case 2 RH-RH
				root = rotate_left(root);
			}else{							// case 4 RH-LH
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}
		}
		*success = true;
		return root;
	}
}

int find_Hmax(T_NODE* root){		// 얘네들은 BF_update를 위한 함수
	int Hmax=-1;

	while(root != NULL){
		if(root->balance == LH){
			root = root->left;
			Hmax++;
		}else if(root->balance == RH){
			root = root->right;
			Hmax++;
		}else{
			root = root->right;
			Hmax++;
		}
	}
	return Hmax;
}

int find_Hmin(T_NODE* root){
	int Hmin=-1;

	while(root != NULL){
		if(root->balance == LH){
			root = root->right;
			Hmin++;
		}else if(root->balance == RH){
			root = root->left;
			Hmin++;
		}else{
			root = root->right;
			Hmin++;
		}
	}
	return Hmin;
}


void BF_update(T_NODE* root){					// BF 업데이트
	if(find_Hmax(root->left) > find_Hmax(root->right) )
		root->balance = LH;
	else if(find_Hmax(root->left) < find_Hmax(root->right) )
		root->balance = RH;
	else
		root->balance = EH;
}

T_NODE* rotate_left(T_NODE* root){		// RH일경우 왼쪽 회전
	T_NODE* new_root;
	new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;
	
	//Balane factor update
	BF_update(root);
	BF_update(new_root);

	return new_root;
}

T_NODE* rotate_right(T_NODE* root){		// LH일 경우 오른쪽 회전
	T_NODE* new_root;
	new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	
	//Balane factor update
	BF_update(root);
	BF_update(new_root);

	return new_root;
}

void preorder(T_NODE* root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(T_NODE* root){			// BST의 장점 inorder! 
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

bool AVL_del(AVL_TREE* avl, int data){			// add랑 거의 유사한 알고리즘
	if(avl->count == 0) return false;

	T_NODE* newroot;
	bool success;

	newroot = del_avl(avl->root, data, &success);

	if(success){
		avl->root = newroot;
		avl->count--;
		if(avl->count == 0)
			avl->root = NULL;
	}

	return success;
}

T_NODE* del_avl(T_NODE* root, int data, bool* success){
	// First, assume data exist!					// 삭제할 데이터가 트리안에 존재한다고 가정하겠음
	if(data < root->data){
		root->left = del_avl(root->left, data, success);
		BF_update(root);

		*success = true;
		return root;
	}else if(data > root->data){
		root->right = del_avl(root->right, data, success);
		BF_update(root);

		*success = true;
		return root;
	}else{		// matched!!
		T_NODE* del_node;
		if( (root->left==NULL) && (root->right==NULL) ){	// case0) leaf node, add와는 다르게 leaf노드 따로 생각해줘야함
			del_node = root;
			root = NULL;
			free(del_node);

			*success = true;
			return NULL;
		}
/*		else if(root->left == NULL){		// 주석처리한 이유는 밑에 두가지 경우에 얘네들이 포함되기때문에 주석처리 했지만,
							   가독성을 위해 남겨둠.
			del_node = root;
			root = root->right;
			free(del_node);
			root->balance = EH;

			*success = true;
			return root;
		}else if( root->right == NULL){
			del_node = root;
			root = root->left;
			free(del_node);
			root->balance = EH;

			*success = true;
			return root;
		}*/else{				// right, left all exist!		
			T_NODE* search;
			if(root->balance == RH){					// case1) root_balance == RH
				search = find_smallest_node(root->right);
				root->data = search->data;
				root->right = del_avl(root->right, search->data, success);
				BF_update(root);

				*success = true;
				return root;
			}else {						// case2) root_balance == LH, case3) EH / EH is anybody case
				search = find_largest_node(root->left);
				root->data = search->data;
				root->left = del_avl(root->left, search->data, success);
				BF_update(root);

				*success = true;
				return root;
			}
		}
	}
}


T_NODE* find_smallest_node(T_NODE* root){
	while(root->left != NULL)
		root = root->left;
	return root;
}

T_NODE* find_largest_node(T_NODE* root){
	while(root->right != NULL)
		root = root->right;
	return root;
}
