#include <dsa.h>

#include "mytype.h"

extern mytype m1, m2;

int main() {
    pair *p = pair_init(&m1.name, &m1, sizeof(char*), sizeof(mytype));

    char *first = pair_first(p);
    mytype *second = pair_second(p);

    pair_set_first(p, &m2.name);
    pair_set_second(p, &m2);

    pair_free(p);
}
