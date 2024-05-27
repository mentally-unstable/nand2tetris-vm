// hello
#include <stdio.h>
#include <stdlib.h>
#include "gen.h"
#include "defs.h"

void fatal_if(int cond, char *msg) {
    if (cond) {
        fprintf(stderr, "%s [%i:%i] fatal: %s\n",
                g__filename, g__col, g__row, msg);
        exit(1);
    }
}
