#include <float.h>
#include <math.h>
#include <stdint.h>

#include "test.h"

bool fequals(float f1, float f2) {
    return fabs(f1 - f2) <= FLT_EPSILON;
}

size_t hash_str(const void *value) {
    size_t hash = 0;
    char *str = (char*) value;
    for (int i = 0; str[i] != 0; i++) hash += (i + 1) * (uint8_t) str[i];
    return hash;
}

size_t hash_size_t(const void *value) {
    return *(size_t*) value;
}

size_t hash_terribly(const void *value) {
    return hash_str(value) % 4;
}

bool gt_int(const void *a, const void *b) {
    return *(int*) a > *(int*) b;
}

bool lt_int(const void *a, const void *b) {
    return *(int*) a < *(int*) b;
}

bool lt_float(const void *a, const void *b) {
    return *(float*) a < *(float*) b;
}

bool lt_size_t(const void *a, const void *b) {
    return *(size_t*) a < *(size_t*) b;
}
