// hello
#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#define GPS_LOCAL
#include "gen.h"

char *rm_ext(char *str);

int main(int argc, char **argv) {
    args_t *args = parse_args(argc, argv);

    g__filename = rm_ext(args->in);

    FILE *fin = fopen(args->in, "r+");
    if (!fin) {
        fprintf(stderr, "File error: unable to open input file `%s`\n",
                args->in);
        exit(1);
    }

    FILE *fout = fopen(args->out, "w+");
    if (!fout) {
        fprintf(stderr, "File error: unable to open output file `%s`\n",
                args->out);
        exit(1);
    }

    if (args->dir) {
        /* do this */
    } else {
        genfile(fin, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
