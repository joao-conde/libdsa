#include <dsa.h>
#include <list.h>

#include "mytype.h"

extern mytype m1, m2, m3;

int main() {
    list *l = list_init(sizeof(mytype));

    list_push_back(l, &m1);
    list_push_front(l, &m2);

    list_node *front = list_front(l);
    list_node *back = list_back(l);

    list_insert(l, front, &m3);
    list_erase(l, front);

    list_pop_front(l);
    list_pop_back(l);

    list_clear(l);

    list_free(l);
}
