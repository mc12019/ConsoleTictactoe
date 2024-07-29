#include "GameBehavior.h"
#include "Type.h"
#include "Function.h"

int turn = 0;

// private methods
int checkInbound(int r, int c)
{
    if (r < 0 || c < 0)
        return 0;
    if (r > 2 || c > 2)
        return 0;
    return 1;
}
int getCount(struct Scene *ps, int begin, int end, int direction, int fixed, int fixedArg, int same)
{
    int count = 0;
    for (int p = begin; p != end; p += direction)
    {
        if (same == 2)
        {
            count += ps->scene[p][2 - p].type * ps->scene[p][2 - p].type;
            continue;
        }
        if (same == 1)
        {
            count += ps->scene[p][p].type * ps->scene[p][p].type;
            continue;
        }
        if (!fixedArg)
            count += ps->scene[fixed][p].type * ps->scene[fixed][p].type;
        else
            count += ps->scene[p][fixed].type * ps->scene[p][fixed].type;
    }
    return count;
}
int getSide(int count)
{
    if (count == 3)
        return 1;
    if (count == 12)
        return 2;
    return 0;
}
int isWin(int count)
{
    if (count == 3 || count == 12)
        return 1;
    return 0;
}

// public methods
void initiate(struct Scene *ps)
{
    ps->index = 0;
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            ps->scene[r][c].type = empty;
            ps->scene[r][c].index = 0;
        }
    }
}
void setCell(struct Scene *ps, int r, int c)
{
    if (checkInbound(r, c))
    {
        if (ps->scene[r][c].type != 0)
            return;
        ps->scene[r][c].type = turn + 1;
        ps->scene[r][c].index = ps->index++;
        turn = turn ? 0 : 1;
    }
}
int checkWin(struct Scene *ps)
{
    for (int r = 0; r < 3; ++r)
    {
        int count = getCount(ps, 0, 3, 1, r, 0, 0);
        if (isWin(count))
            return getSide(count);
    }
    for (int c = 0; c < 3; ++c)
    {
        int count = getCount(ps, 0, 3, 1, c, 1, 0);
        if (isWin(count))
            return getSide(count);
    }
    int count = getCount(ps, 0, 3, 1, 0, 0, 1);
    if (isWin(count))
        return getSide(count);
    count = getCount(ps, 0, 3, 1, 0, 0, 2);
    return getSide(count);
}
void clearOld(struct Scene *ps)
{
    struct Index target;
    target.index = 1000;
    int count = 0;
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            if (ps->scene[r][c].type == !turn + 1)
            {
                ++count;
                if (ps->scene[r][c].index < target.index)
                {
                    target.index = ps->scene[r][c].index;
                    target.r = r;
                    target.c = c;
                }
            }
        }
    }
    if (count > 3)
    {
        ps->scene[target.r][target.c].type = empty;
        ps->scene[target.r][target.c].index = 0;
    }
}