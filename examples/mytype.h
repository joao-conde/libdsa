#ifndef EXAMPLES_MYTYPE_H_
#define EXAMPLES_MYTYPE_H_

typedef struct mytype {
    int id;
    char *name;
    struct mytype *likes;
} mytype;

#endif // EXAMPLES_MYTYPE_H_
