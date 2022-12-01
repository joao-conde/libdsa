#include <check.h>

#include "./deque.c"
#include "./list.c"
#include "./map.c"
#include "./pair.c"
#include "./queue.c"
#include "./stack.c"
#include "./vector.c"

#define SUITE_NAME "libdsa"
#define SUITE_SUCCESS 0
#define SUITE_FAILURE -1

int main() {
    // creates and adds the module test suites to the suite runner
    SRunner *sr = srunner_create(suite_create(SUITE_NAME));
    srunner_add_suite(sr, suite_deque());
    srunner_add_suite(sr, suite_list());
    srunner_add_suite(sr, suite_map());
    srunner_add_suite(sr, suite_pair());
    srunner_add_suite(sr, suite_queue());
    srunner_add_suite(sr, suite_stack());
    srunner_add_suite(sr, suite_vector());

    // runs all test suites and checks for failures
    srunner_run_all(sr, CK_VERBOSE);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? SUITE_SUCCESS : SUITE_FAILURE;
}
