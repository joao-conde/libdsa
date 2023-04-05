#include "../include/stack.h"
#include "../include/vector.h"

struct stack {
    vector *data;
};

stack* stack_init(size_t type_size) {
    stack *s = (stack*) malloc(sizeof(stack));
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

size_t stack_size(const stack *s) {
    return vector_size(s->data);
}

bool stack_empty(const stack *s) {
    return vector_empty(s->data);
}

void stack_clear(stack *s) {
    vector_clear(s->data);
}

void* stack_top(const stack *s) {
    if (vector_empty(s->data)) return NULL;
    return vector_back(s->data);
}

void* stack_push(stack *s, void *value) {
    return vector_push(s->data, value);
}

void* stack_pop(stack *s) {
    return vector_pop(s->data);
}
