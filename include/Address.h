#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Address {
    size_t pid;
    size_t pageNumber;
    bool dirty;
} Address;

typedef Address* AddressPtr;

int Address_setInfo(AddressPtr address, char* info);

int Address_equals(Address address1, Address address2);

void Address_print(Address address);

#endif