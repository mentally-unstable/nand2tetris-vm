// hello
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"

ast_t *build_tree(state_t *state) {
    if (state->eof)
        return NULL;

    ast_t *new = (ast_t *) malloc(sizeof(ast_t));
    if (!new) {
        fprintf(stderr, "Memory error: not enough memory for tree.\n");
        exit(1);
    }

    new->op  = *state->current->type;
    new->col = *state->current->col;
    new->row = *state->current->row;

    scan(state);
    new->next = build_tree(state);

    return new;
}
