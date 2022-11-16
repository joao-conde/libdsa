#include <check.h>

Suite* suite_stack() {
    Suite *suite = suite_create("stack");
    TCase *test_case = tcase_create("");
    suite_add_tcase(suite, test_case);
    return suite;
}