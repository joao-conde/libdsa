#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2, m3;

size_t hash_int(const void *key) {
    return *(size_t*) key;
}

int main() {
    map *m = map_init(sizeof(int), sizeof(mytype), hash_int);

    map_insert(m, &m1.id, &m1);
    map_insert(m, &m2.id, &m2);
    map_insert(m, &m3.id, &m3);

    mytype *x = map_get(m, &m1.id);

    map_erase(m, &m2.id);

    map_clear(m);

    map_free(m);
}
