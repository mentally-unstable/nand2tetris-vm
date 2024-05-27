// hello
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "util.h"
#include "fatal.h"
#include "gen.h" // + stdio
#include "write.h"


state_t statement(char *line);
char *next_token(char *line);
void expect(char *t, int what);
void fatal_if(int cond, char *msg);
int is_segment(char *t);
int segment(char *str);
int strenum(char *t);

void genfile(FILE *in, FILE *out) {
    g__col = 0;
    char line_buf[LINE_LEN];
    char *line = &line_buf[0];

    cg_preamble(out);

    while (fgets(line, LINE_LEN, in)) {
        g__col++;
        g__row = 0;

        state_t state =  { 0 };

        strip(line);

        if (!strcmp(line, ""))
            continue;

        state = statement(line);
        cg_state(state, out); // enter backend
    }

    cg_postamble(out);
}

state_t statement(char *line) {
    state_t new = { 0 };
    new.iden = (char *) malloc(IDEN_LEN);

    char *t = next_token(line);

    new.type = token(t);

    switch (new.type) {
        case PUSH:
        case POP:
            t = next_token(NULL);
            expect(t, WHERE);
            new.where = segment(t);

            t = next_token(NULL);
            expect(t, INTLIT);
            new.value = t;
        break;

        case CALL:
            t = next_token(NULL);
            expect(t, IDEN);
            strncpy(new.iden, t, IDEN_LEN);
        break;

        case FUNC:
            t = next_token(NULL);
            expect(t, IDEN);
            strncpy(new.iden, t, IDEN_LEN);

            t = next_token(NULL);
            expect(t, INTLIT);
            new.value = t;
        break;

        case LABEL:
            t = next_token(NULL);
            expect(t, IDEN);
            strncpy(new.iden, t, IDEN_LEN);
        break;
    }

    return new;
}

char *next_token(char *line) {
    char *next = strtok(line, " ");
    g__row += strlen(next);
    return next;
}

void expect(char *t, int what) {
    int is_int;

    switch (what) {
        case WHERE:
            fatal_if( !is_segment(t) , "expected segment");
        break;

        case INTLIT:
            is_int = strisdigit(t) || (*t == '-');
            fatal_if( !is_int , "expected integer");
        break;

        case IDEN:
            fatal_if( strisdigit(t), "expected identifier");
        break;

        default:
            break;
    }
}


int is_segment(char *t) {
    if (!t)
        return 0;

    const char *wheres[8] =  {
        "local", "argument", "constant",
        "pointer", "this", "that", "temp",
        "static",
    };

    for (int i = 0; i < 8; i++) {
        if (!strcmp(t, wheres[i]))
            return 1;
    }

    return 0;
}
