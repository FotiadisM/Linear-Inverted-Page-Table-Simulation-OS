#include <stdlib.h>
#include "../include/InvertedPageTable.h"

AddressPtr *InvertedPageTable_getAddress(InvertedPageTablePtr invertedPagetable, Address address) {


    for(size_t i=0; i < invertedPagetable->size; i++) {
        if(invertedPagetable->table[i] != NULL) {
            if(Address_equals(*(invertedPagetable->table[i]), address)) {
                return &invertedPagetable->table[i];
            }
        }
    }

    return NULL;
}

AddressPtr *InvertedPageTable_getFreeFrame(InvertedPageTablePtr invertedPagetable) {

    for(size_t i=0; i < invertedPagetable->size; i++) {
        if(invertedPagetable->table[i] == NULL) {
            return &invertedPagetable->table[i];

        }
    }

    return NULL;
}

void InvertedPageTable_print(InvertedPageTablePtr invertedPagetable) {

    for(int i=0; i < invertedPagetable->size; i++) {
        if(invertedPagetable->table[i] == NULL) {
            printf("\tNULL\n");
        }
        else {
            Address_print(*(invertedPagetable->table[i]));
        }
    }
}

void Statistics_Init(StatisticsPtr stats) {
    stats->reads = 0;
    stats->writes = 0;
    stats->pageFaults = 0;
    stats->cachedPages = 0;
    stats->pageRequests = 0;
}