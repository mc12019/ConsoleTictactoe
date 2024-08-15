#include "gamelogic/GameBehavior.h"

#include "gamelogic/InputProcess.h"
#include "gamelogic/Scene.h"
#include "gamelogic/Type.h"

int turn = 0;

void initiate(struct Scene *ps) {
    ps->index = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            ps->board[r][c].type = empty;
            ps->board[r][c].index = 0;
        }
    }
}

void setPawn(struct Scene *ps, int r, int c) {
    if (ps->board[r][c].type != 0) return;
    ps->board[r][c].type = turn + 1;
    ps->board[r][c].index = ps->index++;
    turn = !turn;
}

// Date: 2024/8/12 Refactor of which the idea is from a video
// Replaced the old function, code lines get fewer
// Performance is unknown I think it is negligible for the program


int checkWinRefactor(struct Scene *ps, int r, int c, int i, int rd, int cd) {
    // After finding a begin
    if (i == 2)
        return (ps->board[r][c].type - 1) ? 2 : 1;
    else if (i && checkInbound(r + rd, c + cd)) {
        if (ps->board[r + rd][c + cd].type == ps->board[r][c].type) {
            return checkWinRefactor(ps, r + rd, c + cd, i + 1, rd, cd);
        }
    }
    // Begin
    for (int rp = -1; rp != 2; ++rp) {
        for (int cp = -1; cp != 2; ++cp) {
            if (rp == 0 && cp == 0) continue;
            if (!i && checkInbound(r + rp, c + cp)) {
                if (ps->board[r + rp][c + cp].type == ps->board[r][c].type) {
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
            if (ps->board[r][c].type != empty) {
                int tmp = checkWinRefactor(ps, r, c, 0, -2, -2);
                if (tmp != 0) return tmp;
            }
        }
    }
    return 0;
}

void removeOldPawn(struct Scene *ps, int condition) {
    struct Index target;
    target.index = 1000;
    int count = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (ps->board[r][c].type == (condition - 2 ? !turn : turn) + 1) {
                ++count;
                if (ps->board[r][c].index < target.index) {
                    target.index = ps->board[r][c].index;
                    target.r = r;
                    target.c = c;
                }
            }
        }
    }
    if (count > condition) {
        ps->board[target.r][target.c].type = empty;
        ps->board[target.r][target.c].index = 0;
    }
}