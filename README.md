# libdsa

C data structures and algorithms library, based on the C++ STL.

## Features

- Opaque data types
- PIMPL design pattern
- C generic data structures leveraging void pointers
- 100% code coverage
- Memory-leak detection with Valgrind
- Google's C/C++ style

## Examples

Check the [examples folder](./examples) for example uses of libdsa.

```c
#include <dsa.h>

int main() {
    vector *v = vector_init(sizeof(mytype));
    vector_push(v, &m1);
    vector_insert(v, 0, &m2);
    vector_pop(v);
    vector_clear(v);
    vector_free(v);
}
```

## Install

```bash
make release
make install
```

## References

- deque: https://en.cppreference.com/w/cpp/container/deque
- list: https://en.cppreference.com/w/cpp/container/list
- queue: https://en.cppreference.com/w/cpp/container/queue
- stack: https://en.cppreference.com/w/cpp/container/stack
- vector: https://en.cppreference.com/w/cpp/container/vector
