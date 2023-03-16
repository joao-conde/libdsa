# libdsa

C data structures and algorithms library, inspired on C++ STL.

## Features

- Opaque data types
- PIMPL design pattern
- C generic data structures leveraging void pointers

## Install

```bash
make release
make install
```

## Usage

```c
#include <dsa.h>

typedef struct mytype_t mytype_t;

int main() {
    mytype_t *m = malloc(sizeof(mytype_t));
    vector *v = vector_init(sizeof(mytype_t));
    vector_push(v, m);
}
```

## References

Generally followed the approach C++ STL takes.

- deque: https://en.cppreference.com/w/cpp/container/deque
- list: https://en.cppreference.com/w/cpp/container/list
- queue: https://en.cppreference.com/w/cpp/container/queue
- stack: https://en.cppreference.com/w/cpp/container/stack
- vector: https://en.cppreference.com/w/cpp/container/vector
- map: https://en.cppreference.com/w/cpp/container/unordered_map
