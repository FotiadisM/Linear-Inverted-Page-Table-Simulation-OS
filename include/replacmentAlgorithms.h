#ifndef RPALGO_H
#define RPALGO_H

#include "./InvertedPageTable.h"
#include "../include/Queue.h"

typedef struct LRU {
    QueuePtr queue;
} LRU;

typedef struct WS {
    QueuePtr queue;
} WS;

typedef WS* WSPtr;

typedef struct WS_Manager {
    int maxWorkingSet;
    WSPtr *workingSet;
} WS_Manager;

typedef union Cashe {
    LRU lru;
    WS_Manager ws;
} Cashe;

typedef Cashe* CashePtr;

int LRU_Init(CashePtr mStruct);

void LRU_Close(CashePtr mStruct);

int LRU_Run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats);

int WS_Init(CashePtr mStruct, int maxWorkingSet);

void WS_Close(CashePtr mStruct);

int WS_Run(InvertedPageTablePtr invertedPageTable, AddressPtr address, CashePtr mStruct, StatisticsPtr stats);

int compare_Addresses(AddressPtr* address1, AddressPtr* address2);

#endif