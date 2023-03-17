#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2, m3, m4;

int main() {
    vector *v = vector_init(sizeof(mytype));

    vector_push(v, &m1);
    vector_push(v, &m2);
    vector_push(v, &m3);
    vector_insert(v, 1, &m4);

    for (size_t i = 0; i < vector_length(v); i++) {
        mytype *m = vector_at(v, i);
        mytype_print(m);
    }

    vector_erase(v, 2);
    vector_pop(v);
    vector_pop(v);

    vector_resize(v, 1);
    vector_resize(v, 100);
    vector_clear(v);

    vector_free(v);
}
