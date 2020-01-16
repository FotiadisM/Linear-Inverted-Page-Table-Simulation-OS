#include <stdlib.h>
#include <string.h>

#include "../include/Simulator.h"

int Simulator_run(char* algorithm, int frames, int quantity, int maxReferences) {

    int (*function)();
    int currReferences = 0, currQuantity = 0;
    bool toggleFiles = false;
    FILE *filePtr1 = NULL, *filePtr2 = NULL;
    CashePtr mStruct = NULL;
    AddressPtr address = NULL;
    StatisticsPtr stats = NULL;
    InvertedPageTablePtr invertedPageTable = NULL;

    if((invertedPageTable = malloc(sizeof(InvertedPageTable))) == NULL) {
        perror("malloc failed");
        return -1;
    }
    invertedPageTable->size = frames;
    if((invertedPageTable->table = malloc(frames*sizeof(AddressPtr))) == NULL) {
        perror("malloc failed");
        return -1;
    }
    for(int i=0; i < invertedPageTable->size; i++) {
        invertedPageTable->table[i] = NULL;
    }

    filePtr1 = fopen("./Assets/bzip.trace", "r");
    filePtr2 = fopen("./Assets/gcc.trace", "r");

    if(filePtr1 == NULL || filePtr2 == NULL) {
        perror("fopen failed");
        return -1;
    }

    if((mStruct = malloc(sizeof(Cashe))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    if((stats = malloc(sizeof(Statistics))) == NULL) {
        perror("malloc failed");
        return -1;
    }
    Statistics_Init(stats);

    if(!strcmp(algorithm, "LRU")) {
        function = LRU_run;
        if((mStruct->lru.queue = malloc(sizeof(Queue))) == NULL) {
            perror("malloc failed");
            return -1;
        }
        Queue_Init(mStruct->lru.queue, sizeof(AddressPtr)); // sizeof(AddressPtr *) == sizeof(AddressPtr)
    }
    else if(!strcmp(algorithm, "WS")) {
        function = WS_run;
    }
    else {
        printf("Unknown replacment algorithm %s\n", algorithm);
        return -1;
    }

    while((address = Simulator_getAddress(filePtr1, filePtr2, &currReferences, maxReferences, &currQuantity, quantity, &toggleFiles)) != NULL) {

        function(invertedPageTable, address, mStruct, stats);
        InvertedPageTable_print(invertedPageTable);
        printf("\n");
    }

    fclose(filePtr1);
    fclose(filePtr2);

    for(int i=0; i < invertedPageTable->size; i++) {
        if(invertedPageTable->table[i] != NULL) {
            free(invertedPageTable->table[i]);
        }
    }
    free(invertedPageTable->table);
    free(invertedPageTable);

    if(!strcmp(algorithm, "LRU")) {
        Queue_Close(mStruct->lru.queue);
        free(mStruct->lru.queue);
    }
    else if(!strcmp(algorithm, "WS")) {

    }
    free(mStruct);
    free(stats);

    return 0;
}

AddressPtr Simulator_getAddress(FILE *filePtr1, FILE *filePtr2, int *currReferences, int maxReferences, int *currQuantity, int quantity, bool *togglefiles) {

    char* line = NULL;
    size_t len = 0;
    AddressPtr address = NULL;

    if(maxReferences != -1) {
        if((*currReferences)++ == 2*maxReferences) {
            return NULL;
        }
    }

    if((address = malloc(sizeof(Address))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    if(*togglefiles) {
        if(getline(&line, &len, filePtr2) == -1) {
            return NULL;
        }
        if(++(*currQuantity) == quantity) {
            *currQuantity = 0;
            *togglefiles = false;
        }
        address->pid = 2;
    }
    else {
        if(getline(&line, &len, filePtr1) == -1) {
            return NULL;
        }
        if(++(*currQuantity) == quantity) {
            *currQuantity = 0;
            *togglefiles = true;
        }
        address->pid = 1;
    }

    Address_setInfo(address, line);

    free(line);

    return address;
}