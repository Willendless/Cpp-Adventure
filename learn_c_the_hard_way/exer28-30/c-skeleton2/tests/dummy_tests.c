#include "minunit.h"

char *dummy_test() {
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(dummy_test);
    return NULL;
}

RUN_TESTS(all_tests);
