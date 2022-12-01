#ifndef INCLUDE_PAIR_H_
#define INCLUDE_PAIR_H_

#include <stdlib.h>

typedef struct pair pair;

size_t pair_sizeof();

pair* pair_init(
    const void *first,
    const void *second,
    size_t first_size,
    size_t second_size
);

void pair_free(pair *p);

void* pair_first(const pair *p);

void* pair_second(const pair *p);

#endif // INCLUDE_PAIR_H_
