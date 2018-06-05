///\file graph_functions.c
///\brief C library implementation for basic graph functions
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "list_functions.h"
#include "graph_functions.h"

/**
 *  \fn void set_adj_matrix_value(struct g_graph *graph, int row_index, int column_index, int element_value)
 *  \brief A function to set a value on a specific position in adjacency matrix of a graph
 *  \return void
 *  @param[in] *graph A pointer to a graph
 *  @param[in] row_index The index of the row in the adjacency matrix
 *  @param[in] column_index The index of the column in the adjacency matrix
    @param[in] element_value The value we put in the specific position in the adjacency matrix
 */
void set_adj_matrix_value(struct g_graph *graph, int row_index, int column_index, int element_value){
    int position = 0;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}

/**
 *  \fn int get_adj_matrix_value(struct g_graph *graph, int row_index, int column_index)
 *  \brief A function to get a value from a specific position in adjacency matrix of a graph
 *  \return The value from adjacency matrix specified by row_index and column_index
 *  @param[in] *graph A pointer to a graph
 *  @param[in] row_index The row index in the matrix
 *  @param[in] column_index The column index in the matrix
*/
int get_adj_matrix_value(struct g_graph *graph, int row_index, int column_index){
    int position = 0;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }else{
        printf("Please read the graph first");
        return -1;
    }
}

/**
 *  \fn void print_adj_matrix(struct g_graph *graph)
 *  \brief A function to print the adjacency matrix of a graph
 *  \return void
 *  @param[in] *graph A pointer to a graph
*/
void print_adj_matrix(struct g_graph *graph){
    int aux = 0;
    int row_index = 0;
    int column_index = 0;

    for(row_index = 0; row_index < graph->no_nodes; row_index++){
        for(column_index = 0; column_index < graph->no_nodes; column_index++){
            aux = get_adj_matrix_value(graph, row_index, column_index);
            printf("%d  ", aux);
        }
        printf("\n");
    }
}

/**
 *  \fn void initiate_graph(struct g_graph *graph)
 *  \brief A function to initiate a graph from a file
 *  \return void
 *  @param[in] *graph A pointer to a graph
*/
void initiate_graph(struct g_graph *graph){
    FILE *input_file = NULL;
    int rows_iterator = 0;
    int columns_iterator = 0;
    int aux = 0;

    input_file = fopen("input_file.txt", "r");
    if(input_file == NULL){
        printf("\nThe file doesn't exists.");
        fclose(input_file);
        return;
    }

    fscanf(input_file, "%d", &graph->no_nodes);
    assert(graph->no_nodes > 0);
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes, sizeof(int));

    for(rows_iterator = 0; rows_iterator < graph->no_nodes; rows_iterator++){
        for(columns_iterator = 0; columns_iterator < graph->no_nodes; columns_iterator++){
            fscanf(input_file, "%d", &aux);
            set_adj_matrix_value(graph, rows_iterator, columns_iterator, aux);
        }
    }

    graph->init = 1;

    fclose(input_file);

    printf("=== Reading from file successfull ===\n");
}

/**
 *  \fn int find_start_node(struct g_graph *graph)
 *  \brief A function to find the start node from a graph, a node who doesn't have vertices coming into it
 *  \return The start node found
 *  @param[in] *graph A pointer to a graph
*/
int find_start_node(struct g_graph *graph){
    int iterator_row = 0;
    int ok = 0;
    int start_node = 0;
    int aux = 0;

    if(graph->init == 0){
        printf("\nPlease initiate the graph first!");
        return -1;
    }

    for(start_node = 0; start_node < graph->no_nodes; start_node++){
        ok = 1;
        for(iterator_row = 0; iterator_row < graph->no_nodes; iterator_row++){
            aux = get_adj_matrix_value(graph, iterator_row, start_node);
            if(aux == 1){
                ok = 0;
                break;
            }
        }
        if(ok == 1){
            return start_node;
        }
    }

    printf("\nGraph cyclic can't perform a topological sort on it.");
    return -1;
}

