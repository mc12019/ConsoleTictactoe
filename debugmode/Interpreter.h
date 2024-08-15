#ifndef F_INTERPRETER
#define F_INTERPRETER
#define LNG 20
#define ARGS 10
char com[LNG];
char args[ARGS][LNG];
void interpret(const char* s) {
    // argi -> argument index segi -> segement index
    int inQuote = 0, argi = -1, segi = 0;
    for (int r = 0; r != ARGS; ++r) {
        for (int i = 0; i != LNG; ++i) {
            com[i] = '\0';
            args[r][i] = '\0';
        }
    }
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '\"' || s[i] == '\'') {
            inQuote = !inQuote;
            continue;
        }
        if (argi < 0) {
            com[segi++] = s[i];
            continue;
        }
        if (s[i] == ' ' && !inQuote) {
            if (argi < 0)
                com[segi] = '\0';
            else
                args[argi][segi] = '\0';
            segi = 0;
            ++argi;
            continue;
        }
        args[argi][segi++] = s[i];
    }
    if (segi != 0) com[segi] = '\0';
}
char* getCom() { return com; }
char* getArg(int i) { return args[i]; }
#endif