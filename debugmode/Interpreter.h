#ifndef F_INTERPRETER
#define F_INTERPRETER
#define LNG 20
#define ARGS 10
#include <stdio.h>
char _in_com[LNG]; // NOLINT
char _in_args[ARGS][LNG]; // NOLINT
void in_interpret(const char* s) { // NOLINT
    // argi -> argument index segi -> segement index
    int inQuote = 0, argi = -1, segi = 0;
    for (int r = 0; r != ARGS; ++r) {
        for (int i = 0; i != LNG; ++i) {
            _in_com[i] = '\0';
            _in_args[r][i] = '\0';
        }
    }
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '\n')
            continue;
        if (s[i] == '\"' || s[i] == '\'') {
            inQuote = !inQuote;
            continue;
        }
        if (s[i] == ' ' && !inQuote) {
            if (argi < 0)
                _in_com[segi] = '\0';
            else
                _in_args[argi][segi] = '\0';
            segi = 0;
            ++argi;
            continue;
        }
        if (argi < 0) {
            _in_com[segi++] = s[i];
            continue;
        }
        _in_args[argi][segi++] = s[i];
    }
    if (segi != 0) {
        if (argi < 0)
            _in_com[segi] = '\0';
        else
            _in_args[argi][segi] = '\0';
    }
}
char* in_getCom() { return _in_com; } // NOLINT
char* in_getArg(int r) { return _in_args[r]; } // NOLINT
#endif
