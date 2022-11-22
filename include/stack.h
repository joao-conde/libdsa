#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct stack stack;

stack* stack_init(size_t type_size);

void stack_free(stack *s);

size_t stack_length(const stack *s);

bool stack_is_empty(const stack *s);

void stack_clear(stack *s);

void* stack_top(const stack *s);

void* stack_push(stack *s, void *value);

void* stack_pop(stack *s);

#endif // INCLUDE_STACK_H_
