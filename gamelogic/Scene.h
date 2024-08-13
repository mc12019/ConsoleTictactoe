#ifndef H_SCENE
#define H_SCENE
struct Cell
{
    int type;
    int index;
};
struct Index
{
    int r;
    int c;
    int index;
};
struct Scene
{
    int index;
    struct Cell scene[3][3];
};
#endif
