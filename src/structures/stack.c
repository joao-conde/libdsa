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

size_t stack_length(const stack *s) {
    return vector_length(s->data);
}

bool stack_is_empty(const stack *s) {
    return vector_is_empty(s->data);
}

void* stack_top(const stack *s) {
    if (stack_is_empty(s)) return NULL;
    return vector_back(s->data);
}

void* stack_push(stack *s, void *value) {
    return vector_push(s->data, value);
}

void* stack_pop(stack *s) {
    return vector_pop(s->data);
}
