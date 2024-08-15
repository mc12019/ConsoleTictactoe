// Date: 2024/7/29
#include "gamelogic/AIBehavior.h"

#include <stdlib.h>

#include "gamelogic/GameBehavior.h"
#include "gamelogic/Scene.h"

#define ENEMY 19
#define SELF 5
#define EMPTY 1

int aiSide;

// AI algorithm adopts the score algorithm to make AI choose the right position.
// From the row, line, sometimes diagonal of a cell, it will calculate the
// scores. Enemy has the biggest one to make AI defend more cautiously. Then the
// highest cell will be chosen to set.
// TODO: The algorithm needs renovating date: 2024/8/1
// The algorithm now isn't perfect though it can deal with many situations

struct Scene *clearEarliestCheck(struct Scene *ps) {
    struct Scene *tmp = (struct Scene *)malloc(sizeof(struct Scene));
    tmp->index = ps->index;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) tmp->board[r][c] = ps->board[r][c];
    }
    removeOldPawn(tmp, 2);
    return tmp;
}

int getCellScore(int type) {
    if (type == 0) return EMPTY;
    if (type == aiSide) return SELF;
    return ENEMY;
}

int scan(struct Scene *ps, int begin, int end, int direction, int fixed,
         int fixedArg) {
    int score = 0;
    for (int p = begin; p != end; p += direction) {
        if (fixedArg == 3) {
            score += getCellScore(ps->board[p][2 - p].type);
            continue;
        }
        if (fixedArg == 2) {
            score += getCellScore(ps->board[p][p].type);
            continue;
        }
        if (!fixedArg)
            score += getCellScore(ps->board[fixed][p].type);
        else
            score += getCellScore(ps->board[p][fixed].type);
    }
    if (score == 2 * SELF + EMPTY) score *= 20;
    if (score == 2 * ENEMY + EMPTY) score *= 10;
    return score;
}

int getScore(struct Scene *ps, int r, int c) {
    int score = scan(ps, 0, 3, 1, r, 0) + scan(ps, 0, 3, 1, c, 1);
    if (r == 1 && c == 1)
        return score + scan(ps, 0, 3, 1, 0, 2) + scan(ps, 0, 3, 1, 0, 3);
    if (r != 1 && r == c) return score + scan(ps, 0, 3, 1, 0, 2);
    if (r != c && r + c == 2) return score + scan(ps, 0, 3, 1, 0, 3);
    return score;
}

void setAISide(int first) { aiSide = first ? 1 : 2; }

void aiProcess(struct Scene *ps) {
    struct Scene *tmpScene = clearEarliestCheck(ps);
    struct Index highestCell;
    highestCell.index = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (tmpScene->board[r][c].type == 0) {
                int score = getScore(ps, r, c);
                if (score >= highestCell.index) {
                    if (ps->board[r][c].type != 0) continue;
                    if (score == highestCell.index) {
                        // Make 5% chance to change the cell when same
                        if (rand() % 20 != 11) continue;
                    }
                    highestCell.index = score;
                    highestCell.r = r;
                    highestCell.c = c;
                }
            }
        }
    }
    free(tmpScene);
    setPawn(ps, highestCell.r, highestCell.c);
}
