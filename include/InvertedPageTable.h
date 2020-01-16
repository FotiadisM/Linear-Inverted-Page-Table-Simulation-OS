#ifndef INVERTEDPAGETABLE_H
#define INVERTEDPAGETABLE_H

#include "./Address.h"

typedef struct InvertedPageTable {
    size_t size;
    AddressPtr* table;
} InvertedPageTable;

typedef InvertedPageTable* InvertedPageTablePtr;

typedef struct Statistics {
    int reads;
    int writes;
    int pageFaults;
    int cachedPages;
    int pageRequests;
} Statistics;

typedef Statistics* StatisticsPtr;

AddressPtr *InvertedPageTable_getAddress(InvertedPageTablePtr invertedPagetable, Address address);

AddressPtr *InvertedPageTable_getFreeFrame(InvertedPageTablePtr invertedPagetable);

void InvertedPageTable_print(InvertedPageTablePtr invertedPagetable);

void Statistics_Init(StatisticsPtr stats);

#endif