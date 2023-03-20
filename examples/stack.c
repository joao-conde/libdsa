#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2;

int main() {
    stack *s = stack_init(sizeof(mytype));

    stack_push(s, &m1);
    stack_push(s, &m2);

    mytype *m = stack_top(s);

    stack_pop(s);

    stack_clear(s);

    stack_free(s);
}
