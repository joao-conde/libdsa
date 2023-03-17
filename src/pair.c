#include <stdint.h>
#include <string.h>

#include "../include/pair.h"

struct pair {
    void *first;
    void *second;
    size_t first_size;
    size_t second_size;
};

size_t PAIR_SIZE = sizeof(pair);

pair* pair_init(
    const void *first,
    const void *second,
    size_t first_size,
    size_t second_size
) {
    // checks for overflow of amount of requested memory
    if (first_size > PTRDIFF_MAX || second_size > PTRDIFF_MAX) return NULL;

    pair *p = (pair*) malloc(sizeof(pair));
    void *f = malloc(first_size);
    void *s = malloc(second_size);
    if (p == NULL || f == NULL || s == NULL) {
        free(s);
        free(f);
        free(p);
        return NULL;
    }

    memcpy(f, first, first_size);
    memcpy(s, second, second_size);

    p->first = f;
    p->second = s;
    p->first_size = first_size;
    p->second_size = second_size;
    return p;
}

void pair_free(pair *p) {
    if (p != NULL) {
        free(p->first);
        free(p->second);
    }
    free(p);
}

void* pair_first(const pair *p) {
    return p->first;
}

void* pair_second(const pair *p) {
    return p->second;
}

void pair_set_first(pair *p, const void* first) {
    memcpy(p->first, first, p->first_size);
}

void pair_set_second(pair *p, const void* second) {
    memcpy(p->second, second, p->second_size);
}
