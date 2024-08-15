#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "debugmode/DebugMode.h"
#include "gamelogic/AIBehavior.h"
#include "gamelogic/GameBehavior.h"
#include "gamelogic/InputProcess.h"
#include "gamelogic/Scene.h"

struct GameVariables {
    int ai;
    int aiFirst;
    int indexMode;
    int r;
    int c;
} opts;
#define INXMODE opts.indexMode

int printWin(int side) {
    if (side == (opts.aiFirst ? 1 : 2)) {
        printf("AI won!\n");
        return 1;
    }
    if (side == 1) printf("Circle won!\n");
    if (side == 2) printf("Cross won!\n");
    return side > 0 ? 1 : 0;
}

int shutupScanf(int status) { return 0; }

void enquireAIMode() {
    while (1) {
        printf("If enabling AI mode? Yes - 1, No - 0: ");
        shutupScanf(scanf("%d", &opts.ai));
        if (opts.ai != 0 && opts.ai != 1) {
            printf("Wrong input, try again. ");
            continue;
        }
        break;
    }
    opts.aiFirst = 0;
    if (opts.ai) {
        while (1) {
            printf("Who first, AI - 1, you - 0: ");
            shutupScanf(scanf("%d", &opts.aiFirst));
            if (opts.aiFirst != 0 && opts.aiFirst != 1) {
                printf("Wrong input, try again. ");
                continue;
            }
            break;
        }
        setAISide(opts.aiFirst);
    }
}

int gameLoop() {
    while (1) {
        struct Scene* scene = malloc(sizeof(struct Scene));
        initiate(scene);
        show(scene);
        int w, restart = 0;
        enquireAIMode();
        while (1) {
            if (opts.aiFirst) {
                aiProcess(scene);
                removeOldPawn(scene, 3);
                show(scene);
                w = checkWin(scene);
                if (printWin(w)) break;
            }
            while (1) {
                printf("Input your target (row, column): ");
                shutupScanf(scanf("%d", &opts.r));
                if (opts.r == -1) {
                    if (createThread(scene)) {
                        restart = 1;
                        break;
                    }
                    printf("Input the row again, then the column: ");
                    shutupScanf(scanf("%d", &opts.r));
                }
                shutupScanf(scanf("%d", &opts.c));
                if (!checkInbound(opts.r - INXMODE, opts.c - INXMODE) ||
                    scene->board[opts.r - INXMODE][opts.c - INXMODE].type !=
                        0) {
                    printf("Wrong input, try again. ");
                    continue;
                }
                break;
            }
            if (restart) break;
            setPawn(scene, opts.r - 1, opts.c - 1);
            removeOldPawn(scene, 3);
            if (!opts.aiFirst) {
                aiProcess(scene);
                removeOldPawn(scene, 3);
            }
            show(scene);
            w = checkWin(scene);
            if (printWin(w)) break;
        }
        free(scene);
        int condition;
        printf("Try again? Yes - 1, No - 0: ");
        shutupScanf(scanf("%d", &condition));
        if (!condition) break;
    }
    return 0;
}

int main(void) {
    srand(time(0));
    opts.indexMode = 1;
    return gameLoop();
}