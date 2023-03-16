#include <stdbool.h>

#include "../include/stack.h"

int main() {
    int nelements = 100000000;
    bool is_empty;
    size_t length;
    int *top, *pushed, *popped;

    stack *s = stack_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = stack_push(s, &i);
        length = stack_length(s);
        is_empty = stack_is_empty(s);
        top = stack_top(s);
    }

    for (int i = 0; i < nelements / 2; i++) {
        top = stack_top(s);
        popped = stack_pop(s);
        length = stack_length(s);
        is_empty = stack_is_empty(s);
    }

    stack_free(s);
}