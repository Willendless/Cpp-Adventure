//
// an attempt to implement lock-free queue
//
#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Queue *Queue_create() {
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    QueueNode *n = (QueueNode *)calloc(1, sizeof(QueueNode));
    n->next = NULL;
    q->head = q->tail = n;
    return q;
}

/**
 * Queue_enqueue:
 *  -Version 1
 *   if a thread died before set q->tail,
 *   then other threads cannot move forward.
 */ 
// void Queue_enqueue(Queue *q, void *value) {
//     QueueNode *old;
//     QueueNode *n = (QueueNode *)calloc(1, sizeof(QueueNode));
//     n->value = value;
//     do {
//         old = q->tail;
//     } while (!__sync_bool_compare_and_swap(&(old->next), 0, n));
//     // only one thread can reach here
//     // since tail pointers of other threads
//     // are still pointing to the old tail.
//     q->tail = n;
// }

/**
 * Queue_enqueue:
 *  -Version 2
 *  since we don't know whether or when the stuck thread will come back
 *  we cannot modify the Queue.tail, but still need to lengthen the queue
 */ 
// void Queue_enqueue(Queue *q, void *value) {
//     QueueNode *old;
//     QueueNode *n = (QueueNode *)calloc(1, sizeof(QueueNode));
//     n->value = value;
//     do {
//         old = q->tail;
//         while (old->next != NULL) {
//             old = old->next;
//         }
//     } while (!__sync_bool_compare_and_swap(&(old->next), NULL, n));
//     // only one thread can reach here
//     // since tail pointers of other threads
//     // are still pointing to the old tail.
//     q->tail = n;
// }

/**
 * Queue_enqueue:
 *  -Version 3
 *  grant other thread the permission to modify the Queue.tail,
 *  but need coordination mechanism.
 */ 
void Queue_enqueue(Queue *q, void *value) {
    QueueNode *old, *next;
    QueueNode *n = (QueueNode *)calloc(1, sizeof(QueueNode));
    n->value = value;
    do {
        old = q->tail;
        next = old->next;

        if (old != q->tail) {
            // another thread has finished data enqueue
            // after cur thread's tail read
            continue;
        }

        if (next != NULL) {
            // another thread has enqued but
            // not set Queue.tail yet
            __sync_bool_compare_and_swap(&(q->tail), old, next);
            continue;
        }

    } while (!__sync_bool_compare_and_swap(&(old->next), NULL, n));
    // only one thread can reach here
    // since tail pointers of other threads
    // are still pointing to the old tail.
    q->tail = n;
}

/**
 * Queuue_dequeue:
 *  -Version 1
 *   This version still suffer ABA problem.
 */
void *Queue_dequeue(Queue *q) {
    QueueNode *old;
    void *ret;

    do {
        old = q->head;
        ret = old->next->value;
        if (old->next == NULL) {
            // empty queue
            return NULL;
        }
    } while(!__sync_bool_compare_and_swap(&(q->head), old, old->next));

    free(old);
    return ret;
}

// int main() {
//     Queue *q = Queue_create();

//     Queue_enqueue(q, "My future1.");
//     Queue_enqueue(q, "My future2.");
//     Queue_enqueue(q, "My future3.");
//     Queue_enqueue(q, "My future4.");
//     Queue_enqueue(q, "My future5.");
//     printf("%s\n", (char *)Queue_dequeue(q));
//     printf("%s\n", (char *)Queue_dequeue(q));
//     printf("%s\n", (char *)Queue_dequeue(q));
//     printf("%s\n", (char *)Queue_dequeue(q));
//     printf("%s\n", (char *)Queue_dequeue(q));

//     return 0;
// }
