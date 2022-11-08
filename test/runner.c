#include <check.h>

#include "test_set.c"
#include "test_vector.c"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main(){
    SRunner *sr = srunner_create(suite_create(""));

    // creates and adds the module test suites to the suite runner
    Suite* suites[] = {
        test_set_suite(),
        test_vector_suite()
    };
    int suites_len = sizeof(suites) / sizeof(suites[0]);
    for (int i = 0; i < suites_len; i++) {
        srunner_add_suite(sr, suites[i]);
    }

    // runs all test suites and checks for failures
    srunner_run_all(sr, CK_VERBOSE);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
