#include <lc/debug.h>
#include <lc/list.h>
#include <assert.h>

List *List_create() {
    return calloc(1, sizeof(List));
}

void List_destroy(List *list) {
    assert(list != NULL && "input list cannot be null");

    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);
}

void List_clear(List *list) {
    assert(list != NULL && "input list cannot be null");

    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List *list) {
    assert(list != NULL && "input list cannot be null");

    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        if (cur -> prev) {
            free(cur->prev);
        }
    }
}

void List_push(List *list, void *value) {
    assert(list != NULL && "input list cannot be null");

    ListNode *n = calloc(1, sizeof(ListNode));
    check_mem(n);

    n->value = value;

    if (list->last == NULL) {
        list->first = list->last = n;
    } else {
        n->prev = list->last;
        list->last->next = n;
        list->last = n;
    }

    ++list->count;

error:
    return;
}

void *List_pop(List *list) {
    assert(list != NULL && "input list cannot be null");
    
    ListNode *n = list->last;
    return n == NULL? NULL : List_remove(list, n);
}

void List_unshift(List *list, void *value) {
    assert(list != NULL && "input list cannot be null");

    ListNode *n = calloc(1, sizeof(ListNode));
    check_mem(n);

    n->value = value;

    if (list->first == NULL) {
        list->first = list->last = n;
    } else {
        n->next = list->first;
        list->first->prev = n;
        list->first = n;
    }

    ++list->count;

error:
    return;
}

void *List_shift(List *list) {
    assert(list != NULL && "input list cannot be null");

    ListNode *n = list->first;
    return n == NULL? NULL : List_remove(list, n);
}

void *List_remove(List *list, ListNode *node) {
    assert(list != NULL && "input list cannot be null");

    ListNode *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be null");

    if (list->first == node && list->last == node) {
        list->first = list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid non-empty list, NULL first")
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid non-empty list, NULL last")
        list->last->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    --list->count;
    result = node->value;
    free(node);

error:
    return result;
}

void List_insert(List *list, ListNode *next, void *value) {
    assert(list != NULL && "Input list cannot be null.");
    assert(next != NULL && "Next node cannot be null.");

    ListNode *n = calloc(1, sizeof(ListNode));
    n->value = value;
    n->next = next;
    n->prev = next->prev;

    if (n->prev == NULL) {
        check(List_begin(list) == next, "Bad list or bad next node.");
        list->first = n;
    } else
        n->prev->next = n;
    n->next->prev = n;

    return;

error:
    free(n);
    return;
}
