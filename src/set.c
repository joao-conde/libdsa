#include "../include/set.h"

struct set {};

set* set_init(size_t type_size, hash_fn *hasher) {}

set* set_with_buckets(size_t type_size, hash_fn *hasher, size_t nbuckets) {}

void set_free(set *s) {}

float set_max_load_factor(const set *s) {}

void set_set_max_load_factor(set *s, float factor) {}

float set_load_factor(const set *s) {}

size_t set_size(const set *s) {}

size_t set_buckets(const set *s) {}

bool set_empty(const set *s) {}

void set_clear(set *s) {}

bool set_has(const set *s, const void *value) {}

void* set_insert(set *s, const void *value) {}

void set_erase(set *s, const void *value) {}

void set_rehash(set *s, size_t nbuckets) {}
