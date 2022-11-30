#include <check.h>
#include <stdint.h>

#include "../include/map.h"

START_TEST(test_map_init) {
    map *m = map_init(sizeof(int), sizeof(int), NULL);
    ck_assert(map_is_empty(m));
    map_free(m);
}
END_TEST

START_TEST(test_map_free) {
    map_free(NULL);

    map *m = map_init(sizeof(int), sizeof(int), NULL);
    map_free(m);
}
END_TEST

START_TEST(test_map_length) {
    float value = 3.5;
    map *m = map_init(sizeof(float), sizeof(float), NULL);
    ck_assert(map_length(m) == 0);

    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    ck_assert(map_length(m) == 3);

    map_free(m);
}
END_TEST

START_TEST(test_map_is_empty) {
    map *m = map_init(sizeof(int), sizeof(int), NULL);
    ck_assert(map_is_empty(m));

    int value = -10;
    map_insert(m, &value, &value);
    ck_assert(!map_is_empty(m));

    map_erase(m, &value);
    ck_assert(map_is_empty(m));

    map_free(m);
}
END_TEST

START_TEST(test_map_clear) {
    float value = 3.5;
    map *m = map_init(sizeof(float), sizeof(float), NULL);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    ck_assert(map_length(m) == 3);

    map_clear(m);
    ck_assert(map_length(m) == 0);

    map_free(m);
}
END_TEST

Suite* suite_map() {
    Suite *suite = suite_create("map");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_map_init);
    tcase_add_test(test_case, test_map_free);
    tcase_add_test(test_case, test_map_length);
    tcase_add_test(test_case, test_map_is_empty);
    tcase_add_test(test_case, test_map_clear);
    suite_add_tcase(suite, test_case);
    return suite;
}
