#ifndef F_GAMEBEHAVIOR
#define F_GAMEBEHAVIOR
#include "Scene.h"
void initiate(struct Scene*);
void show(struct Scene*);
void setCell(struct Scene*, int, int);
int checkWin(struct Scene* ps);
void clearOld(struct Scene*, int);
#endif