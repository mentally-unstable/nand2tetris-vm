// hello
#ifndef WRITE_INCLUDE
#define WRITE_INCLUDE

#include <stdio.h>

#include "defs.h"

void cg_state(state_t state, FILE *out);
void cg_preamble(FILE *out);
void cg_postamble(FILE *out);

#endif
