#include "../include/InvertedPageTable.h"

AddressPtr InvertedPageTable_getAddress(InvertedPageTablePtr invertedPagetable, size_t size, AddressPtr address) {

    for(size_t i=0; i < size; i++) {
        if(invertedPagetable->table[i] != NULL) {
            if(Address_equals(invertedPagetable->table[i], address)) {
                return invertedPagetable->table[i];
            }
        }
    }

    return NULL;
}