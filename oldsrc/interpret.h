// hello
#ifndef INTERPRET_INCLUDE
#define INTERPRET_INCLUDE

#include "types.h"

#define STACK_SIZE 32
#define HEAP_SIZE 1028

void interpret(tree_t *head, int act, int expect);

#endif
