#include <stdio.h>
#include <stdlib.h>

#include "gamelogic/Scene.h"
#include "gamelogic/Type.h"

char getChar(int type) {
    switch (type) {
        case empty:
            return ' ';
        case circle:
            return 'O';
        case cross:
            return 'X';
        default:
            break;
    }
}

void show(struct Scene *ps) {
    if (system("clear"))
        printf("Error: unable to clear");
    printf("-------------------\n");
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c)
            printf("|%c|\t", getChar(ps->board[r][c].type));
        printf("\n-------------------\n");
    }
}
