#include <lc/list_algo.h>
#include <assert.h>
#include <lc/debug.h>

static void swap(ListNode* n1, ListNode* n2) {
    void* t = n1->value;
    n1->value = n2->value;
    n2->value = t;
}

int List_bubble_sort(List *list, List_compare cmp) {
    assert(list != NULL && "List cannot be null.");

    int i;
    ListNode *n, *e;

    e = List_end(list);
    for (i = 0; i < list->count - 1; ++i) {
        n = List_begin(list);
        for (; n != e; n = n->next) {
            if (n->value == NULL
                || n->next->value == NULL) {
                return 1;
            }
            if (cmp(n->value, n->next->value) > 0) {
                swap(n, n->next);
            }
        }
        e = e->prev;
    }

    return 0;
}

static ListNode *find_end_of_run(ListNode *n, List_compare cmp) {
    assert(n != NULL);

    while (n->next != NULL) {
        if (n->value == NULL
            || n->next->value == NULL)
            return NULL;
        if (cmp(n->value, n->next->value) > 0)
            break;
        n = n->next;
    }
    return n;
}

/**
 * Inplace merge adjunct sublist.
 * both a1 and b1 are exclusive.
 */
static void list_inplace_merge(List *list, ListNode *a0, ListNode *a1b0, ListNode * b1, List_compare cmp) {
    assert(a0 != NULL);
    assert(a1b0 != NULL);
    assert(b1 != NULL);

    while (a0 != a1b0 && a1b0 != b1) {
        if (cmp(a0->value, a1b0->value) <= 0) {
            a0 = a0->next;
        } else {
            ListNode *t = a1b0;
            a1b0 = a1b0->next;
            void *v = List_remove(list, t);
            List_insert(list, a0, v);
        }
    }
}

/**
 * Interative merge sort that runs in O(nlogn) time and O(1) space.
 */
int List_merge_sort(List *list, List_compare cmp) {
    assert(list != NULL && "List cannot be null.");

    int runs_left_cnt;
    ListNode *a0, *a1b0, *b1;

    do {
        runs_left_cnt = 0;
        for (a0 = List_begin(list); a0 != NULL; a0 = b1->next) {
            runs_left_cnt++; // each iteration produces one run.
            a1b0 = find_end_of_run(a0, cmp);
            if (a1b0 == NULL) {
                return 1;
            } else if (a1b0 == List_end(list)) {
                break;
            }
            b1 = find_end_of_run(a1b0->next, cmp);
            if (b1 == NULL) {
                return 1;
            }
            list_inplace_merge(list, a0, a1b0->next, b1->next, cmp);
        }
    } while (runs_left_cnt > 1);

    return 0;
}
