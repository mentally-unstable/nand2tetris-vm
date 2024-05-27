// hello
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fatal.h"
#include "util.h"

int chrpos(char *s, char c);
int clean_comment(char *d);

char *rm_ext(char *str) {
    char *s = strdup(str); char *end = strchr(s, '.');
    *(++end) = '\0';
    return s;
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

int chrpos(char *s, char c) {
    char *p;

    p = strchr(s, c);
    return p ?  p - s : -1;
}

int strisdigit(char *s) {
    if (!s)
        return 0;

    char *str = strdup(s);
    for (int i = 0; i < (int) strlen(str); i++) {
        if (chrpos("0123456789", *(str+i)) < 0)
            return 0;
    }
    return 1;
}

/* TODO
 * remove leading
 * remove trailing
 *  - set pointer at where last char was found; chop at end
 */
void strip(char *s) {
    char *p = s;

    char *start;
    while (*p == ' ' || *p == '\t') {
        ++p;
    }
    start = p;

    char *end;
    while (*p != '\0') {
        if (*p != ' ' || *p != '\t')
            end = p;

        ++p;
    }

    s = start;
    *end = '\0';
}

int clean_comment(char *d) {
    if (*d == '/') {
        if (*(d++) == '/') {
            --d;
            *d = '\0';
            return 1;
        }

        return 0;
    }

    // redundant but for compiler satisfaction
    return 1;
}

int segment(char *str) {
    char *s = strtolower(str);

    if (!strcmp(s, "local"))
        return LOCAL;

    if (!strcmp(s, "constant"))
        return CONSTANT;

    if (!strcmp(s, "argument"))
        return ARGUMENT;

    if (!strcmp(s, "this"))
        return THIS;

    if (!strcmp(s, "that"))
        return THAT;

    if (!strcmp(s, "static"))
        return STATIC;

    if (!strcmp(s, "temp"))
        return TEMP;

    if (!strcmp(s, "pointer"))
        return POINTER;

    return -1;
}

int token(char *t) {
    char *str = strtolower(t);

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
    if (!strcmp(str, "call")) {
        return CALL;
    }
    if (!strcmp(str, "function")) {
        return FUNC;
    }
    if (!strcmp(str, "return")) {
        return RETURN;
    }

    fatal_if( 1 , "expected statement (e.g. push)");
    return -1; // just to keep clang happy
}
