#include <stdlib.h>

#include "../include/vector.h"

Vector* vector() {
    Vector *vec = malloc(sizeof(Vector));
    vec->size = 0;
    return vec;
}
