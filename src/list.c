#include "../include/list.h"
#include <stdlib.h>
#include <string.h>

typedef struct node node;
struct node {
    node *prev;
    node *next;
    void *data;
};

void node_free(node *n) {
    if (n != NULL) {
        free(n->data);
    }
    free(n);
}

struct list {
    size_t length;
    size_t type_size;
    node *front;
    node *back;
};

list* list_init(size_t type_size) {
    list *l = malloc(sizeof(list));
    if (l == NULL) return NULL;

    l->length = 0;
    l->type_size = type_size;
    l->front = NULL;
    l->back = NULL;
    return l;
}

void list_free(list *l) {
    if (l != NULL) {
        if (l->back != l->front) node_free(l->back);
        node_free(l->front);
    }
    free(l);
}

size_t list_length(const list *l) {
    return l->length;
}

bool list_is_empty(const list *l) {
    return l->length == 0;
}

void* list_front(const list *l) {
    if (list_is_empty(l)) return NULL;
    return l->front->data;
}

void* list_back(const list *l) {
    if (list_is_empty(l)) return NULL;
    return l->back->data;
}

void* list_push_back(list *l, const void *value) {
    node *new = malloc(sizeof(node));
    void *data = malloc(l->type_size);
    if (new == NULL || data == NULL) {
        free(data);
        node_free(new);
        return NULL;
    }

    memcpy(data, value, l->type_size);

    new->data = data;
    new->prev = l->back;
    new->next = NULL;

    if (list_is_empty(l)) {
        l->front = new;
    } else {
        l->back->next = new;
    }

    l->back = new;
    l->length += 1;
    return new->data;
}

void* list_push_front(list *l, const void *value) {
    node *new = malloc(sizeof(node));
    void *data = malloc(l->type_size);
    if (new == NULL || data == NULL) {
        free(data);
        node_free(new);
        return NULL;
    }

    memcpy(data, value, l->type_size);

    new->data = data;
    new->next = l->front;
    new->prev = NULL;

    if (list_is_empty(l)) {
        l->back = new;
    } else {
        l->front->prev = new;
    }

    l->front = new;
    l->length += 1;
    return new->data;
}

void list_pop_back(list *l) {
    if (list_is_empty(l)) return;
    node *back = l->back;
    node *prev = back->prev;
    l->back = prev;
    if (prev != NULL) prev->next = NULL;
    l->length -= 1;
}

void list_pop_front(list *l) {
    if (list_is_empty(l)) return;
    node *front = l->front;
    node *next = front->next;
    l->front = next;
    if (next != NULL) next->prev = NULL;
    l->length -= 1;
}
