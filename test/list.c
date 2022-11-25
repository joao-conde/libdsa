#include <check.h>

#include "../include/list.h"

START_TEST(test_list_init) {
    list *l = list_init(sizeof(int));
    ck_assert(list_is_empty(l));
    list_free(l);
}
END_TEST

START_TEST(test_list_free) {
    list_free(NULL);

    list *l = list_init(sizeof(int));
    list_free(l);
}
END_TEST

START_TEST(test_list_length) {
    float value = 3.5;
    list *l = list_init(sizeof(float));
    ck_assert(list_length(l) == 0);

    list_push_back(l, &value);
    list_push_back(l, &value);
    list_push_back(l, &value);
    ck_assert(list_length(l) == 3);

    list_free(l);
}
END_TEST

START_TEST(test_list_is_empty) {
    list *l = list_init(sizeof(int));
    ck_assert(list_is_empty(l));

    int value = -10;
    list_push_back(l, &value);
    ck_assert(!list_is_empty(l));

    list_pop_front(l);
    ck_assert(list_is_empty(l));

    list_free(l);
}
END_TEST

START_TEST(test_list_front) {
    int values[4] = {-1, 10, 24, 59};
    list *l = list_init(sizeof(int));

    ck_assert(list_front(l) == NULL);

    list_push_back(l, &values[0]);
    ck_assert(*(int*) list_front(l) == -1);

    list_push_back(l, &values[1]);
    ck_assert(*(int*) list_front(l) == -1);

    list_push_front(l, &values[2]);
    ck_assert(*(int*) list_front(l) == 24);

    list_push_front(l, &values[3]);
    ck_assert(*(int*) list_front(l) == 59);

    list_pop_back(l);
    ck_assert(*(int*) list_front(l) == 59);

    list_pop_front(l);
    ck_assert(*(int*) list_front(l) == 24);

    list_pop_front(l);
    ck_assert(*(int*) list_front(l) == -1);

    list_pop_front(l);
    ck_assert(list_front(l) == NULL);

    list_free(l);
}
END_TEST

START_TEST(test_list_back) {
    int values[4] = {-1, 10, 24, 59};
    list *l = list_init(sizeof(int));

    ck_assert(list_back(l) == NULL);

    list_push_front(l, &values[0]);
    ck_assert(*(int*) list_back(l) == -1);

    list_push_front(l, &values[1]);
    ck_assert(*(int*) list_back(l) == -1);

    list_push_back(l, &values[2]);
    ck_assert(*(int*) list_back(l) == 24);

    list_push_back(l, &values[3]);
    ck_assert(*(int*) list_back(l) == 59);

    list_pop_front(l);
    ck_assert(*(int*) list_back(l) == 59);

    list_pop_back(l);
    ck_assert(*(int*) list_back(l) == 24);

    list_pop_back(l);
    ck_assert(*(int*) list_back(l) == -1);

    list_pop_back(l);
    ck_assert(list_back(l) == NULL);

    list_free(l);
}
END_TEST

START_TEST(test_list_pointers) {
    list *l = list_init(sizeof(int));
    ck_assert(list_front(l) == list_back(l));

    int value = 3;
    list_push_front(l, &value);
    ck_assert(list_front(l) == list_back(l));

    list_push_front(l, &value);
    ck_assert(list_front(l) != list_back(l));

    list_pop_back(l);
    ck_assert(list_front(l) == list_back(l));

    list_free(l);
}
END_TEST

Suite* suite_list() {
    Suite *suite = suite_create("list");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_list_init);
    tcase_add_test(test_case, test_list_free);
    tcase_add_test(test_case, test_list_length);
    tcase_add_test(test_case, test_list_is_empty);
    tcase_add_test(test_case, test_list_front);
    tcase_add_test(test_case, test_list_back);
    tcase_add_test(test_case, test_list_pointers);
    suite_add_tcase(suite, test_case);
    return suite;
}
