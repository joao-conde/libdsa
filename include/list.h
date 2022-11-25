#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct list list;

typedef struct node node;

struct node {
    node *prev;
    node *next;
    void *data;
};

list* list_init(size_t type_size);

void list_free(list *l);

size_t list_length(const list *l);

bool list_is_empty(const list *l);

node* list_front(const list *l);

node* list_back(const list *l);

node* list_push_back(list *l, const void *value);

node* list_push_front(list *l, const void *value);

void list_pop_back(list *l);

void list_pop_front(list *l);

node* list_insert(list *l, node *pos, const void *value);

node* list_erase(list *l, node *pos);

#endif // INCLUDE_LIST_H_
