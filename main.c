#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list_functions.h"
#include "graph_functions.h"

int main(){
    struct g_graph *graph = NULL;
    int start_node = 0;

    graph = calloc(1, sizeof(struct g_graph));

    initiate_graph(graph);

    start_node = find_start_node(graph);

    graph_bfs(graph, start_node);
    graph_dfs(graph, start_node);

    topological_sort(graph, start_node);
	
	printf("\nPress any key to exit.");
	getch();

    free(graph);

    return 0;
}
