#ifndef INVERTEDPAGETABLE_H
#define INVERTEDPAGETABLE_H

#include "./Address.h"

typedef struct InvertedPageTable {
    size_t size;
    AddressPtr* table;
} InvertedPageTable;

typedef InvertedPageTable* InvertedPageTablePtr;

AddressPtr *InvertedPageTable_getAddress(InvertedPageTablePtr invertedPagetable, Address address);
AddressPtr *InvertedPageTable_getFreeTrace(InvertedPageTablePtr invertedPagetable);

void InvertedPageTable_print(InvertedPageTablePtr invertedPagetable);

#endif