#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LH 1		// 노드 기준 Left_height 이 더 클때
#define EH 0		// 같을때
#define RH -1		// Right_height이 더클때

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
T_NODE* add_avl(T_NODE* root, int data, bool* success);			// 루트노드 업데이트
bool AVL_add(AVL_TREE* avl, int data);					// 트리 업데이트
T_NODE* del_avl(T_NODE* root, int data, bool* success);		
bool AVL_del(AVL_TREE* avl, int data);						

void BF_update(T_NODE* root);					// Balance_Factor 업데이트
int find_Hmax(T_NODE* root);					// 루트노드 밑으로 가장 큰 height 찾기
int find_Hmin(T_NODE* root);					// 루트노드 밑으로 가장 작은 height 찾기

T_NODE* rotate_left(T_NODE* root);				// AVL구조 맞추기위한 회전	
T_NODE* rotate_right(T_NODE* root);

T_NODE* find_smallest_node(T_NODE* root);
T_NODE* find_largest_node(T_NODE* root);

void preorder(T_NODE* root);
void inorder(T_NODE* root);
void postorder(T_NODE* root);
