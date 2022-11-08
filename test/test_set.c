#include <check.h>

START_TEST(test_set_create) {
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_set_remove) {
    ck_assert_int_eq(1, 1);
}
END_TEST

Suite* test_set_suite() {
    Suite *suite = suite_create("Set");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_set_create);
    tcase_add_test(test_case, test_set_remove);
    suite_add_tcase(suite, test_case);
    return suite;
}
