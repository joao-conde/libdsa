#include <stdlib.h>
#include <string.h>

#include "../include/list.h"

node* node_init(size_t type_size, const void *value) {
    node *new = malloc(sizeof(node));
    void *data = malloc(type_size);
    if (new == NULL || data == NULL) {
        free(data);
        free(new);
        return NULL;
    }
    memcpy(data, value, type_size);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

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
        node *front = l->front;
        while (front != NULL) {
            node *tmp = front->next;
            node_free(front);
            front = tmp;
        }
    }
    free(l);
}

size_t list_length(const list *l) {
    return l->length;
}

bool list_is_empty(const list *l) {
    return l->length == 0;
}

node* list_front(const list *l) {
    if (list_is_empty(l)) return NULL;
    return l->front;
}

node* list_back(const list *l) {
    if (list_is_empty(l)) return NULL;
    return l->back;
}

node* list_push_back(list *l, const void *value) {
    node *new = node_init(l->type_size, value);
    new->prev = l->back;
    new->next = NULL;

    if (list_is_empty(l)) {
        l->front = new;
    } else {
        l->back->next = new;
    }

    l->back = new;
    l->length += 1;
    return new;
}

node* list_push_front(list *l, const void *value) {
    node *new = node_init(l->type_size, value);
    new->next = l->front;
    new->prev = NULL;

    if (list_is_empty(l)) {
        l->back = new;
    } else {
        l->front->prev = new;
    }

    l->front = new;
    l->length += 1;
    return new;
}

void list_pop_back(list *l) {
    if (list_is_empty(l)) return;
    node *back = l->back;
    node *prev = back->prev;
    l->back = prev;
    if (l->front == back) l->front = l->back;
    if (prev != NULL) prev->next = NULL;
    l->length -= 1;
    node_free(back);
}

void list_pop_front(list *l) {
    if (list_is_empty(l)) return;
    node *front = l->front;
    node *next = front->next;
    l->front = next;
    if (l->back == front) l->back = l->front;
    if (next != NULL) next->prev = NULL;
    l->length -= 1;
    node_free(front);
}

node* list_insert(list *l, node *pos, const void *value) {
    node *new = node_init(l->type_size, value);

    node *tmp = pos->next;

    pos->next = new;
    new->prev = pos;

    if (tmp != NULL) {
        new->next = tmp;
        tmp->prev = new;
    }

    if (l->back == pos) l->back = new;

    l->length += 1;
    return new;
}

node* list_erase(list *l, node *pos) {
    node *prev = pos->prev;
    node *next = pos->next;
    if (prev != NULL) prev->next = next;
    if (next != NULL) next->prev = prev;
    if (l->front == pos) l->front = prev != NULL ? prev : next;
    if (l->back == pos) l->back = next != NULL ? next : prev;
    l->length -= 1;
    node_free(pos);
    return pos;
}
