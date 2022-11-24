#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct list list;

list* list_init(size_t type_size);

void list_free(list *l);

size_t list_length(const list *l);

bool list_is_empty(const list *l);

void list_clear(list *l);

void* list_front(const list *l);

void* list_back(const list *l);

void* list_push_back(list *l, const void *value);

void* list_push_front(list *l, const void *value);

void* list_pop_back(list *l);

void* list_pop_front(list *l);

void* list_insert(list *l, size_t index, const void *value);

void* list_erase(list *l, size_t index);

#endif // INCLUDE_LIST_H_
