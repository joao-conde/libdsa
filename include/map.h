#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include <stdlib.h>

typedef struct map map;

map* map_init(size_t key_size, size_t value_size);

void map_free(map *m);

void* map_get(const map *m, const void *key);

void map_insert(map *m, const void *key, const void *value);

#endif // INCLUDE_MAP_H_
