#include <check.h>
#include <stdint.h>

#include "../include/map.h"
#include "../include/pair.h"

START_TEST(test_hash_int) {
    int key = 3;
    size_t hash = hash_int(&key);
    ck_assert(key == hash);
    ck_assert(hash == hash_int(&key));
}
END_TEST

START_TEST(test_hash_str) {
    char *key = "hello world";
    size_t hash = hash_str(key);
    ck_assert(hash == 6736);
    ck_assert(hash == hash_str(key));
}
END_TEST

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

START_TEST(test_map_has) {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");

    ck_assert(map_has(m, "key1"));
    ck_assert(map_has(m, "key2"));
    ck_assert(map_has(m, "key3"));
    ck_assert(!map_has(m, "key4"));

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

START_TEST(test_map_get) {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");

    ck_assert(strcmp(map_get(m, "key1"), "value1") == 0);
    ck_assert(strcmp(map_get(m, "key2"), "value2") == 0);
    ck_assert(strcmp(map_get(m, "key3"), "value3") == 0);
    ck_assert(map_get(m, "key4") == NULL);

    map_free(m);
}
END_TEST

START_TEST(test_map_insert) {
    pair *inserted;
    char *first, *second;
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    ck_assert(map_length(m) == 0);
    ck_assert(!map_has(m, "key1"));
    ck_assert(!map_has(m, "key2"));
    ck_assert(!map_has(m, "key3"));

    inserted = map_insert(m, "key1", "value1");
    first = pair_first(inserted);
    second = pair_second(inserted);
    ck_assert(strcmp(first, "key1") == 0);
    ck_assert(strcmp(second, "value1") == 0);

    inserted = map_insert(m, "key2", "value2");
    first = pair_first(inserted);
    second = pair_second(inserted);
    ck_assert(strcmp(first, "key2") == 0);
    ck_assert(strcmp(second, "value2") == 0);

    ck_assert(map_length(m) == 2);
    ck_assert(map_has(m, "key1"));
    ck_assert(map_has(m, "key2"));
    ck_assert(!map_has(m, "key3"));

    map_free(m);
}
END_TEST

START_TEST(test_map_erase) {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");
    ck_assert(map_length(m) == 3);
    ck_assert(map_has(m, "key1"));
    ck_assert(map_has(m, "key2"));
    ck_assert(map_has(m, "key3"));

    map_erase(m, "key1");
    map_erase(m, "key2");
    map_erase(m, "unknown");
    ck_assert(map_length(m) == 1);
    ck_assert(!map_has(m, "key1"));
    ck_assert(!map_has(m, "key2"));
    ck_assert(map_has(m, "key3"));

    map_free(m);
}
END_TEST

Suite* suite_map() {
    Suite *suite = suite_create("map");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_hash_int);
    tcase_add_test(test_case, test_hash_str);
    tcase_add_test(test_case, test_map_init);
    tcase_add_test(test_case, test_map_free);
    tcase_add_test(test_case, test_map_length);
    tcase_add_test(test_case, test_map_is_empty);
    tcase_add_test(test_case, test_map_has);
    tcase_add_test(test_case, test_map_clear);
    tcase_add_test(test_case, test_map_get);
    tcase_add_test(test_case, test_map_insert);
    tcase_add_test(test_case, test_map_erase);
    suite_add_tcase(suite, test_case);
    return suite;
}
