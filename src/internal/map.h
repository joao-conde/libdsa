#ifndef SRC_PRIVATE_MAP_H_
#define SRC_PRIVATE_MAP_H_

#include "../../include/list.h"
#include "../../include/map.h"

#define CAPACITY 512
#define ALLOC_FACTOR 2
#define LOAD_FACTOR 1.0

struct map {
    size_t length;
    size_t capacity;
    size_t key_size;
    size_t value_size;
    float max_load_factor;
    list **buckets;
    hash_fn *hasher;
};

#endif // SRC_PRIVATE_MAP_H_
