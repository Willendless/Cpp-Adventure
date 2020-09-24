#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode{
    void *value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
} Queue;

Queue *Queue_create();

void Queue_enqueue(Queue *q, void *n);
void *Queue_dequeue(Queue *q);

#endif
