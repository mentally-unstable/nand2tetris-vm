// hello
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gen.h"
#include "stringutils.h"
#include "asm.h"

void gen_ast(ast_t *head, FILE *out);
void try_push(ast_t *node, FILE *out);
void try_pop(ast_t *node, FILE *out);
void cg_push_s(char *i);
void cg_push_i(int n);
void cg_pop_s(char *s);
void cg_pop_i(int n);

void genfile(state_t *state, ast_t *head, FILE *out) {
    fprintf(out, "%s", preamble);
    statements(state);
    fprintf(out, "%s", postamble);
}

void gen_ast(ast_t *head, FILE *out) {
    if (!head)
        return;

    switch (head->tok.type) {
        case PUSH:
            try_push(head->next, out);
            break;
        case POP:
            try_pop(head->next, out);
            break;
        case MUL:
            fprintf(out, "%s", mul_R1_R2);
            break;
        case DIV:
            fprintf(out, "%s", div_R1_R2);
            break;
        case EQ:
            fprintf(out, "%s", eq);
            break;
        case ADD:
            fprintf(out, "%s", add);
            break;
        case SUB:
            fprintf(out, "%s", sub);
            break;
        default:
            fprintf(stderr, "bruh i donno dis  %s\n", enumstr(head->tok.type));
            exit(1);
    }

    if (head->next) {
        gen_ast(head->next, out);
    }
}

void try_push(ast_t *node, FILE *out) {
    token_t tok = node->tok;

    switch (tok.type) {
        case IDEN:
            cg_push_s(tok->iden);
            break;

        case INT:
            cg_push_i(tok.value)
            break;

        default:
            fprintf(stderr, "Error: expected number or identifier in %s %i:%i"
                            "  (got %s)\n",
                    g__filename, tok.row, tok.col, enumstr(tok.type));
            exit(1);
    }
}

void cg_push_s(char *iden) {
    char *line = (char *) malloc(sizeof(pushs_f) + sizeof(iden));
    sprintf(line, pushs_f, iden);
    fprintf(out, "%s", line);
}

void cg_push_i(int n) {
    char *line = (char *) malloc(sizeof(pushi_f) + NUMLEN);
    sprintf(line, pushi_f, abs(n));
    fprintf(out, "%s", line);

    if (n < 0)
        fprintf(out, "%s", negate);
}

void try_pop(ast_t *node, FILE *out) {
    token_t tok = node->tok;

    switch (tok.type) {
        case IDEN:
            cg_pop_s(tok->iden);
            break;

        case INT:
            cg_pop_i(tok.intvalue);

        default:
            fprintf(stderr, "Error: expected number or identifier in %s %i:%i\n",
                    g__filename, tok.row, tok.col);
            exit(1);
    }
}

// TODO check if enough mem for malloc
void cg_pop_s(char *iden) {
    char *line = (char *) malloc(sizeof(pops_f) + sizeof(iden));
    sprintf(line, pops_f, iden);
    fprintf(out, "%s", line);
}

void cg_pop_i(int n) {
    char *line = (char *) malloc(sizeof(pops_f) + NUMLEN);
    sprintf(line, popi_f, n);
    fprintf(out, "%s", line);
}

void cg_eq(FILE *out) {
    fprintf(out, "%s", eq);
}

void cg_mul(FILE *out) {
    fprintf(out, "%s", mul_R1_R2);
}

void cg_div(FILE *out) {
    fprintf(out, "%s", div_R1_R2);
}
