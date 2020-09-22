#ifndef LIST_ALGO_H
#define LIST_ALGO_H

#include <lc/list.h>

typedef int (*List_compare) (const void *a, const void *b);
int List_bubble_sort(List *list, List_compare cmp);
int List_merge_sort(List *list, List_compare cmp);

#endif
