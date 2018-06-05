/// \file Header file for graph functions
#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

/// \brief A struct to define a graph
struct g_graph{
    int no_nodes; /**< The graph's number of nodes */
    int init; /**< Value 1 means graph is initialized, value 0 means graph isn't initialized */
    int *adj_matrix; /**< The adjacency matrix of the graph */
};

void set_adj_matrix_value(struct g_graph *graph, int row_index, int column_index, int element_value);
int get_adj_matrix_value(struct g_graph *graph, int row_index, int column_index);
void initiate_graph(struct g_graph *graph);
int find_start_node(struct g_graph *graph);
void delete_start_node(struct g_graph *graph, int node);
void graph_bfs(struct g_graph *graph, int start_node);
void graph_dfs(struct g_graph *graph, int start_node);
void topological_sort_util(struct g_graph *graph, int node, int visited[], struct list_node *stack_head);
void topological_sort(struct g_graph *graph, int start_node);

#endif //GRAPH_FUNCTIONS_H
