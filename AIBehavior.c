// Date: 2024/7/29
#include "AIBehavior.h"
#include <stdlib.h>
#include "GameBehavior.h"
#include "Scene.h"
#include "Type.h"
#include "Function.h"

#define ENEMY 10
#define SELF 5
#define EMPTY 1

int AIside;

// AI algorithm adopts the score algorithm to make AI choose the right position.
// From the row, line, sometimes diagonal of a cell, it will caculates the scores.
// Enemy has the biggest one to make AI defend more cautiously.
// Then the highest cell will be chosen to set.
int getCellScore(int type)
{
    if (type == 0)
        return EMPTY;
    if (type == AIside)
        return SELF;
    if (type - 1 == !(AIside - 1))
        return ENEMY;
}
int scan(struct Scene *ps, int begin, int end, int direction, int fixed, int fixedArg)
{
    int score = 0;
    for (int p = begin; p != end; p += direction)
    {
        if (fixedArg == 3)
        {
            score += getCellScore(ps->scene[p][2 - p].type);
            continue;
        }
        if (fixedArg == 2)
        {
            score += getCellScore(ps->scene[p][p].type);
            continue;
        }
        if (!fixedArg)
            score += getCellScore(ps->scene[fixed][p].type);
        if (fixedArg)
            score += getCellScore(ps->scene[p][fixed].type);
    }
    return score;
}
int getScore(struct Scene *ps, int r, int c)
{
    int score = scan(ps, 0, 3, 1, r, 0) + scan(ps, 0, 3, 1, c, 1);
    if (r == 1 && c == 1)
        return score + scan(ps, 0, 3, 1, 0, 2) + scan(ps, 0, 3, 1, 0, 3);
    if (r != 1 && r == c)
        return score + scan(ps, 0, 3, 1, 0, 2);
    if (r != c && r + c == 2)
        return score + scan(ps, 0, 3, 1, 0, 3);
    return score;
}

void setAISide(int first)
{
    AIside = first ? 1 : 2;
}
void AIprocess(struct Scene *ps)
{
    struct Index highestCell;
    highestCell.index = 0;
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            if (ps->scene[r][c].type == 0)
            {
                int score = getScore(ps, r, c);
                if (score >= highestCell.index)
                {
                    if (score == highestCell.index)
                    {
                        if (rand() % 20 != 11)
                            continue;
                    }
                    highestCell.index = score;
                    highestCell.r = r;
                    highestCell.c = c;
                }
            }
        }
    }
    setCell(ps, highestCell.r, highestCell.c);
}