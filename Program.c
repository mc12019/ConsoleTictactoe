#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gamelogic/AIBehavior.h"
#include "gamelogic/GameBehavior.h"
#include "gamelogic/InputProcess.h"
#include "gamelogic/Scene.h"

int AI, first, debug;

int printWin(int side) {
    if (side == (first ? 1 : 2)) {
        printf("AI won!\n");
        return 1;
    }
    if (side == 1) printf("Circle won!\n");
    if (side == 2) printf("Cross won!\n");
    return side > 0 ? 1 : 0;
}

int main(void) {
    srand(time(0));
    while (1) {
        struct Scene* scene = malloc(sizeof(struct Scene));
        initiate(scene);
        show(scene);
        int r, c, w;
        while (1) {
            printf("If enabling AI mode? Yes - 1, No - 0: ");
            scanf("%d", &AI);
            if (AI == 123) {
                debug = 1;
                break;
            }
            if (AI != 0 && AI != 1) {
                printf("Wrong input, try again. ");
                continue;
            }
            break;
        }
        if (AI) {
            while (1) {
                printf("Who first, AI - 1, you - 0: ");
                scanf("%d", &first);
                if (first != 0 && first != 1) {
                    printf("Wrong input, try again. ");
                    continue;
                }
                break;
            }
            setAISide(first);
        }
        while (1) {
            if (AI && first) {
                aiProcess(scene);
                clearOld(scene, 3);
                show(scene);
                w = checkWin(scene);
                if (printWin(w)) break;
            }
            while (1) {
                printf(
                    "Input your target (row, column): ");
                scanf("%d%d", &r, &c);
                if (!checkInbound(r - 1, c - 1) ||
                    scene->scene[r - 1][c - 1].type != 0) {
                    printf("Wrong input, try again. ");
                    continue;
                }
                break;
            }
            setCell(scene, r - 1, c - 1);
            clearOld(scene, 3);
            if (AI && !first) aiProcess(scene);
            clearOld(scene, 3);
            show(scene);
            w = checkWin(scene);
            if (printWin(w)) break;
        }
        free(scene);
        int condition;
        printf("Try again? Yes - 1, No - 0: ");
        if (!scanf("%d", &condition) && !condition) break;
    }
    return 0;
}