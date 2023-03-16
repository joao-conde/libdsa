#include <stdbool.h>

#include "../include//vector.h"

int main() {
    int random, nelements = 1000000;
    bool is_empty;
    size_t length, capacity;
    int *at, *set, *pushed, *popped, *inserted, *erased, *begin, *back, *end;

    vector *v = vector_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = vector_push(v, &i);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
    }

    for (int i = 0; i < nelements / 2; i++) {
        popped = vector_pop(v);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
    }

    vector_clear(v);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);

    for (int i = 0; i < nelements; i++) {
        length = vector_length(v);
        inserted = vector_insert(v, i, &i);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
    }

    for (int i = 0; i < nelements / 2; i++) {
        length = vector_length(v);
        erased = vector_erase(v, i);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
    }

    vector_resize(v, 100000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);

    vector_resize(v, 1000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);

    vector_resize(v, 1);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);

    vector_resize(v, 0);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);

    vector_free(v);
}