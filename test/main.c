#include <check.h>

START_TEST (test_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

Suite* test_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Test");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_basic);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(){
    int failed;

    Suite *s;
    SRunner *sr;
    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed == 0 ? 0 : -1;
}
