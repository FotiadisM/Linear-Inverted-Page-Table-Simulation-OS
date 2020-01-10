#include <stdlib.h>
#include "../include/replacmentAlgorithms.h"

int LRU_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address) {

    AddressPtr tmpAddress = NULL;

    if((tmpAddress = InvertedPageTable_getAddress(*invertedPageTable, (*invertedPageTable)->size, *address)) != NULL) {
        if((*address)->dirty) {
            
        }
        free(*address);
    }
    else {
        free(*address);
    }

    return 1;
}

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address) {

    

    return 1;
}
