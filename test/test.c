#include <float.h>
#include <math.h>
#include <stdint.h>

#include "test.h"

size_t hash_str(const void *value) {
    size_t hash = 0;
    char *str = (char*) value;
    for (int i = 0; str[i] != 0; i++) hash += (i + 1) * (uint8_t) str[i];
    return hash;
}

size_t hash_int(const void *value) {
    return *(int*) value;
}

size_t hash_terribly(const void *value) {
    return hash_str(value) % 4;
}

bool fequals(float f1, float f2) {
    return fabs(f1 - f2) <= FLT_EPSILON;
}
