# libdsa

**C data structures** and **algorithms** library.

A personal endeavor to **learn the inner workings** of different **data structures** and **algorithms**. Consider using production-ready C template container libraries.

## Features

- **Opaque data types**
- **PIMPL** design pattern
- **C generics** leveraging **void pointers**
- Benchmarks versus the C++ STL
- Compliance with [Google's Sanitizers](https://github.com/google/sanitizers)
- Compliance with [Google's C/C++ style](https://github.com/cpplint/cpplint)
- 100% code coverage

## Examples

Check the [examples folder](./examples) for more uses of libdsa.

```c
#include <dsa.h>

int main() {
    vector *v = vector_init(sizeof(mytype));
    vector_push(v, &m);
    vector_pop(v);
    vector_free(v);
}
```

## Usage

Install:

```bash
$ make release
$ make install
```

Import:

```c
#include <dsa.h>
```

Compile your code with `-ldsa`:

```bash
$ gcc yourcode.c -ldsa
```

## References

- deque: https://en.cppreference.com/w/cpp/container/deque
- list: https://en.cppreference.com/w/cpp/container/list
- map: https://en.cppreference.com/w/cpp/container/unordered_map
- pair: https://en.cppreference.com/w/cpp/utility/pair
- queue: https://en.cppreference.com/w/cpp/container/queue
- stack: https://en.cppreference.com/w/cpp/container/stack
- vector: https://en.cppreference.com/w/cpp/container/vector
