#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2, m3;

int main() {
    vector *v = vector_init(sizeof(mytype));

    vector_push(v, &m1);
    vector_push(v, &m2);

    vector_insert(v, 1, &m3);

    mytype *m = vector_at(v, 1);

    vector_erase(v, 2);

    vector_pop(v);

    vector_resize(v, 1);

    vector_clear(v);

    vector_free(v);
}
