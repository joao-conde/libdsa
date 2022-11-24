#include "../include/list.h"

struct list {
    size_t length;
};

list* list_init(size_t type_size) {
    list *l = malloc(sizeof(list));
    if (l == NULL) return NULL;
    l->length = 0;
    return l;
}

void list_free(list *l) {
    free(l);
}
