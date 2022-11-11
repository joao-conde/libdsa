#include <check.h>

#include "../include/vector.h"

START_TEST(test_vector) {
    Vector *vec = vector(sizeof(int), 10);
    ck_assert_uint_eq(vector_length(vec), 0);
    ck_assert_uint_eq(vector_capacity(vec), 10);
}
END_TEST

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector);
    suite_add_tcase(suite, test_case);
    return suite;
}
