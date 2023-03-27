#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include <stdlib.h>

#include "../include/pair.h"

typedef size_t (hash_fn)(const void* key);

typedef struct map map;

map* map_init(size_t key_size, size_t value_size, hash_fn *hasher);

void map_free(map *m);

size_t map_length(const map *m);

pair* map_find(const map *m, const void *key);

void* map_get(const map *m, const void *key);

pair* map_insert(map *m, const void *key, const void *value);

#endif // INCLUDE_MAP_H_
