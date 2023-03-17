#ifndef EXAMPLES_MYTYPE_H_
#define EXAMPLES_MYTYPE_H_

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct mytype {
    int id;
    char *name;
    struct mytype *likes;
} mytype;

void mytype_print(const mytype *m);

#endif // EXAMPLES_MYTYPE_H_
