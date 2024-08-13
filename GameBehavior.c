#include "gamelogic/GameBehavior.h"

#include "gamelogic/InputProcess.h"
#include "gamelogic/Scene.h"
#include "gamelogic/Type.h"

int turn = 0;

void initiate(struct Scene *ps) {
    ps->index = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            ps->scene[r][c].type = empty;
            ps->scene[r][c].index = 0;
        }
    }
}

void setCell(struct Scene *ps, int r, int c) {
    if (ps->scene[r][c].type != 0) return;
    ps->scene[r][c].type = turn + 1;
    ps->scene[r][c].index = ps->index++;
    turn = !turn;
}

// Date: 2024/8/12 Refactor of which the idea is from a video
// Replaced the old function, code lines get fewer
// Performance is unknown I think it is negligible for the program


int checkWinRefactor(struct Scene *ps, int r, int c, int i, int rd, int cd) {
    // After finding a begin
    if (i == 2)
        return (ps->scene[r][c].type - 1) ? 2 : 1;
    else if (i && checkInbound(r + rd, c + cd)) {
        if (ps->scene[r + rd][c + cd].type == ps->scene[r][c].type) {
            return checkWinRefactor(ps, r + rd, c + cd, i + 1, rd, cd);
        }
    }
    // Begin
    for (int rp = -1; rp != 2; ++rp) {
        for (int cp = -1; cp != 2; ++cp) {
            if (rp == 0 && cp == 0) continue;
            if (!i && checkInbound(r + rp, c + cp)) {
                if (ps->scene[r + rp][c + cp].type == ps->scene[r][c].type) {
                    int tmp = checkWinRefactor(ps, r + rp, c + cp, 1, rp, cp);
                    if (tmp != 0) return tmp;
                }
            }
        }
    }
    return 0;
}

int checkWin(struct Scene *ps) {
    for (int r = 0; r != 3; ++r) {
        for (int c = 0; c != 3; ++c) {
            if (ps->scene[r][c].type != empty) {
                int tmp = checkWinRefactor(ps, r, c, 0, -2, -2);
                if (tmp != 0) return tmp;
            }
        }
    }
    return 0;
}

void clearOld(struct Scene *ps, int condition) {
    struct Index target;
    target.index = 1000;
    int count = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (ps->scene[r][c].type == (condition - 2 ? !turn : turn) + 1) {
                ++count;
                if (ps->scene[r][c].index < target.index) {
                    target.index = ps->scene[r][c].index;
                    target.r = r;
                    target.c = c;
                }
            }
        }
    }
    if (count > condition) {
        ps->scene[target.r][target.c].type = empty;
        ps->scene[target.r][target.c].index = 0;
    }
}