/**
 *  \fn void graph_bfs(struct g_graph *graph, int start_node)
 *  \brief Breadth-first search
 *  \return void
 *  @param[in] *graph A pointer to a graph
 *  @param[in] start_node The start node of Breadth-first search
*/
void graph_bfs(struct g_graph *graph, int start_node){
    struct list_node *head_queue = NULL;
    int *visited = NULL;
    int column_index = 0;
    int aux = 0;
    int current_node = 0;

    head_queue = calloc(1, sizeof(struct list_node));
    head_queue->next = NULL;
    head_queue->info = 0; //no of elements in the queue
    visited = calloc((graph->no_nodes), sizeof(int));
    push_element_beggining(head_queue, start_node);
    visited[start_node] = 1;

    printf("\nBFS traversal: ");
    while (head_queue->next != NULL){
        current_node = pop_last_element(head_queue);
        printf("%d,",current_node);
        for(column_index = 0; column_index < graph->no_nodes; column_index++){
            aux = get_adj_matrix_value(graph, current_node, column_index);
            if ( (aux != 0) && ( (visited[column_index]) == 0 )){
                push_element_beggining(head_queue, column_index);
                visited[column_index] = 1;
            }
        }
    }

    free(head_queue);
    free(visited);
}

/**
 *  \fn void graph_dfs(struct g_graph *graph, int start_node)
 *  \brief Depth-first search
 *  \return void
 *  @param[in] *graph A pointer to a graph
 *  @param[in] start_node The start node of Depth-first search
*/
void graph_dfs(struct g_graph *graph, int start_node){
    struct list_node *head_stack = NULL;
    int *visited = NULL;
    int column_index = 0;
    int aux = 0;
    int current_node = 0;

    head_stack = calloc(1, sizeof(struct list_node));
    head_stack->next = NULL;
    head_stack->info = 0;
    visited = calloc(graph->no_nodes, sizeof(int));
    push_element_beggining(head_stack, start_node);
    visited[start_node] = 1;

    printf("\nDFS traversal: ");
    while(head_stack->next != NULL){
        current_node = pop_first_element(head_stack);
        printf("%d,",current_node);
        for(column_index = graph->no_nodes - 1; column_index >= 0; column_index--){
            aux = get_adj_matrix_value(graph, current_node, column_index);
            if( (aux != 0) && (visited[column_index] == 0) ){
                push_element_beggining(head_stack, column_index);
                visited[column_index] = 1;
            }
        }
    }
}

/**
 *  \fn void topological_sort_util(struct g_graph *graph, int node, int visited[], struct list_node *stack_head)
 *  \brief A recursive function to help us on primary topological sort function
 *  \return void
 *  @param[in] *graph A pointer to a graph
 *  @param[in] node The current node from the graph
 *  @param[in] visited[] An array to keep evidence of visited nodes
 *  @param[in] *stack_head A pointer to a stack head
*/
void topological_sort_util(struct g_graph *graph, int node, int visited[], struct list_node *stack_head){
    int iterator = 0;
    int aux = 0;

    visited[node] = 1;
    for(iterator = 0; iterator < graph->no_nodes; iterator++){
        aux = get_adj_matrix_value(graph, node, iterator);
        if( (aux != 0) && (visited[iterator] == 0) ){
            topological_sort_util(graph, iterator, visited, stack_head);
        }
    }
    push_element_beggining(stack_head, node);
}

/**
 *  \fn void topological_sort(struct g_graph *graph, int start_node)
 *  \brief This function print the topological sort of a graph
 *  \return void
 *  @param[in] *graph A pointer to a graph
 *  @param[in] start_node The start node of the topological sort
*/
void topological_sort(struct g_graph *graph, int start_node){
	struct list_node *stack_head = NULL;
	int *visited = NULL;
	int iterator = 0;
	int aux = 0;

	stack_head = calloc(1, sizeof(struct list_node));
	stack_head->next = NULL;
	visited = calloc(graph->no_nodes, sizeof(int));

	for(iterator = 0; iterator < graph->no_nodes; iterator++){
        if(visited[iterator] == 0){
            topological_sort_util(graph, iterator, visited, stack_head);
        }
	}

	printf("\nTopological sort of graph: ");
	while(stack_head->next != NULL){
        aux = pop_first_element(stack_head);
        printf("%d, ", aux);
	}
}
