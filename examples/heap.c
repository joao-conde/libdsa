#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2, m3;

bool lesser(const void *a, const void *b) {
    return ((mytype*) a)->id < ((mytype*) b)->id;
}

int main() {
    heap *h = heap_init(sizeof(mytype), lesser);

    heap_push(h, &m1);
    heap_push(h, &m2);
    heap_push(h, &m3);

    mytype *m = (mytype*) heap_top(h);

    heap_pop(h);

    heap_clear(h);

    heap_free(h);
}
