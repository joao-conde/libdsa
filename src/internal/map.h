#ifndef SRC_INTERNAL_MAP_H_
#define SRC_INTERNAL_MAP_H_

#include "../../include/list.h"
#include "../../include/map.h"

#define CAPACITY 512

#define ALLOC_FACTOR 2.0

#define LOAD_FACTOR 1.0

void _map_free_buckets(map *m);

list* _map_find_bucket(const map *m, const void *key);

list_node* _map_find_bucket_node(const map *m, const list *bucket, const void *key);

#endif // SRC_INTERNAL_MAP_H_
