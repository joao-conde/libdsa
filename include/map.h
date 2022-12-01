#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include <stdbool.h>
#include <stdlib.h>

#include "./list.h"
#include "./pair.h"

typedef size_t (hash_fn)(const void* key);

typedef struct map map;

size_t hash_int(const void *key);

size_t hash_str(const void *key);

map* map_init(size_t key_size, size_t value_size, hash_fn *hash);

void map_free(map *m);

size_t map_length(const map *m);

bool map_is_empty(const map *m);

bool map_has(const map *m, const void *key);

void map_clear(map *m);

node* map_find(const map *m, const void *key);

void* map_get(const map *m, const void *key);

pair* map_insert(map *m, const void *key, const void *value);

void map_erase(map *m, const void *key);

void rehash(map *m, size_t nbuckets);

#endif // INCLUDE_MAP_H_
