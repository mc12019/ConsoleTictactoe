#ifndef H_SCENE
#define H_SCENE
struct Cell
{
    int type;
    int index;
};
struct Index;
struct Scene
{
    int index;
    struct Cell scene[3][3];
};
void initiate(struct Scene*);
void show(struct Scene*);
void setCell(struct Scene*, int, int);
int checkWin(struct Scene*);
int checkWin(struct Scene*);
void clearOld(struct Scene*);
#endif
