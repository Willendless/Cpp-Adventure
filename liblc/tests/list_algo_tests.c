#include <lc/list_algo.h>
#include "minunit.h"
#include <assert.h>
#include <string.h>

char *values[] = {"xxxx", "1234", "abcd", "xjvef", "NDSS"};

#define NUM_VALUES 5

static List *create_words() {
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; ++i) {
        List_push(words, values[i]);
    }
    return words;
}

static int is_sorted(List *words) {
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            LIST_FOREACH(words, first, next, cur) {
                debug("%s ", (char *)(cur->value));
            }
            return 0;
        }
    }
    return 1;
}

static char *test_bubblesort() {
    List *words = create_words();

    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on sorted list.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    List_destroy(words);

    // empty list
    words = List_create();
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    List_destroy(words);
    return NULL;
}

static char *test_mergesort() {
    List *words = create_words();

    int rc = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Merge sort failed");
    mu_assert(is_sorted(words), "Words are not sorted after merge sort.");

    // sorted list
    rc = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Merge sort failed on sorted list.");
    mu_assert(is_sorted(words), "Words are not sorted after Merge sort.");

    List_destroy(words);

    // empty list
    words = List_create();
    rc = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Merge sort failed on empty list.");
    mu_assert(is_sorted(words), "Words are not sorted after Merge sort.");

    List_destroy(words);
    return NULL;
}

static char *all_tests() {
    mu_suite_start();
    mu_run_test(test_bubblesort);
    mu_run_test(test_mergesort);
    return NULL;
}

RUN_TESTS(all_tests);
