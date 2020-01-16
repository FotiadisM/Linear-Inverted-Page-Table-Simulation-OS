#ifndef RPALGO_H
#define RPALGO_H

#include "./InvertedPageTable.h"
#include "../include/Queue.h"

typedef struct LRU {
    QueuePtr queue;
} LRU;

typedef struct WS
{
    /* data */
} WS;

typedef union Cashe {
    LRU lru;
    WS ws;
} Cashe;

typedef Cashe* CashePtr;

int LRU_run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats);

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address);

int compare_Addresses(AddressPtr* address1, AddressPtr* address2);

#endif