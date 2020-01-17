#include <stdlib.h>
#include "../include/replacmentAlgorithms.h"

int LRU_Init(CashePtr mStruct) {
    if((mStruct->lru.queue = malloc(sizeof(Queue))) == NULL) {
        perror("malloc failed");
        return -1;
    }
    Queue_Init(mStruct->lru.queue, sizeof(AddressPtr)); // sizeof(AddressPtr *) == sizeof(AddressPtr)

    return 0;
}

void LRU_Close(CashePtr mStruct) {
    Queue_Close(mStruct->lru.queue);
    free(mStruct->lru.queue);
}

int LRU_Run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats) {

    AddressPtr *tmpAddress = NULL;

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

    return 1;
}

int WS_Init(CashePtr mStruct, int maxWorkingSet) {

    if((mStruct->ws.workingSet = malloc(NUMBER_OF_PIDS * sizeof(WSPtr))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    for(int i=0; i < NUMBER_OF_PIDS; i++) {
        if((mStruct->ws.workingSet[i] = malloc(sizeof(WS))) == NULL) {
            perror("malloc failed");
            return -1;
        }
        if((mStruct->ws.workingSet[i]->queue = malloc(sizeof(Queue))) == NULL) {
            perror("malloc failed");
            return -1;
        }
        Queue_Init(mStruct->ws.workingSet[i]->queue, sizeof(AddressPtr));
    }

    mStruct->ws.maxWorkingSet = maxWorkingSet;

    return 0;
}

void WS_Close(CashePtr mStruct) {

    for(int i=0; i < NUMBER_OF_PIDS; i++) {
        Queue_Close(mStruct->ws.workingSet[i]->queue);
        free(mStruct->ws.workingSet[i]->queue);
        free(mStruct->ws.workingSet[i]);
    }

    free(mStruct->ws.workingSet);
}

int WS_Run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats) {

    AddressPtr *tmpAddress = NULL;
    AddressPtr *killedNode = NULL;

    stats->pageRequests++;

    if(address->dirty)
        stats->writes++;
    else
        stats->reads++;

     if((tmpAddress = InvertedPageTable_getAddress(invertedPageTable, *address)) == NULL) {

        if((tmpAddress = InvertedPageTable_getFreeFrame(invertedPageTable)) == NULL) {

            stats->pageFaults++;
            for(int i=0; i < invertedPageTable->size; i++) {
                tmpAddress = &invertedPageTable->table[i];
                if(!Queue_Exist(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress, compare_Addresses)) {
                    free(*tmpAddress);
                    *tmpAddress = address;
                    if(mStruct->ws.workingSet[address->pid - 1]->queue->sizeOfQueue <= mStruct->ws.maxWorkingSet) {
                        Queue_Insert(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress);
                    }
                    else {
                        Queue_Pop(mStruct->ws.workingSet[address->pid - 1]->queue, &killedNode);
                        Queue_Insert(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress);
                    }
                    break;
                }
                
            }
        }
        else {
            *tmpAddress = address;
            if(mStruct->ws.workingSet[address->pid - 1]->queue->sizeOfQueue <= mStruct->ws.maxWorkingSet) {
                Queue_Insert(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress);
            }
            else {
                Queue_Pop(mStruct->ws.workingSet[address->pid - 1]->queue, &killedNode);
                Queue_Insert(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress);
            }
        }
    }
    else {
        Queue_Prioritize(mStruct->ws.workingSet[address->pid - 1]->queue, &tmpAddress, compare_Addresses);
        stats->cachedPages++;
        if(address->dirty) {
            (*tmpAddress)->dirty = true;
        }
        free(address);
    }

    return 1;
}

int compare_Addresses(AddressPtr* address1, AddressPtr* address2) {

    if(*address1 == *address2) {
        return 1;
    }

    return 0;
}