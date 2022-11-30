#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct map map;

map* map_init(size_t key_size, size_t value_size);

void map_free(map *m);

size_t map_length(const map *m);

bool map_is_empty(const map *m);

bool map_has(const map *m, const void *key);

void map_clear(map *m);

void* map_get(const map *m, const void *key);

void* map_insert(map *m, const void *key, const void *value);

void* map_erase(map *m, const void *key);

void rehash(map *m, size_t nbuckets);

#endif // INCLUDE_MAP_H_