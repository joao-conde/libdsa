#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2, m3;

int main() {
    deque *dq = deque_init(sizeof(mytype));

    deque_push_back(dq, &m1);
    deque_push_front(dq, &m2);

    mytype *at = deque_at(dq, 1);
    mytype *front = deque_front(dq);
    mytype *back = deque_back(dq);

    deque_pop_back(dq);
    deque_pop_front(dq);

    deque_clear(dq);

    deque_free(dq);
}
