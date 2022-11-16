#include "../../include/stack.h"
#include "../../include/vector.h"

struct stack {
    vector *data;
};

stack* stack_init(size_t type_size) {
    stack *s = malloc(sizeof(stack));
    vector *data = vector_init(type_size);
    if (s == NULL || data == NULL) {
        vector_free(data);
        free(s);
        return NULL;
    }

    s->data = data;
    return s;
}

void stack_free(stack *s) {
    if (s != NULL) vector_free(s->data);
    free(s);
}
