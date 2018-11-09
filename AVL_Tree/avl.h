#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LH 1
#define EH 0
#define RH -1

typedef struct node{
	int data;
	struct node* left;
	struct node* right;
	int balance;	
} T_NODE;

typedef struct {
	int count;
	T_NODE* root;
} AVL_TREE;

AVL_TREE* create_avl();
T_NODE* add_avl(T_NODE* root, int data, bool* success);
bool AVL_add(AVL_TREE* avl, int data);
T_NODE* del_avl(T_NODE* root, int data, bool* success);		
bool AVL_del(AVL_TREE* avl, int data);						

void BF_update(T_NODE* root);
int find_Hmax(T_NODE* root);
int find_Hmin(T_NODE* root);

T_NODE* rotate_left(T_NODE* root);
T_NODE* rotate_right(T_NODE* root);

T_NODE* find_smallest_node(T_NODE* root);
T_NODE* find_largest_node(T_NODE* root);

void preorder(T_NODE* root);
void inorder(T_NODE* root);
void postorder(T_NODE* root);
