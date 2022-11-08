#include <cmocka.h>

static void null_test_success(void **state) {
    (void) state;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
