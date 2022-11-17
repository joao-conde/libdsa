#ifndef INCLUDE_DEQUEUE_H_
#define INCLUDE_DEQUEUE_H_

#include <stdlib.h>

typedef struct dequeue dequeue;

dequeue* dequeue_init(size_t type_size);

void dequeue_free(dequeue *q);

#endif // INCLUDE_DEQUEUE_H_
