///\file list_functions.c
///\brief C library implementation for using lists, stacks and queues
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list_functions.h"

/**
 *  \fn void print_list(struct list_node *list_head)
 *  \brief A function to print a list
 *  \return void
 *  @param[in] *list_head A pointer to a list head
*/
void print_list(struct list_node *list_head){
    struct list_node *iterator = list_head;

    if(iterator->next == NULL){
        printf("\nStack/Queue is empty.");
    }else{
        printf("\nStack/Queue: ");
        while(iterator->next!= NULL){
            printf("%d, ", iterator->next->info);
            iterator = iterator->next;
        }
    }
}

/**
 *  \fn void push_element_beggining(struct list_node *list_head, int new_element_value)
 *  \brief A function to add an element at the beggining of the list
 *  \return void
 *  @param[in] *list_head A pointer to a list head
 *  @param[in] new_element_value The value of the pushed element
*/
void push_element_beggining(struct list_node *list_head, int new_element_value){
    struct list_node *pushed_element = malloc(sizeof(struct list_node));

    pushed_element->info = new_element_value;
    pushed_element->next = list_head->next;
    list_head->next = pushed_element;
}

/**
 *  \fn int pop_first_element(struct list_node *list_head)
 *  \brief A function to pop the first element of the list
 *  \return The information of first node in the list/stack/queue
 *  @param[in] *list_head A pointer to a list head
*/
int pop_first_element(struct list_node *list_head){
    int aux = 0;
    struct list_node *popped_element = malloc(sizeof(struct list_node));

    if(list_head->next != NULL){
        popped_element = list_head->next;
        aux = popped_element->info;
    }else{
        printf("\nNo element to be popped.");
        return -1;
    }

    list_head->next = popped_element->next;
    free(popped_element);

    return aux;
}

/**
 *  \fn int pop_last_element(struct list_node *list_head)
 *  \brief A function to pop the last element of the list
 *  \return The information of last element of the list/stack/queue
 *  @param[in] *list_head A pointer to a list head
*/
int pop_last_element(struct list_node *list_head){
    int aux = 0;
    struct list_node *iterator = list_head;
    struct list_node *popped_element = malloc(sizeof(struct list_node));
    struct list_node *new_last_element = malloc(sizeof(struct list_node));

    if(list_head->next == NULL){
        printf("\nNo element to be popped");
        return -1;
    }else{
        while(iterator->next->next != NULL){
            iterator = iterator->next;
        }
        new_last_element = iterator;
        popped_element = iterator->next;
        aux = popped_element->info;
    }

    free(popped_element);
    new_last_element->next = NULL;

    return aux;
}
