#include "Scene.h"
#include "Type.h"
#include <stdio.h>
#include <stdlib.h>

char getChar(int type)
{
    switch (type)
    {
    case empty:
        return '_';
    case circle:
        return 'O';
    case cross:
        return 'X';
    default:
        break;
    }
}
void show(struct Scene *ps)
{
    system("clear");
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
            printf("%c\t", getChar(ps->scene[r][c].type));
        printf("\n");
    }
}