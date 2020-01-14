#ifndef RPALGO_H
#define RPALGO_H

#include "./InvertedPageTable.h"

typedef struct LRU {

} LRU;

typedef LRU* LRUPtr;

int LRU_run(InvertedPageTablePtr invertedPageTable, AddressPtr address);

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address);

#endif