#include <check.h>

#include "../include/list.h"

Suite* suite_list() {
    Suite *suite = suite_create("list");
    TCase *test_case = tcase_create("");
    // tcase_add_test(test_case, test_list_init);
    suite_add_tcase(suite, test_case);
    return suite;
}
