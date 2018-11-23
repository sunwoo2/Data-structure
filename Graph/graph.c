#include "graph.h"

GRAPH* create_graph(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	if(!graph) return NULL;

	graph->count = 0;
	graph->v_list = create_v_list();

	return graph;
}

bool g_insert_vertex(GRAPH* graph, char vertex){
	VERTEX* new = (VERTEX*)malloc(sizeof(VERTEX));

	new->next = NULL;
	new->data = vertex;
	new->indegree = 0;
	new->outdegree = 0;
	new->processed = 0;
	new->a_list = create_a_list();

	add_vertex_at(graph->v_list, graph->v_list->count, new);		// insert at rear

	graph->count++;
	return true;
}

bool g_insert_arc(GRAPH* graph, char from, char to){
	ARC* new = (ARC*)malloc(sizeof(ARC));
	if(!new) return false;

	VERTEX* to_vertex = search_v_list(graph->v_list, to);		// find vertex
	VERTEX* from_vertex = search_v_list(graph->v_list, from);

	new->destination = to_vertex; 
	new->destination->indegree++;

	add_arc_at(from_vertex->a_list, from_vertex->a_list->count, new);		// add at rear 
	from_vertex->outdegree++;

	return true;
}

bool g_delete_vertex(GRAPH* graph, char vertex){			// include arc(edge) relation!!
	VERTEX* v1 = search_v_list(graph->v_list, vertex);
	ARC* temp = v1->a_list->front;		// delete all edge
	
	while(v1->a_list->count != 0)	
		g_delete_edge(graph, vertex, v1->a_list->front->destination->data);	// automatic reset front&count!!!

	del_vertex_at(graph->v_list, vertex);			// delete the vertex
	
	graph->count--;
	return true;
}

bool g_delete_arc(GRAPH* graph, char from, char to){
	VERTEX* from_vertex = search_v_list(graph->v_list, from);
	VERTEX* to_vertex = search_v_list(graph->v_list, to);

	del_arc_at(from_vertex->a_list, to);

	from_vertex->outdegree--;
	to_vertex->indegree--;

	return true;
}

V_LIST* create_v_list(){
	V_LIST* list = (V_LIST*)malloc(sizeof(V_LIST));
	if(!list) return NULL;

	list->count = 0;
	list->front = NULL;
	list->rear= NULL;
	list->pos= NULL;

	return list;
}

A_LIST* create_a_list(){
	A_LIST* list = (A_LIST*)malloc(sizeof(A_LIST));
	if(!list) return NULL;

	list->count = 0;
	list->front = NULL;
	list->rear= NULL;
	list->pos= NULL;

	return list;
}

bool g_insert_edge(GRAPH* graph, char A, char B){
	if(!g_insert_arc(graph, A, B)) return false;
	if(!g_insert_arc(graph, B, A)) return false;
	return true;
}

void DFT(V_LIST* v_list){
	int i;
	STACK* stack = create_stack();
	VERTEX* temp_v = v_list->front;
	ARC* temp_a;

	// Fisrt vertex
	push(stack, &(temp_v->data));
	temp_v->processed = 1;

	// start
	char* data;
	for(i=0; i<v_list->count; i++){
		data = (char*)pop(stack);
		printf("%c ", *data);

		temp_v = search_v_list(v_list, *data);		// find next vertex
		temp_v->processed = 1;				// processed!

		temp_a = temp_v->a_list->front;
		while(temp_a != NULL){							// all of arc push! ( not processed)
			if(temp_a->destination->processed == 0 )
				push(stack, &(temp_a->destination->data));		// vertex->data is 'char' not a pointer!!
			temp_a = temp_a->next;
		}
	}
	printf("\n");
	temp_v = v_list->front;
	while(temp_v != NULL){				// processed reset for next traverse!!
		temp_v->processed = 0;
		temp_v = temp_v->next;
	}
}

VERTEX* search_v_list(V_LIST* v_list, char data){
	VERTEX* temp = v_list->front;
	while(temp->data != data)
		temp = temp->next;
	return temp;
}

ARC* search_a_list(A_LIST* a_list, char data){
	ARC* temp = a_list->front;
	while(temp->destination->data != data)
		temp = temp->next;
	return temp;
}

bool g_delete_edge(GRAPH* graph, char A, char B){
	g_delete_arc(graph, A, B);
	g_delete_arc(graph, B, A);
	return true;
}

void BFT(V_LIST* v_list){
	int i;
	QUEUE* queue = create_queue();
	VERTEX* temp_v = v_list->front;
	ARC* temp_a;

	// Fisrt vertex
	enqueue(queue, &(temp_v->data));
	temp_v->processed = 1;

	// start
	char* data;
	for(i=0; i<v_list->count; i++){
		data = (char*)dequeue(queue);
		printf("%c ", *data);

		temp_v = search_v_list(v_list, *data);		// find next vertex
		temp_v->processed = 1;				// processed!

		temp_a = temp_v->a_list->front;
		while(temp_a != NULL){							// all of arc enqueue! ( not processed)
			if(temp_a->destination->processed == 0 ){
				enqueue(queue, &(temp_a->destination->data));	// vertex->data is 'char' not a pointer!!
			}
			temp_a = temp_a->next;
		}
	}
	printf("\n");
	temp_v = v_list->front;
	while(temp_v != NULL){				// processed reset for next traverse!!
		temp_v->processed = 0;
		temp_v = temp_v->next;
	}
}
