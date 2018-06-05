///\file Header file for lists functions
#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

/// \brief A struct to define a node list
struct list_node{
    int info; /**< The information of the node */
    struct list_node *next; /**< A pointer to the next node */
};

void print_list(struct list_node *list_head);
void push_element_beggining(struct list_node *list_head, int new_element_value);
int pop_first_element(struct list_node *list_head);
int pop_last_element(struct list_node *list_head);

#endif //LIST_FUNCTIONS_H
