#include <stdlib.h>

#include "mytype.h"

mytype m1 = { .id = 1, .name = "m1" };
mytype m2 = { .id = 2, .name = "m2", .likes = &m1 };
mytype m3 = { .id = 3, .name = "m3", .likes = &m2 };
mytype m4 = { .id = 4, .name = "m4", .likes = &m3 };

void mytype_print(const mytype *m) {
    char *likes_name = m->likes != NULL ? m->likes->name : "(nil)";
    printf("mytype(id=%d, name=%s, likes=%s)\n", m->id, m->name, likes_name);
}
