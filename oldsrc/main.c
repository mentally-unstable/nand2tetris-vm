// hello
#include <stdio.h>
#include <stdlib.h>

#define LOCAL_FILE_INFO
#include "args.h"
#include "gen.h"
#include "lexer.h"
#include "ast.h"
#include "asm.h"

#define loadfile(state) scan(state)

int main(int argc, char **argv) {
    args_t *args = parse_args(argc, argv);

    state_t state = {
        .eof = 0,
        .putback = 0,
        .current = (token_t *)malloc(sizeof(token_t)),
    };

    state.current->col = 0;
    state.current->row = 0;

    // local file info
    g__code = fopen(args->in, "r+");
    g__filename = args->in;

    if (!g__code) {
        fprintf(stderr, "File error: unable to open %s\n", g__filename);
        exit(1);
    }

    FILE *fout = fopen(args->out, "w+");
    if (!fout) {
        fprintf(stderr, "File error: unable to open output file `%s`\n", args->out);
        exit(1);
    }

    if (args->dir) {
        // load each file
        // build trees
        // generate file from all trees
    } else {
        loadfile(&state);
        tree_t *trunk = build_tree(&state);
        genfile(&state, trunk, fout);
    }

    free(state.current);

    return 0;
}
