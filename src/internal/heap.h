#ifndef SRC_INTERNAL_HEAP_H_
#define SRC_INTERNAL_HEAP_H_

#include "../../include/heap.h"

size_t _parent_index(size_t index);

size_t _left_child_index(size_t index);

size_t _right_child_index(size_t index);

#endif // SRC_INTERNAL_HEAP_H_
