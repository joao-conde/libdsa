#include <check.h>
#include <stdint.h>
#include <string.h>

#include "../include/pair.h"

START_TEST(test_pair_size) {
    ck_assert(PAIR_SIZE);
}
END_TEST

START_TEST(test_pair_init) {
    int first = 1;
    char *second = "value";

    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
    ck_assert(p != NULL);

    pair_free(p);
}
END_TEST

START_TEST(test_pair_init_fail) {
    int x = 1;
    pair *p = pair_init(&x, &x, SIZE_MAX, SIZE_MAX);
    ck_assert(p == NULL);
}
END_TEST

START_TEST(test_pair_free) {
    pair_free(NULL);

    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
    pair_free(p);
}
END_TEST

START_TEST(test_pair_first) {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));

    ck_assert(*(int*)pair_first(p) == first);

    pair_free(p);
}
END_TEST

START_TEST(test_pair_second) {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
    ck_assert(strcmp(pair_second(p), "value") == 0);

    pair_free(p);
}
END_TEST

START_TEST(test_pair_stress) {
    int nelements = 100000;
    int *first, *second;
    for (int i = 0; i < nelements; i++) {
        pair *p = pair_init(&i, &i, sizeof(int), sizeof(int));
        first = pair_first(p);
        second = pair_second(p);
        ck_assert(*first == i);
        ck_assert(*second == i);
        pair_free(p);
    }
}
END_TEST

Suite* suite_pair() {
    Suite *suite = suite_create("pair");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_pair_size);
    tcase_add_test(test_case, test_pair_init);
    tcase_add_test(test_case, test_pair_init_fail);
    tcase_add_test(test_case, test_pair_free);
    tcase_add_test(test_case, test_pair_first);
    tcase_add_test(test_case, test_pair_second);
    tcase_add_test(test_case, test_pair_stress);
    suite_add_tcase(suite, test_case);
    return suite;
}
