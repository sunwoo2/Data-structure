#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define LH -1
#define EH 0
#define RH 1

typedef struct node{
	int data;
	struct node* left;
	struct node* right;
	int BF;
} T_NODE;

typedef struct{
	int count;
	T_NODE* root;
} AVL_TREE;

AVL_TREE* create_avl();
bool add_avl(AVL_TREE* tree, int data);
T_NODE* add_node(T_NODE* root, int data, bool* success);
bool del_avl(AVL_TREE* tree, int data);
T_NODE* del_node(T_NODE* root, int data, bool* success);

T_NODE* rotate_right(T_NODE* root);
T_NODE* rotate_left(T_NODE* root);

int find_Hmax(T_NODE* root);
int find_Hmin(T_NODE* root);
bool check_avl(T_NODE* root);
void BF_update(T_NODE* root);

void preorder(T_NODE* root);
void inorder(T_NODE* root);
void postorder(T_NODE* root);
void preorder_BF(T_NODE* root);
