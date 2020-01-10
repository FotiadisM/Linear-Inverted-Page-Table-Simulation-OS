#ifndef INVERTEDPAGETABLE_H
#define INVERTEDPAGETABLE_H

#include "./Address.h"

typedef struct InvertedPageTable {
    size_t size;
    AddressPtr* table;
} InvertedPageTable;

typedef InvertedPageTable* InvertedPageTablePtr;

AddressPtr InvertedPageTable_getAddress(InvertedPageTablePtr invertedPagetable, size_t size, AddressPtr address);

#endif