#include <dsa.h>
#include <stdbool.h>

#include "mytype.h"

extern mytype m1, m2, m3;

size_t hash(const void *value) {
    return (size_t) ((mytype*) value)->id;
}

int main() {
    set *s = set_init(sizeof(mytype), hash);

    set_insert(s, &m1);
    set_insert(s, &m2);
    set_insert(s, &m3);

    bool x = set_has(s, &m1);

    set_erase(s, &m2);

    set_clear(s);

    set_free(s);
}
