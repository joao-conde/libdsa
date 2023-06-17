#include "../include/heap.h"
#include "../include/vector.h"
#include "internal/heap.h"

struct heap {
    vector *data;
};

heap* heap_init(size_t type_size) {
    heap *h = (heap*) malloc(sizeof(heap));
    vector *data = vector_init(type_size);
    if (h == NULL || data == NULL) {
        vector_free(data);
        free(h);
        return NULL;
    }

    h->data = data;
    return h;
}

void heap_free(heap *h) {
    if (h != NULL) vector_free(h->data);
    free(h);
}

size_t heap_size(const heap *h) {
    return vector_size(h->data);
}

bool heap_empty(const heap *h) {
    return vector_empty(h->data);
}

void heap_clear(heap *h) {
    vector_clear(h->data);
}

void* heap_max(const heap *h) {
    return vector_at(h->data, 0);
}

void heap_push(heap *h, const void *value) {
    vector_push(h->data, value);

    size_t index = vector_size(h->data) - 1;
    while (true) {
        size_t parent_index = _parent_index(index);
        void *parent = vector_at(h->data, parent_index);

        // TODO(joao-conde): comparison must be a function for this type
        if (value <= parent) break;

        vector_set(h->data, index, parent);
        vector_set(h->data, parent_index, value);
        index = parent_index;
    }
}

void heap_pop(heap *h) {
    void *last = vector_pop(h->data);
    vector_set(h->data, 0, last);

    size_t index = 0;
    while (true) {
        size_t left_child_index = _left_child_index(index);
        void *left_child = vector_at(h->data, left_child_index);

        size_t right_child_index = _right_child_index(index);
        void *right_child = vector_at(h->data, right_child_index);

        // TODO(joao-conde): comparison must be a function for this type
        if (last >= left_child && last >= right_child) break;

        if (left_child >= right_child) {
            vector_set(h->data, index, left_child);
            vector_set(h->data, left_child_index, last);
            index = left_child_index;
        } else {
            vector_set(h->data, index, right_child);
            vector_set(h->data, right_child_index, last);
            index = right_child_index;
        }
    }
}

size_t _parent_index(size_t index) {
    return (index - 1) / 2;
}

size_t _left_child_index(size_t index) {
    return 2 * index + 1;
}

size_t _right_child_index(size_t index) {
    return 2 * index + 2;
}