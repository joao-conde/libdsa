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
    ck_assert(*(int*) list_front(l)->data == -1);

    list_push_back(l, &values[1]);
    ck_assert(*(int*) list_front(l)->data == -1);

    list_push_front(l, &values[2]);
    ck_assert(*(int*) list_front(l)->data == 24);

    list_push_front(l, &values[3]);
    ck_assert(*(int*) list_front(l)->data == 59);

    list_pop_back(l);
    ck_assert(*(int*) list_front(l)->data == 59);

    list_pop_front(l);
    ck_assert(*(int*) list_front(l)->data == 24);

    list_pop_front(l);
    ck_assert(*(int*) list_front(l)->data == -1);

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
    ck_assert(*(int*) list_back(l)->data == -1);

    list_push_front(l, &values[1]);
    ck_assert(*(int*) list_back(l)->data == -1);

    list_push_back(l, &values[2]);
    ck_assert(*(int*) list_back(l)->data == 24);

    list_push_back(l, &values[3]);
    ck_assert(*(int*) list_back(l)->data == 59);

    list_pop_front(l);
    ck_assert(*(int*) list_back(l)->data == 59);

    list_pop_back(l);
    ck_assert(*(int*) list_back(l)->data == 24);

    list_pop_back(l);
    ck_assert(*(int*) list_back(l)->data == -1);

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

START_TEST(test_list_push_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));

    result = list_push_back(l, &values[0])->data;
    ck_assert(*result == 51);

    result = list_push_back(l, &values[1])->data;
    ck_assert(*result == 12);

    result = list_push_back(l, &values[2])->data;
    ck_assert(*result == -123);

    result = list_push_back(l, &values[3])->data;
    ck_assert(*result == 1000);

    result = list_push_back(l, &values[4])->data;
    ck_assert(*result == -1);

    ck_assert(list_length(l) == 5);

    list_free(l);
}
END_TEST

START_TEST(test_list_push_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));

    result = list_push_front(l, &values[0])->data;
    ck_assert(*result == 51);

    result = list_push_front(l, &values[1])->data;
    ck_assert(*result == 12);

    result = list_push_front(l, &values[2])->data;
    ck_assert(*result == -123);

    result = list_push_front(l, &values[3])->data;
    ck_assert(*result == 1000);

    result = list_push_front(l, &values[4])->data;
    ck_assert(*result == -1);

    ck_assert(list_length(l) == 5);

    list_free(l);
}
END_TEST

START_TEST(test_list_pop_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    list_push_back(l, &values[4]);

    result = list_back(l)->data;
    ck_assert(*result == -1);
    ck_assert(list_length(l) == 5);

    list_pop_back(l);
    result = list_back(l)->data;
    ck_assert(*result == 1000);
    ck_assert(list_length(l) == 4);

    list_pop_back(l);
    result = list_back(l)->data;
    ck_assert(*result == -123);
    ck_assert(list_length(l) == 3);

    list_pop_back(l);
    result = list_back(l)->data;
    ck_assert(*result == 12);
    ck_assert(list_length(l) == 2);

    list_pop_back(l);
    result = list_back(l)->data;
    ck_assert(*result == 51);
    ck_assert(list_length(l) == 1);

    list_pop_back(l);
    ck_assert(list_back(l) == NULL);
    ck_assert(list_length(l) == 0);

    list_free(l);
}
END_TEST

START_TEST(test_list_pop_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));
    list_push_front(l, &values[0]);
    list_push_front(l, &values[1]);
    list_push_front(l, &values[2]);
    list_push_front(l, &values[3]);
    list_push_front(l, &values[4]);

    result = list_front(l)->data;
    ck_assert(*result == -1);
    ck_assert(list_length(l) == 5);

    list_pop_front(l);
    result = list_front(l)->data;
    ck_assert(*result == 1000);
    ck_assert(list_length(l) == 4);

    list_pop_front(l);
    result = list_front(l)->data;
    ck_assert(*result == -123);
    ck_assert(list_length(l) == 3);

    list_pop_front(l);
    result = list_front(l)->data;
    ck_assert(*result == 12);
    ck_assert(list_length(l) == 2);

    list_pop_front(l);
    result = list_front(l)->data;
    ck_assert(*result == 51);
    ck_assert(list_length(l) == 1);

    list_pop_front(l);
    ck_assert(list_front(l) == NULL);
    ck_assert(list_length(l) == 0);

    list_free(l);
}
END_TEST

START_TEST(test_list_insert) {
    int values[4] = {15, 21, 30, 69};
    list *l = list_init(sizeof(int));
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    ck_assert(list_length(l) == 4);

    node *inserted, *prev, *next, *front, *back;

    front = list_front(l);
    back = list_back(l);
    prev = front;
    next = prev->next;
    inserted = list_insert(l, front, &values[0]);
    ck_assert(prev->next == inserted);
    ck_assert(next->prev == inserted);
    ck_assert(inserted->prev == prev);
    ck_assert(inserted->next == next);
    ck_assert(list_length(l) == 5);
    ck_assert(list_front(l) == front);
    ck_assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    prev = front->next->next;
    next = prev->next;
    inserted = list_insert(l, prev, &values[0]);
    ck_assert(prev->next == inserted);
    ck_assert(next->prev == inserted);
    ck_assert(inserted->prev == prev);
    ck_assert(inserted->next == next);
    ck_assert(list_length(l) == 6);
    ck_assert(list_front(l) == front);
    ck_assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    prev = back;
    inserted = list_insert(l, prev, &values[0]);
    ck_assert(back->next == inserted);
    ck_assert(inserted->prev == prev);
    ck_assert(inserted->next == NULL);
    ck_assert(list_length(l) == 7);
    ck_assert(list_front(l) == front);
    ck_assert(list_back(l) == inserted);

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
    tcase_add_test(test_case, test_list_push_back);
    tcase_add_test(test_case, test_list_push_front);
    tcase_add_test(test_case, test_list_pop_back);
    tcase_add_test(test_case, test_list_pop_front);
    tcase_add_test(test_case, test_list_insert);
    suite_add_tcase(suite, test_case);
    return suite;
}
