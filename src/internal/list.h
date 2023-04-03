#ifndef SRC_INTERNAL_LIST_H_
#define SRC_INTERNAL_LIST_H_

#include "../../include/list.h"

list_node* _list_node_init(size_t type_size, const void *value);

void _list_node_free(list_node *n);

#endif // SRC_INTERNAL_LIST_H_
