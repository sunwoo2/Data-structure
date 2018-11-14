#include "avl.h"

AVL_TREE* create_avl(){
	AVL_TREE* tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if(!tree) return false;

<<<<<<< HEAD
	tree->count = 0;
	tree->root = NULL;
	
	return tree;
}

int find_Hmax(T_NODE* root){
	int Hmax=0;
	
=======
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

>>>>>>> 01170c02b25adee60955592152342de9c8782974
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

<<<<<<< HEAD
bool check_avl(T_NODE* root){
	int HL, HR;

	HL = find_Hmax(root->left);
	HR = find_Hmax(root->right);

	if(abs(HL-HR) <= 1)
		return true;	
	else
		return false;
}
=======

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
>>>>>>> 01170c02b25adee60955592152342de9c8782974

void BF_update(T_NODE* root){
	if(find_Hmax(root->left) > find_Hmax(root->right))
		root->BF = LH;
	else if(find_Hmax(root->left) < find_Hmax(root->right))
		root->BF = RH;
	else
		root->BF = EH;
}

<<<<<<< HEAD
T_NODE* rotate_right(T_NODE* root){
	T_NODE* newroot;
	newroot = root->left;
	root->left = newroot->right;
	newroot->right = root;

	BF_update(newroot);
=======
T_NODE* rotate_right(T_NODE* root){		// LH일 경우 오른쪽 회전
	T_NODE* new_root;
	new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	
	//Balane factor update
>>>>>>> 01170c02b25adee60955592152342de9c8782974
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

<<<<<<< HEAD
bool add_avl(AVL_TREE* tree, int data){
	T_NODE* newroot;
	bool success;

	newroot = add_node(tree->root, data, &success);

	if(success){
		tree->root = newroot;
		tree->count++;
=======
void inorder(T_NODE* root){			// BST의 장점 inorder! 
	if(root != NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
>>>>>>> 01170c02b25adee60955592152342de9c8782974
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

<<<<<<< HEAD
bool del_avl(AVL_TREE* tree, int data){
	if(tree->count == 0){
		printf("there is no data!\n");
		return false;
	}
	
=======
bool AVL_del(AVL_TREE* avl, int data){			// add랑 거의 유사한 알고리즘
	if(avl->count == 0) return false;

>>>>>>> 01170c02b25adee60955592152342de9c8782974
	T_NODE* newroot;
	bool success;

	newroot = del_node(tree->root, data, &success);

	if(success){
		tree->root = newroot;
		tree->count--;
	}
	return success;
}

<<<<<<< HEAD
T_NODE* del_node(T_NODE* root, int data, bool* success){
	*success = false;
	
	if(root == NULL){		// We cannot found data in this tree!
		printf("there is no data!\n");
		return NULL;
	}

=======
T_NODE* del_avl(T_NODE* root, int data, bool* success){
	// First, assume data exist!					// 삭제할 데이터가 트리안에 존재한다고 가정하겠음
>>>>>>> 01170c02b25adee60955592152342de9c8782974
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
<<<<<<< HEAD
	}else{			// match!
		T_NODE* temp = root;
		if(root->left == NULL){
=======
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
>>>>>>> 01170c02b25adee60955592152342de9c8782974
			root = root->right;
			free(temp);

			*success = true;
			return root;
		}else if(root->right == NULL){
			root = root->left;
			free(temp);

			*success = true;
			return root;
<<<<<<< HEAD
		}else{		// left,right all exist!
			T_NODE* search;
			if(root->BF == LH){
				search = root->left;
				while(search->right != NULL)
					search = search->right;
=======
		}*/else{				// right, left all exist!		
			T_NODE* search;
			if(root->balance == RH){					// case1) root_balance == RH
				search = find_smallest_node(root->right);
>>>>>>> 01170c02b25adee60955592152342de9c8782974
				root->data = search->data;
				root->left = del_node(root->left, search->data, success);

				BF_update(root);
				*success = true;
				return root;
<<<<<<< HEAD
			}else{		// RH or EH (including EH is no problem!)
				search = root->right;
				while(search->left != NULL)
					search = search->left;
=======
			}else {						// case2) root_balance == LH, case3) EH / EH is anybody case
				search = find_largest_node(root->left);
>>>>>>> 01170c02b25adee60955592152342de9c8782974
				root->data = search->data;
				root->right = del_node(root->right, search->data, success);

				BF_update(root);
				*success = true;
				return root;
			}
		}
	}
}

<<<<<<< HEAD
void preorder(T_NODE* root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
=======
>>>>>>> 01170c02b25adee60955592152342de9c8782974

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
