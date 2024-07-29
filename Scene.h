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
#endif
