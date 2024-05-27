// hello
#ifndef GEN_INCLUDE
#define GEN_INCLUDE

#include <stdio.h>
#include "defs.h"

enum {
    WHERE,
    INTLIT,
    IDEN,
    BIN_OP,
};

#ifdef GPS_LOCAL
#define extern_ /**/
#else
#define extern_ extern
#endif

// GPS (global positioning system lol)
extern_ int g__col;
extern_ int g__row;
extern_ char *g__filename;

void genfile(FILE *in, FILE *out);

#endif
