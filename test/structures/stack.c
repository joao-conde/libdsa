#include <check.h>
#include <stdint.h>

#include "../../include/stack.h"

START_TEST(test_stack_init) {
    stack *s = stack_init(sizeof(int));
    ck_assert(s != NULL);
    stack_free(s);
}
END_TEST

START_TEST(test_stack_init_fail) {
    stack *s = stack_init(SIZE_MAX);
    ck_assert(s == NULL);
}
END_TEST

START_TEST(test_stack_free) {
    stack_free(NULL);

    stack *s = stack_init(sizeof(int));
    stack_free(s);
}
END_TEST

START_TEST(test_stack_length) {
    float value = 3.5;
    stack *s = stack_init(sizeof(float));
    ck_assert(stack_length(s) == 0);

    stack_push(s, &value);
    stack_push(s, &value);
    stack_push(s, &value);
    ck_assert(stack_length(s) == 3);

    stack_free(s);
}
END_TEST

START_TEST(test_stack_is_empty) {
    stack *s = stack_init(sizeof(int));
    ck_assert(stack_is_empty(s) == true);

    int value = -10;
    stack_push(s, &value);
    ck_assert(stack_is_empty(s) == false);

    stack_pop(s);
    ck_assert(stack_is_empty(s) == true);

    stack_free(s);
}
END_TEST

START_TEST(test_stack_top) {
    int values[4] = { -1, 10, 24, 59 };
    stack *s = stack_init(sizeof(int));

    ck_assert(stack_top(s) == NULL);

    stack_push(s, &values[0]);
    ck_assert(*(int*) stack_top(s) == -1);

    stack_push(s, &values[1]);
    ck_assert(*(int*) stack_top(s) == 10);

    stack_push(s, &values[2]);
    ck_assert(*(int*) stack_top(s) == 24);

    stack_push(s, &values[3]);
    ck_assert(*(int*) stack_top(s) == 59);

    stack_pop(s);
    ck_assert(*(int*) stack_top(s) == 24);

    stack_pop(s);
    ck_assert(*(int*) stack_top(s) == 10);

    stack_pop(s);
    ck_assert(*(int*) stack_top(s) == -1);

    stack_pop(s);
    ck_assert(stack_top(s) == NULL);

    stack_free(s);
}
END_TEST

START_TEST(test_stack_push) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    stack *s = stack_init(sizeof(int));

    result = stack_push(s, &values[0]);
    ck_assert(*result == 51);

    result = stack_push(s, &values[1]);
    ck_assert(*result == 12);

    result = stack_push(s, &values[2]);
    ck_assert(*result == -123);

    result = stack_push(s, &values[3]);
    ck_assert(*result == 1000);

    result = stack_push(s, &values[4]);
    ck_assert(*result == -1);

    ck_assert(stack_length(s) == 5);

    stack_free(s);
}
END_TEST

START_TEST(test_stack_pop) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    stack *s = stack_init(sizeof(int));
    stack_push(s, &values[0]);
    stack_push(s, &values[1]);
    stack_push(s, &values[2]);
    stack_push(s, &values[3]);
    stack_push(s, &values[4]);

    ck_assert(stack_length(s) == 5);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 4);
    ck_assert(*result == -1);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 3);
    ck_assert(*result == 1000);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 2);
    ck_assert(*result == -123);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 1);
    ck_assert(*result == 12);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 0);
    ck_assert(*result == 51);

    result = stack_pop(s);
    ck_assert(stack_length(s) == 0);
    ck_assert(result == NULL);

    stack_free(s);
}
END_TEST

Suite* suite_stack() {
    Suite *suite = suite_create("stack");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_stack_init);
    tcase_add_test(test_case, test_stack_init_fail);
    tcase_add_test(test_case, test_stack_free);
    tcase_add_test(test_case, test_stack_length);
    tcase_add_test(test_case, test_stack_is_empty);
    tcase_add_test(test_case, test_stack_top);
    tcase_add_test(test_case, test_stack_push);
    tcase_add_test(test_case, test_stack_pop);
    suite_add_tcase(suite, test_case);
    return suite;
}
