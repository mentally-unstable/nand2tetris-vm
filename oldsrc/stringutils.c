// hello
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "stringutils.h"

int chrpos(char *s, char c) {
    char *p;

    p = strchr(s, c);
    return p ?  p - s : -1;
}

char *strtolower(char *str) {
    char *new = (char *) malloc(sizeof(char) * IDEN_LEN+1);

    int i = 0;
    while (*(str+i) && i < IDEN_LEN) {
        *(new+i) = tolower( *(str+i) );

        ++i;
    }

    *(new+i) = '\0';

    return new;
}

int strisdigit(char *s) {
    char *str = strdup(s);
    for (int i = 0; i < (int) strlen(str); i++) {
        if (chrpos("0123456789", *(str+i)) < 0)
            return 0;
    }
    return 1;
}

// XXX better name is strenum
int which_token(char *s) {
    char *str = strtolower(s);

    if (strisdigit(str)) {
        return INT;
    }
    if (!strcmp(str, "push")) {
        return PUSH;
    }
    if (!strcmp(str, "pop")) {
        return POP;
    }
    if (!strcmp(str, "add")) {
        return ADD;
    }
    if (!strcmp(str, "sub")) {
        return SUB;
    }
    if (!strcmp(str, "mul")) {
        return MUL;
    }
    if (!strcmp(str, "div")) {
        return DIV;
    }
    if (!strcmp(str, "neg")) {
        return NEG;
    }
    if (!strcmp(str, "eq")) {
        return EQ;
    }
    if (!strcmp(str, "gt")) {
        return GT;
    }
    if (!strcmp(str, "lt")) {
        return LT;
    }
    if (!strcmp(str, "and")) {
        return AND;
    }
    if (!strcmp(str, "or")) {
        return OR;
    }
    if (!strcmp(str, "not")) {
        return NOT;
    }

    if (isalpha(*(s))) {
        return IDEN;
    }

    fprintf(stderr, "Error: unknown token %s\n", str);
    exit(1);
}

char *enumstr(int token) {
    switch (token) {
        case PUSH:
            return "push";
        case POP:
            return "pop";
        case INT:
            return "integer";
        case ADD:
            return "add";
        case SUB:
            return "sub";
        case NEG:
            return "neg";
        case EQ:
            return "eq";
        case GT:
            return "gt";
        case LT:
            return "lt";
        case AND:
            return "and";
        case OR:
            return "or";
        case NOT:
            return "not";
        case IDEN:
            return "identifier";
        default:
            fprintf(stderr, "Error: unknown token (enumstr)\n");
            exit(1);
    }
}
