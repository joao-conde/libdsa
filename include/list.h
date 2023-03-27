#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct list list;

typedef struct list_node list_node;

struct list_node {
    list_node *prev;
    list_node *next;
    void *data;
};

list_node* list_node_init(size_t type_size, const void *value);

void list_node_free(list_node *n);

list* list_init(size_t type_size);

void list_free(list *l);

size_t list_length(const list *l);

bool list_is_empty(const list *l);

void list_clear(list *l);

list_node* list_front(const list *l);

list_node* list_back(const list *l);

list_node* list_push_back(list *l, const void *value);

list_node* list_push_front(list *l, const void *value);

void list_pop_back(list *l);

void list_pop_front(list *l);

list_node* list_insert(list *l, list_node *pos, const void *value);

void list_erase(list *l, list_node *pos);

#endif // INCLUDE_LIST_H_
