#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct Scene *scene = (struct Scene *)malloc(sizeof(struct Scene));
    initiate(scene);
    show(scene);
    int r, c, w;
    while (1)
    {
        scanf("%d%d", &r, &c);
        setCell(scene, r - 1, c - 1);
        clearOld(scene);
        show(scene);
        w = checkWin(scene);
        if (w == 1)
        {
            printf("Circle won!\n");
            return 0;
        }
        if (w == 2)
        {
            printf("Cross won!\n");
            return 0;
        }
    }
}