#include "mytype.h"

mytype m1 = { .id = 1, .name = "m1" };
mytype m2 = { .id = 2, .name = "m2", .likes = &m1 };
mytype m3 = { .id = 3, .name = "m3", .likes = &m2 };
