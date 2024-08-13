#include "gamelogic/InputProcess.h"

int checkInbound(int r, int c) {
    if (r < 0 || c < 0) return 0;
    if (r > 2 || c > 2) return 0;
    return 1;
}

int setPos(int rp, int cp, int* r, int* c) {
    if (checkInbound(*r + rp, *c + cp)) {
        *r += rp;
        *c += cp;
        return 0;
    }
    return 1;
}

int movePos(char direction, int* r, int* c) {
    switch (direction) {
        case 'w':
            return setPos(-1, 0, r, c);
        case 's':
            return setPos(1, 0, r, c);
        case 'a':
            return setPos(0, -1, r, c);
        case 'd':
            return setPos(0, 1, r, c);
        default:
            return 1;
    }
}
