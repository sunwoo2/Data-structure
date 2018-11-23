#include "graph.h"

int main(){
	GRAPH* g1 = create_graph();

	g_insert_vertex(g1, 'A');
	g_insert_vertex(g1, 'B');
	g_insert_vertex(g1, 'C');
	g_insert_vertex(g1, 'D');
	g_insert_vertex(g1, 'E');
	g_insert_vertex(g1, 'F');
	g_insert_vertex(g1, 'G');
	g_insert_vertex(g1, 'H');
	g_insert_vertex(g1, 'I');

	g_insert_edge(g1, 'A', 'B');
	g_insert_edge(g1, 'A', 'C');
	g_insert_edge(g1, 'A', 'D');
	g_insert_edge(g1, 'B', 'E');
	g_insert_edge(g1, 'B', 'F');
	g_insert_edge(g1, 'D', 'G');
	g_insert_edge(g1, 'D', 'H');
	g_insert_edge(g1, 'D', 'I');


//	g_insert_arc(g1, 'A', 'B');
//	g_insert_arc(g1, 'B', 'A');

	g_delete_vertex(g1, 'G');
//	g_delete_vertex(g1, 'C');
//	g_delete_vertex(g1, 'A');

//	g_delete_edge(g1, 'B', 'A');
//	g_delete_edge(g1, 'B', 'C');

//	g_delete_arc(g1, 'A', 'B');
//	g_delete_arc(g1, 'B', 'A');
	
	printf("g1's count: %d\n", g1->count);
	
	DFT(g1->v_list);
	BFT(g1->v_list);

	return 0;
}
