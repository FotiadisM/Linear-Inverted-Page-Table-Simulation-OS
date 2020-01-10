#include <stdlib.h>
#include <string.h>

#include "../include/Simulator.h"

int main(int argc, char* argv[]) {

    if(argc < 7) {
        printf("Correct usage: \n");
        return -1;
    }

    char *algorithm = NULL;
    int quantum = 0;
    int frames = 0;
    int maxReferences = -1;

    for(int i=0; i < argc; i++) {
        if(!strcmp(argv[i], "-f")) {
            frames = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-q")) {
            quantum = atoi(argv[++i]);
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
        }
    }

    if(Simulator_run(algorithm, frames, quantum, maxReferences) == -1) {
        perror("Error occurred, program terminated");
        return -1;
    }

    free(algorithm);

    return 0;
}