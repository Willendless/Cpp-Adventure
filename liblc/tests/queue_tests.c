#include "minunit.h"
#include <lc/queue.h>

char *test_create() {
    Queue *q = Queue_create();
    mu_assert(q != NULL, "Failed to create list");
    return NULL;
}

// TODO: add more tests

char *all_tests() {
    mu_suite_start();
    mu_run_test(test_create);
    return NULL;
}

RUN_TESTS(all_tests);
