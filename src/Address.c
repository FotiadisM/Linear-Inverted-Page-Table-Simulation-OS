#include <stdlib.h>
#include <string.h>

#include "../include/Address.h"

int Address_setInfo(AddressPtr address, char* info) {

    char *hex = NULL, *operation = NULL;

    hex = strtok(info, " ");
    operation = strtok(NULL, "\n");

    address->pageNumber = strtoul(hex, NULL, 16) / FRAME_SIZE;

    if(!strcmp(operation, "W")) {
        address->dirty = true;
    }
    else {
        address->dirty = false;
    }

    return 0;
}

int Address_equals(Address address1, Address address2) {

    if(address1.pid == address2.pid && address1.pageNumber == address2.pageNumber) {
        return 1;
    }

    return 0;
}

void Address_print(Address address) {
    printf("\tpid: %ld, pageNumber: %8ld, operation: %d\n", address.pid, address.pageNumber, address.dirty);
}