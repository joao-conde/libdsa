#include <check.h>
#include <stdint.h>

#include "../../include/stack.h"

START_TEST(test_stack_init) {
    stack *s = stack_init(sizeof(int));
    ck_assert(s != NULL);
    stack_free(s);
}
END_TEST

START_TEST(test_stack_init_fail) {
    stack *s = stack_init(SIZE_MAX);
    ck_assert(s == NULL);
}
END_TEST

Suite* suite_stack() {
    Suite *suite = suite_create("stack");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_stack_init);
    tcase_add_test(test_case, test_stack_init_fail);
    suite_add_tcase(suite, test_case);
    return suite;
}
