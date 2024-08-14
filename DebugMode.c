#include "debugmode/DebugMode.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugmode/Interpreter.h"

#define ERROR -2
#define EXIT -1
#define SET 0
#define PRINT 1

int getOperation(const char* s) {
    if (!strcmp(s, "set")) {
        return SET;
    } else if (!strcmp(s, "print")) {
        return PRINT;
    } else if (!strcmp(s, "exit")) {
        return EXIT;
    }
    return ERROR;
}

void forceSet(struct Scene* ps, int r, int c, int side) {
    ps->scene[r][c].type = side + 1;
}

void sceneFields(struct Scene* ps) {
    for (int r = 0; r != 3; ++r) {
        for (int c = 0; c != 3; ++c) {
            printf("index: %d %d information:\n", r, c);
            printf("type: %d, index: %d", ps->scene[r][c].type,
                   ps->scene[r][c].index);
        }
    }
}

void* debugMode(void* p) {
    struct Scene* ps = (struct Scene*)p;
    char command[100];
    while (1) {
        printf("Debug mode:~$ ");
        if (scanf("%s", command)) {
            interpret(command);
            switch (getOperation(com)) {
                case SET:
                    forceSet(ps, atoi(getArg(0)), atoi(getArg(1)), atoi(getArg(2)));
                    break;
                case PRINT:
                    sceneFields(ps);
                    break;
                case EXIT:
                    return NULL;
                default:
                    fprintf(stderr, "Error command, try again.\n");
                    break;
            }
        }
    }
}

void* createThread(struct Scene* ps) {
    pthread_t debugThread;
    if (pthread_create(&debugThread, NULL, debugMode, (void*)ps)) {
        fprintf(stderr, "Error on creating the debug thread.");
        return NULL;
    }
    if (pthread_join(debugThread, NULL)) {
        fprintf(stderr, "Error on joining the debug thread.");
        return NULL;
    }
}