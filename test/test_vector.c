#include <check.h>

#include "../src/headers/vector.h"

START_TEST(test_vector_create) {
    Vector *vec = vector();
    ck_assert_int_eq(vec->size, 0);
}
END_TEST

Suite* test_vector_suite() {
    Suite *suite = suite_create("Vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector_create);
    suite_add_tcase(suite, test_case);
    return suite;
}
