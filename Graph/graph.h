#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	void* data_ptr;
	struct node* link;
} STACK_NODE;

typedef struct stack{
	int count;
	STACK_NODE* top;
} STACK;

typedef struct node2 {
	void* data_ptr;
	struct node2* next;
} QUEUE_NODE;

typedef struct {
	int count;
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
} QUEUE;

typedef struct node3{
	void* data_ptr;
	struct node3* next;
} NODE;

typedef struct {
	int count;
	NODE* front;	
	NODE* rear;	
	NODE* pos;	
} LLIST;

typedef struct {
	int count;
	struct vertex* front;	
	struct vertex* rear;	
	struct vertex* pos;	
} V_LIST;

typedef struct {
	int count;
	struct arc* front;	
	struct arc* rear;	
	struct arc* pos;	
} A_LIST;

typedef struct vertex{
	struct vertex* next;
	char data;
	int indegree;
	int outdegree;
	short processed;
	A_LIST* a_list;
} VERTEX;

typedef struct{
	int count;
	V_LIST* v_list;
} GRAPH;

typedef struct arc{
	struct vertex* destination;
	struct arc* next;
} ARC;

STACK* create_stack();
int push(STACK* stack, void* in); 
void* pop(STACK* stack); 

QUEUE* create_queue();
bool enqueue(QUEUE* queue, void* in);
void* dequeue(QUEUE* queue);

LLIST* create_list();
bool add_node_at(LLIST* list, unsigned int index, void* data);
bool del_node_at(LLIST* list, unsigned int index);
void* read_node_at(LLIST* list, unsigned int index);

GRAPH* create_graph();
V_LIST* create_v_list();
A_LIST* create_a_list();
bool g_insert_vertex(GRAPH* graph, char vertex);
bool g_insert_arc(GRAPH* graph, char from, char to);
bool g_delete_vertex(GRAPH* graph, char vertex);
bool g_delete_arc(GRAPH* graph, char from, char to);

bool add_vertex_at(V_LIST* list, unsigned int index, VERTEX* new_node);	// these function exist at llist.c
bool add_arc_at(A_LIST* list, unsigned int index, ARC* new_node);
bool del_vertex_at(V_LIST* list, char data); 
bool del_arc_at(A_LIST* list, char data); 

VERTEX* search_v_list(V_LIST* v_list, char data);
ARC* search_a_list(A_LIST* a_list, char data);
bool g_insert_edge(GRAPH* graph, char A, char B);
bool g_delete_edge(GRAPH* graph, char A, char B);

void DFT(V_LIST* v_list);
void BFT(V_LIST* v_list);
