// hello
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "stringutils.h"

char *getiden(state_t *state, char c);
int getint(state_t *state, char c);
void putback(state_t *state, char c);
char next(state_t *state);
char skip(state_t *state);

void putback(state_t *state, char c) { state->putback = c; }

char next(state_t *state) {
    char c;

    if (state->putback) {
        c = state->putback;
        state->putback = 0;
        return c;
    }

    c = fgetc(g__code);
    state->current->col++;

    if (c == '\n') {
        state->current->row++;
        state->current->col = 0;
    }

    return c;
}

char skip(state_t *state) {
    char c;

    do {
        c = next(state);
    } while (isspace(c));

    // TODO: comments
    return c;
}

int getint(state_t *state, char c) {
    int pos, neg = 0, val = 0;

    if (c == '-') {
        neg = 1;
        c = next(state);
    }

    while ((pos = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + pos;
        c = next(state);
    }

    return neg ? val * -1 : val;
}

char *getiden(state_t *state, char c) {
    int i = 0;
    char *buf = (char *)malloc(sizeof(char) * IDEN_LEN + 1);

    while (isalpha(c)) {
        if (IDEN_LEN - 1 == i) {
            fprintf(stderr, "Error: identifier too long at %s %i:%i\n",
                    g__filename, state->current->row, state->current->col);
            exit(1);
        } else {

            *(buf + i) = c;
            ++i;
        }

        c = next(state);
    }

    putback(state, c);
    *(buf + i) = '\0';
    return buf;
}

void scan(state_t *state) {
    char c = skip(state);

    if (c == EOF) {
        state->eof = 1;
        fprintf(stdout, "+++  read file (:\n");
        return;
    }

    if (isdigit(c) || c == '-') {
        state->current->intvalue = getint(state, c);
        state->current->type = INT;
    } else { // identifier
        state->current->iden = getiden(state, c);
        state->current->type = which_token(state->current->iden);
    }
}
