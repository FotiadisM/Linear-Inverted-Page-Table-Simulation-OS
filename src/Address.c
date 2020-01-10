#include <stdlib.h>
#include <string.h>
#include "../include/Address.h"

int Address_setInfo(AddressPtr *address, char* info) {

    char *token, *operation;

    token = strtok(info, " ");
    operation = strtok(NULL, "\n");

    (*address)->pageNumber = strtoul(token, NULL, 16);

    if(!strcmp(operation, "R")) {
        (*address)->dirty = true;
    }
    else {
        (*address)->dirty = false;
    }

    return 0;
}

int Address_equals(AddressPtr address1, AddressPtr address2) {

    if(address1->pid == address2->pid && address1->pageNumber == address2->pageNumber) {
        return 1;
    }

    return 0;
}