#include <stdlib.h>
#include <string.h>
#include "../include/Queue.h"

void Queue_Init(QueuePtr queue, size_t dataSize) {

    queue->sizeOfQueue = 0;
    queue->dataSize = dataSize;
    queue->head = NULL;
    queue->tail = NULL;
}

int Queue_Insert(QueuePtr queue, void *data) {

    Queue_nodePtr newNode = NULL;

    if((newNode = malloc(sizeof(Queue_node))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if((newNode->data = malloc(queue->dataSize)) == NULL) {
        perror("malloc failed");
        return -1;
    }

    newNode->next = NULL;
    memcpy(newNode->data, data, queue->dataSize);

    if(queue->sizeOfQueue) {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    else {
        queue->head = newNode;
        queue->tail = newNode;
    }

    queue->sizeOfQueue++;

    return 1;
}

void Queue_Pop(QueuePtr queue, void *data) {

    Queue_nodePtr tmpNode = NULL;

    if(queue->sizeOfQueue) {
        tmpNode = queue->head;

        memcpy(data, tmpNode->data, queue->dataSize);

        queue->sizeOfQueue--;

        if(queue->sizeOfQueue) {
            queue->head = queue->head->next;
        }
        else {
            queue->head = NULL;
            queue->tail = NULL;
        }

        free(tmpNode->data);
        free(tmpNode);
    }
}

void Queue_Prioritize(QueuePtr queue, void *data, int (*function)()) {

    Queue_nodePtr fastPtr = NULL;
    Queue_nodePtr slowPtr = NULL;

    fastPtr = queue->head;
    for(int i=0; i < queue->sizeOfQueue; i++) {
        if(fastPtr->data == NULL) {
            printf("WHATUP/");
        }

        // printf("ad1: %p, ad2: %p\n", fastPtr->data, data);
        if(function(fastPtr->data, data)) {
            printf("i: %d\n", i);
            if(fastPtr->next == NULL) {
                return;
            }
            else if(i) {
                slowPtr->next = fastPtr->next;
            }
            else {
                queue->head = fastPtr->next;
            }
            queue->tail->next = fastPtr;
            queue->tail = fastPtr;
            fastPtr->next = NULL;

            return;
        }
        slowPtr = fastPtr;
        fastPtr = fastPtr->next;
    }
}

void Queue_Print(QueuePtr queue, void (*function)()) {

    Queue_nodePtr tmpNode = NULL;

    tmpNode = queue->head;
    for(int i=0; i < queue->sizeOfQueue; i++) {
        function(tmpNode->data, tmpNode->data);
        tmpNode = tmpNode->next;
    }
}

void Queue_Close(QueuePtr queue) {

    Queue_nodePtr tmpNode = NULL;

    for(int i=0; i < queue->sizeOfQueue; i++) {
        tmpNode = queue->head;
        queue->head = queue->head->next;

        free(tmpNode->data);
        free(tmpNode);
    }
}