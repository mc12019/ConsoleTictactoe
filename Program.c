#include "Scene.h"
#include "GameBehavior.h"
#include "AIBehavior.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct Scene *scene = (struct Scene *)malloc(sizeof(struct Scene));
    initiate(scene);
    show(scene);
    int r, c, w, AI, first;
    printf("If enabling AI mode? 1 - yes, 0 - no: ");
    scanf("%d", &AI);
    if (AI)
    {
        printf("Who first, AI - 1, you - 0: ");
        scanf("%d", &first);
        setAISide(first);
    }
    while (1)
    {
        if (AI && first)
        {
            AIprocess(scene);
            clearOld(scene);
            show(scene);
            w = checkWin(scene);
            if (w == 1)
            {
                printf("Circle won!\n");
                break;
            }
            if (w == 2)
            {
                printf("Cross won!\n");
                break;
            }
        }
        printf("Input your target (row, column): ");
        scanf("%d%d", &r, &c);
        setCell(scene, r - 1, c - 1);
        if (AI && !first)
            AIprocess(scene);
        clearOld(scene);
        show(scene);
        w = checkWin(scene);
        if (w == 1)
        {
            printf("Circle won!\n");
            break;
        }
        if (w == 2)
        {
            printf("Cross won!\n");
            break;
        }
    }
    free(scene);
    return 0;
}