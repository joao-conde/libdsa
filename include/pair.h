#ifndef INCLUDE_PAIR_H_
#define INCLUDE_PAIR_H_

#include <stdlib.h>

extern size_t PAIR_SIZE;

typedef struct pair pair;

pair* pair_init(
    const void *first,
    const void *second,
    size_t first_size,
    size_t second_size
);

void pair_free(pair *p);

void* pair_first(const pair *p);

void* pair_second(const pair *p);

void pair_set_first(pair *p, const void* first);

void pair_set_second(pair *p, const void* second);

#endif // INCLUDE_PAIR_H_
