#include <check.h>

#include "../include/linkedlist.h"

Suite* suite_linked_list() {
    Suite *suite = suite_create("linked list");
    TCase *test_case = tcase_create("");
    // tcase_add_test(test_case, test_dequeue_init);
    suite_add_tcase(suite, test_case);
    return suite;
}
