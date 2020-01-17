#include <stdlib.h>
#include <string.h>

#include "../include/Simulator.h"

int main(int argc, char* argv[]) {

    if(argc < 7) {
        printf("Correct usage: \n");
        return -1;
    }

    char *algorithm = NULL;
    int quantity = 0;
    int frames = 0;
    int maxReferences = -1;
    int maxWorkingSet = -1;

    for(int i=0; i < argc; i++) {
        if(!strcmp(argv[i], "-f")) {
            frames = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-q")) {
            quantity = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-m")) {
            maxReferences = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-a")) {
            i++;    // malloc(sizeof(argv[++i])) doesn't seem to work
            if((algorithm = malloc(sizeof(argv[i]))) == NULL) {
                perror("malloc failed");
                return -1;
            }
            strcpy(algorithm, argv[i]);
            if(!strcmp(algorithm, "WS") || !strcmp(algorithm, "ws")) {
                for(int j=0; j < argc; j++) {
                    if(!strcmp(argv[j], "-ws")) {
                        maxWorkingSet = atoi(argv[++j]);
                        break;
                    }
                }
                if(maxWorkingSet == -1) {
                    printf("A max working set window must be defined when using -a WS\n");
                    printf("Example ./bin/runner -a WS -ws 10 -f 100 -q 10\n");
                    return -1;
                }
            }
        }
    }

    if(Simulator_run(algorithm, frames, quantity, maxReferences, maxWorkingSet) == -1) {
        perror("Error occurred, program terminated");
        return -1;
    }

    free(algorithm);

    return 0;
}