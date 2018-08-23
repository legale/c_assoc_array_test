#ifndef _SINGLE_LIST
#define _SINGLE_LIST
/*
 * Single linked list structure v0.1
 */

#include <stdlib.h>     //malloc() calloc() free()
#include <stdbool.h>    //bool true false
#include <string.h>     //memcpy() memcmp()
#include "inline.h"    //INLINE constant


//structures
//linked list
typedef struct list_node {
    unsigned char *key;
    unsigned long value;
    struct list_node *next;
} list_node;

//list
typedef struct list {
    unsigned int elements; //list elements counter
    struct list_node *head; //head node
    struct list_node *tail; //tail node
} list;


//functions declaration
INLINE list *list_unshift(list *lst, unsigned char *key, unsigned int len, unsigned long value);

INLINE list *list_push(list *lst, unsigned char *key, unsigned int len, unsigned long value);

INLINE list_node *list_get(list *lst, unsigned char *key, unsigned int len);

INLINE int list_remove(list *lst, unsigned char *key, unsigned int len);

INLINE list_node *list_nodes_traverse(list_node *parent, list_node *node, unsigned char *key, unsigned int len);


//internal function to find parent node by child element key
inline list_node *list_nodes_traverse(list_node *parent, list_node *node, unsigned char *key, unsigned int len) {
    if (memcmp(node->key, key, len) == 0) {
        return parent;
    } else if (node->next != NULL) {
        return list_nodes_traverse(node, node->next, key, len);
    } else {
        return NULL;
    }
}

//add list element in the beginning
inline list *list_unshift(list *lst, unsigned char *key, unsigned int len, unsigned long value) {
    if (lst == NULL) {
        lst = (list *) calloc(1, sizeof(list)); //init list with zeroes
    }
    unsigned char *key_allocated = (unsigned char *) malloc(len);
    memcpy(key_allocated, key, len);

    list_node *new = (list_node *) malloc(sizeof(list)); //allocate memory for the new element
    new->value = value;
    new->key = key_allocated;
    new->next = NULL;
    ++lst->elements;

    if (lst->head == NULL) {
        lst->tail = new;
        lst->head = new;
    } else {
        new->next = lst->head;
        lst->head = new;
    }

    return lst;
}


//add list element in the end
inline list *list_push(list *lst, unsigned char *key, unsigned int len, unsigned long value) {
    if (lst == NULL) {
        lst = (list *) calloc(1, sizeof(list)); //init new list with zeroes
    }
    unsigned char *key_allocated = (unsigned char *) malloc(len);
    memcpy(key_allocated, key, len);

    list_node *new = (list_node *) malloc(sizeof(list)); //allocate memory for the new element
    new->key = key_allocated;
    new->value = value;
    new->next = NULL;
    ++lst->elements;

    if (lst->tail == NULL) {
        lst->tail = new;
        lst->head = new;
    } else {
        lst->tail->next = new;
        lst->tail = new;
    }
    return lst;
};


//get list element by the key and key length
inline list_node *list_get(list *lst, unsigned char *key, unsigned int len) {
    if (lst == NULL || lst->head == NULL) {
        return NULL;
    }
    if (memcmp(lst->head->key, key, len) == 0) {
        return lst->head;
    }

    list_node *parent = list_nodes_traverse(NULL, lst->head, key, len);
    if (parent != NULL) {
        return parent->next;
    }
}


//remove list element by the key and key length
inline int list_remove(list *lst, unsigned char *key, unsigned int len) {
    if (memcmp(lst->head->key, key, len) == 0) {
        if (lst->head == lst->tail) { //if head = tail
            free(lst->head->key); //free key memory
            lst->head->key = NULL; //set list key pointer to NULL
            free(lst->head); //free list element memory
            lst->head = NULL; //set list pointer to NULL
            free(lst); //free list pointer
            lst = NULL; //set list pointer to NULL
            return 0;
        } else {
            list_node *next = lst->head->next;
            free(lst->head->key);
            lst->head->key = NULL; //set list pointer to NULL
            free(lst->head);
            lst->head = NULL; //set list pointer to NULL
            lst->head = next;
            return --lst->elements;
        }
    }

    list_node *parent = list_nodes_traverse(NULL, lst->head, key, len);
    if (parent != NULL) {
        list_node *next = parent->next->next;
        free(parent->next->key);
        parent->next->key = NULL; //set list key pointer to NULL
        free(parent->next);
        parent->next = next;
        --lst->elements;
        return true;
    } else {
        return false;
    }
}

#endif /* single_list.h  */