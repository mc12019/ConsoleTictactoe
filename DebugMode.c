#include "debugmode/DebugMode.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmode/Interpreter.h"

#define ERROR -3
#define RESTART -2
#define EXIT -1
#define SETPAWN 0
#define PRINT 1
#define SETOPTION 2

int getOperation(const char* s) {
    if (!strcmp(s, "set-option")) {
        return SETOPTION;
    } else if (!strcmp(s, "set-pawn")) {
        return SETPAWN;
    } else if (!strcmp(s, "print")) {
        return PRINT;
    } else if (!strcmp(s, "exit")) {
        return EXIT;
    } else if (!strcmp(s, "restart")) {
        return RESTART;
    }
    return ERROR;
}

void forceSet(struct Scene* ps, int r, int c, int type) {
    ps->board[r][c].type = type;
}

void sceneFields(struct Scene* ps) {
    for (int r = 0; r != 3; ++r) {
        for (int c = 0; c != 3; ++c) {
            printf("index: %d %d\tinformation:\n", r, c);
            printf("type: %d, index: %d\n", ps->board[r][c].type,
                   ps->board[r][c].index);
        }
    }
}

void setOption() {
}

void* debugMode(void* p) {
    struct Scene* ps = (struct Scene*)p;
    char command[100];
    while (1) {
        printf("Debug mode: $ ");
        if (scanf("%s", command)) {
            interpret(command);
            switch (getOperation(com)) {
                case SETOPTION:
                    setOption();
                    break;
                case SETPAWN:
                    forceSet(ps, atoi(getArg(0)), atoi(getArg(1)),
                             atoi(getArg(2)));
                    break;
                case PRINT:
                    sceneFields(ps);
                    break;
                case EXIT:
                    printf("Debug mode exited.\n");
                    pthread_exit(NULL);
                case RESTART:
                    pthread_exit((void*)1);
                case ERROR:
                    fprintf(stderr, "Error command, try again.\n");
                    break;
                default:
                    fprintf(stderr, "An unexpected exception had occured.\n");
                    exit(1);
            }
        }
    }
}

int createThread(struct Scene* ps) {
    pthread_t debugThread;
    if (pthread_create(&debugThread, NULL, debugMode, (void*)ps)) {
        fprintf(stderr, "Error on creating the debug thread.");
        return -1;
    }
    void* value;
    if (pthread_join(debugThread, &value)) {
        fprintf(stderr, "Error on joining the debug thread.");
        return -1;
    }
    if (value == (void*)1) return 1;
    return 0;
}