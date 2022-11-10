#include <stdlib.h>

#include "headers/vector.h"

Vector* vector() {
    Vector *vec = malloc(sizeof(Vector));
    vec->size = 0;
    return vec;
}
