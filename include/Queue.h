#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

typedef struct Queue_node {
    void *data;
    struct Queue_node *next;
} Queue_node;

typedef Queue_node* Queue_nodePtr;

typedef struct Queue {
    int sizeOfQueue;
    size_t dataSize;
    Queue_nodePtr head;
    Queue_nodePtr tail;
} Queue;

typedef Queue* QueuePtr;

void Queue_Init(QueuePtr queue, size_t dataSize);

int Queue_Insert(QueuePtr queue, void *data);

void Queue_Pop(QueuePtr queue, void *data);

void Queue_Prioritize(QueuePtr queue, void *data, int (*function)());

void Queue_Close(QueuePtr queue);

#endif