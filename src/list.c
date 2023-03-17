#include <stdint.h>
#include <string.h>

#include "../include/list.h"

node* node_init(size_t type_size, const void *value);
void node_free(node *n);

struct list {
    size_t length;
    size_t type_size;
    node *front;
    node *back;
};

node* node_init(size_t type_size, const void *value) {
    // checks for overflow of amount of requested memory
    if (type_size > PTRDIFF_MAX) return NULL;

    node *n = (node*) malloc(sizeof(node));
    void *data = malloc(type_size);
    if (n == NULL || data == NULL) {
        free(data);
        free(n);
        return NULL;
    }

    memcpy(data, value, type_size);
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void node_free(node *n) {
    if (n != NULL) free(n->data);
    free(n);
}

list* list_init(size_t type_size) {
    list *l = (list*) malloc(sizeof(list));
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
    node *n = node_init(l->type_size, value);
    if (n == NULL) return NULL;

    if (list_is_empty(l)) {
        l->front = n;
        l->back = n;
    } else {
       l->back->next = n;
       n->prev = l->back;
       l->back = n;
    }

    l->length += 1;
    return n;
}

node* list_push_front(list *l, const void *value) {
    node *n = node_init(l->type_size, value);
    if (n == NULL) return NULL;

    if (list_is_empty(l)) {
        l->front = n;
        l->back = n;
    } else {
        n->next = l->front;
        l->front->prev = n;
        l->front = n;
    }

    l->length += 1;
    return n;
}

void list_pop_back(list *l) {
    if (list_is_empty(l)) return;

    node *back = l->back;
    node *prev = back->prev;
    l->back = prev;
    if (prev != NULL) prev->next = NULL;
    if (l->front == back) l->front = prev;

    l->length -= 1;
    node_free(back);
}

void list_pop_front(list *l) {
    if (list_is_empty(l)) return;

    node *front = l->front;
    node *next = front->next;
    l->front = next;
    if (next != NULL) next->prev = NULL;
    if (l->back == front) l->back = next;

    l->length -= 1;
    node_free(front);
}

node* list_insert(list *l, node *pos, const void *value) {
    node *n = node_init(l->type_size, value);
    if (n == NULL) return NULL;

    if (pos == l->back) {
        pos->next = n;
        n->prev = pos;
        l->back = n;
    } else {
        node *next = pos->next;
        pos->next = n;
        n->prev = pos;
        n->next = next;
        next->prev = n;
    }

    l->length += 1;
    return n;
}

void list_erase(list *l, node *pos) {
    bool is_back = l->back == pos;
    bool is_front = l->front == pos;
    if (is_back) list_pop_back(l);
    if (is_front) list_pop_front(l);
    if (is_back || is_front) return;

    node *next = pos->next;
    node *prev = pos->prev;
    next->prev = prev;
    prev->next = next;

    l->length -= 1;
    node_free(pos);
}
