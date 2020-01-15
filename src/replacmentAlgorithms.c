#include <stdlib.h>

#include "../include/replacmentAlgorithms.h"
#include "../include/Queue.h"

int LRU_run(InvertedPageTablePtr invertedPageTable, AddressPtr address) {

    int a = 1;
    Queue q;
    AddressPtr *tmpAddress = NULL;

    if((tmpAddress = InvertedPageTable_getAddress(invertedPageTable, *address)) == NULL) {

        if((tmpAddress = InvertedPageTable_getFreeFrame(invertedPageTable)) == NULL) {

        }
        else {
            *tmpAddress = address;
        }
    }
    else {
        if(address->dirty) {
            (*tmpAddress)->dirty = true;
        }
        free(address);
    }

    Queue_Init(&q, sizeof(int));

    for(int i=0; i < 4; i++) {
        Queue_Insert(&q, &i);
    }

    Queue_Prioritize(&q, &a, compare);

    for(int i=0; i < 4; i++) {
        Queue_Pop(&q, &a);
        printf("%d\n", a);
    }
    printf("\n");

    Queue_Close(&q);

    return 1;
}

int compare(int *a, int *b) {
    if(*a == *b) {
        return 1;
    }
    return 0;
}

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address) {

    

    return 1;
}
