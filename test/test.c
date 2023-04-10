#include <float.h>
#include <math.h>
#include <stdint.h>

#include "test.h"

size_t hash_str(const void *key) {
    size_t hash = 0;
    char *str = (char*) key;
    for (int i = 0; str[i] != 0; i++) hash += (i + 1) * (uint8_t) str[i];
    return hash;
}

size_t hash_int(const void *key) {
    return *(int*) key;
}

size_t hash_terribly(const void *key) {
    return hash_str(key) % 4;
}

bool fequals(float f1, float f2) {
    return fabs(f1 - f2) <= FLT_EPSILON;
}
