#include "minunit.h"
#include <lc/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create() {
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");
    return NULL;
}

char *test_destory() {
    List_clear_destroy(list);
    return NULL;
}

char *test_push_pop() {
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");
    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");
    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift() {
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong first value");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove() {
    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed value.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    return NULL;
}

char *test_shift() {
    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");
    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count before shift.");
    return NULL;
}

char *all_test() {
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_destory);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    return NULL;
}

RUN_TESTS(all_test);
