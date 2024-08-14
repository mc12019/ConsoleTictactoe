#ifndef F_UNITTEST
#define F_UNITTEST
#include <stdio.h>
void printMessage(const char *m) { fprintf(stderr, "Unit test message: %s", m); }
void assert(const int condition, const int state, const char *m) {
    if (condition != state) {
        fprintf(stderr, "Unit test assert: %d != %d\n", condition, state);
        fprintf(stderr, "Unit test message: %s", m);
    }
}
#endif