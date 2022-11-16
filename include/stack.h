#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdlib.h>

typedef struct stack stack;

stack* stack_init(size_t type_size);

void stack_free(stack *s);

#endif // INCLUDE_STACK_H_
