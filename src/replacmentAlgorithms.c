#include <stdlib.h>
#include "../include/replacmentAlgorithms.h"

int LRU_run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats) {

    AddressPtr *tmpAddress = NULL;

    // AddressPtr mAddress = NULL, tAddress = NULL;

    // mAddress = malloc(sizeof(Address));

    // mAddress->pageNumber = 1234;

    // printf("%p, %p\n", &mAddress, mAddress);
    // printf("%p, %p\n", &tmpAddress, tmpAddress);
    // printf("%p, %p\n\n", &tAddress, tAddress);


    // tmpAddress = &tAddress;
    // *tmpAddress = mAddress;

    // printf("%p, %p, %p, %ld\n", tmpAddress, *tmpAddress, tAddress, tAddress->pageNumber);


    // Queue_Insert(mStruct->lru.queue, &tmpAddress);
    // Queue_Print(mStruct->lru.queue, print_Address);

    // tmpAddress = NULL;
    // printf("%p\n", tmpAddress);

    // Queue_Pop(mStruct->lru.queue, &tmpAddress);
    // printf("%p, %p, %p, %ld\n", tmpAddress, *tmpAddress, tAddress, tAddress->pageNumber);


    // free(mAddress);
    stats->pageRequests++;

    if(address->dirty)
        stats->writes++;
    else
        stats->reads++;

    if((tmpAddress = InvertedPageTable_getAddress(invertedPageTable, *address)) == NULL) {

        stats->pageFaults++;
        if((tmpAddress = InvertedPageTable_getFreeFrame(invertedPageTable)) == NULL) {
            Queue_Pop(mStruct->lru.queue, &tmpAddress);;
            free(*tmpAddress);
            *tmpAddress = address;;
            Queue_Insert(mStruct->lru.queue, &tmpAddress);
        }
        else {
            *tmpAddress = address;
            Queue_Insert(mStruct->lru.queue, &tmpAddress);
        }
    }
    else {
        Queue_Prioritize(mStruct->lru.queue, &tmpAddress, compare_Addresses);
        stats->cachedPages++;
        if(address->dirty) {
            (*tmpAddress)->dirty = true;
        }
        free(address);
    }
    // Queue_Print(mStruct->lru.queue, print_Address);

    return 1;
}

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address) {

    

    return 1;
}

int compare_Addresses(AddressPtr* address1, AddressPtr* address2) {

    // if(*address1 == *address2) {
    //     printf("ela dike mou");
    //     return 1;
    // }

    return 0;
}
