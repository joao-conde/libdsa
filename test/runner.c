#include <check.h>

#include "test_set.c"
#include "test_vector.c"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main(){
    // creates and adds the module test suites to the suite runner
    SRunner *sr = srunner_create(suite_create(""));
    srunner_add_suite(sr, test_set_suite());
    srunner_add_suite(sr, test_vector_suite());

    // runs all test suites and checks for failures
    srunner_run_all(sr, CK_VERBOSE);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
