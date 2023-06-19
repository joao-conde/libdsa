#include "../include/heap.h"
#include "../include/vector.h"

struct heap {
    vector *data;
    lt_fn *lesser;
};

heap* heap_init(size_t type_size, lt_fn *lesser) {
    heap *h = (heap*) malloc(sizeof(heap));
    vector *data = vector_init(type_size);
    if (h == NULL || data == NULL || lesser == NULL) {
        vector_free(data);
        free(h);
        return NULL;
    }

    h->data = data;
    h->lesser = lesser;
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

void* heap_top(const heap *h) {
    return vector_at(h->data, 0);
}

void heap_push(heap *h, const void *value) {
    vector_push(h->data, value);

    size_t index = vector_size(h->data) - 1;
    while (index > 0) {
        size_t parent_index = (index - 1) / 2;
        void *parent = vector_at(h->data, parent_index);

        if (h->lesser(value, parent)) break;

        vector_set(h->data, index, parent);
        vector_set(h->data, parent_index, value);
        index = parent_index;
    }
}

void heap_pop(heap *h) {
    if (heap_empty(h)) return;

    void *last = vector_pop(h->data);
    vector_set(h->data, 0, last);

    size_t index = 0;
    while (true) {
        size_t left_child_index = 2 * index + 1;
        size_t right_child_index = 2 * index + 2;

        void *left_child = vector_at(h->data, left_child_index);
        void *right_child = vector_at(h->data, right_child_index);

        bool swap_left =
            left_child != NULL &&
            h->lesser(last, left_child) &&
            (right_child == NULL || h->lesser(right_child, left_child));

        bool swap_right =
            right_child != NULL &&
            h->lesser(last, right_child) &&
            (left_child == NULL || h->lesser(left_child, right_child));

        if (swap_left) {
            vector_set(h->data, index, left_child);
            vector_set(h->data, left_child_index, last);
            index = left_child_index;
        } else if (swap_right) {
            vector_set(h->data, index, right_child);
            vector_set(h->data, right_child_index, last);
            index = right_child_index;
        } else {
            break;
        }
    }
}
