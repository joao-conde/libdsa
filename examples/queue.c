#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2;

int main() {
    queue *q = queue_init(sizeof(mytype));

    queue_push(q, &m1);
    queue_push(q, &m2);

    mytype *at = queue_at(q, 1);
    mytype *front = queue_front(q);
    mytype *back = queue_back(q);

    queue_pop(q);

    queue_clear(q);

    queue_free(q);
}
