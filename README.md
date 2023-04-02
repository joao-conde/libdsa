# libdsa

**C data structures and algorithms library**, based on the **C++ STL**.

A personal endeavor to **learn the inner workings** of different **data structures** and **algorithms**. Consider using production-ready C template container libraries.

## Features

- **Opaque data types**
- **PIMPL** design pattern
- **C generic** data structures leveraging **void pointers**
- Benchmarked and compared with the C++ STL
- 100% code coverage
- Memory-leak free (analyzed with Valgrind)
- Google's C/C++ style

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
