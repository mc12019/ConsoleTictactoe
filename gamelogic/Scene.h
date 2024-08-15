#ifndef H_SCENE
#define H_SCENE
struct Pawn
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
    struct Pawn board[3][3];
};
#endif
