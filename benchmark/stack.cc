#include <stack>

#include "benchmark.h"

void bcc_stack_push() {
    std::stack<size_t> s;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s.push(i);
    }
}

void bcc_stack_push_pop() {
    std::stack<size_t> s;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s.push(i);
    }
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s.pop();
    }
}
