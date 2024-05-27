// hello
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOCAL
#include "args.h"

args_t *parse_args(int argc, char **argv) {
    args_t *args = (args_t *) malloc(sizeof(args_t));
    args->out = "out.asm";

    args->dir = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            exit(1);
        }

        // check dir

        else if (strcmp(argv[i-1], "-o") && !strchr(argv[i], '-')) {
            args->in = argv[i];
            continue;
        }

        else if (!strcmp(argv[i], "-o")) {
            continue;
        }

        else if (!strcmp(argv[i-1], "-o")) {
            args->out = argv[i];
            continue;
        }

        else {
            fprintf(stderr, "Command line error: unknown argument `%s`\n", argv[i]);
        }
    }

    if (!args->in) {
        fprintf(stderr, "Command line error: no input file provided\n");
        usage(argv[0]);
        exit(1);
    }

    return args;
}

void usage(char *cmd) {
    fprintf(stderr,
"Usage:\n$ %s file [options]\n\
options:\n\
\t-o <file>\toutput file name\n\
\t-h|--help\tdisplays this message\n", cmd);
}

