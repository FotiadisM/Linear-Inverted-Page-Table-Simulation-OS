#include <stdlib.h>
#include "../include/replacmentAlgorithms.h"

int LRU_run(InvertedPageTablePtr invertedPageTable, AddressPtr address) {


    AddressPtr *tmpAddress = NULL;

    if((tmpAddress = InvertedPageTable_getAddress(invertedPageTable, *address)) == NULL) {

        if((tmpAddress = InvertedPageTable_getFreeTrace(invertedPageTable)) == NULL) {
            // tmpAddress = address;
        }
        else {
            // printf("%p, %p, %p\n", &tmpAddress, tmpAddress, &(*tmpAddress));

            *tmpAddress = address;
        }
    }
    else {
    //     if(address->dirty) {
    //         tmpAddress->dirty = true;
    //     }
        free(address);
    }


    return 1;
}

int WS_run(InvertedPageTablePtr *invertedPageTable, AddressPtr *address) {

    

    return 1;
}
