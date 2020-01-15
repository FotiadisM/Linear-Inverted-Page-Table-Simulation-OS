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
        if(invertedPagetable->table[i] != NULL) {
            Address_print(*(invertedPagetable->table[i]));
        }
    }
}