// hello
#include <stdio.h>
#include <stdlib.h>

#include "interpret.h"
#include "stringutils.h"

typedef struct {
    int data[STACK_SIZE];
    int top;
} v_stack_t;

v_stack_t global_stack;

int heap[HEAP_SIZE];
// TODO symbol table in heap

void push(v_stack_t *s, int val);
void pop(v_stack_t *s, int addr);
void add(v_stack_t *s);
void sub(v_stack_t *s);
void neg(v_stack_t *s);
void eq(v_stack_t *s);
void gt(v_stack_t *s);
void lt(v_stack_t *s);
void and(v_stack_t *s);
void or(v_stack_t *s);
void not(v_stack_t *s);
void printstack(v_stack_t *s);

void printstack(v_stack_t *s) {
    printf("[");
    for (int i = 0; i < STACK_SIZE; i++) {
        printf(" %i", s->data[i]);
        if (i == s->top)
            printf("*");
    }
    printf("]\n");
}

void push(v_stack_t *s, int val) {
    printf("pushed %i onto ", val);

    int *top = &s->top;

    s->data[*top] = val;
    *top += 1;

    printstack(s);
}

void pop(v_stack_t *s, int addr) {
    printf("popped %i off into %i\n", s->data[s->top], addr);

    int *top = &s->top;

    heap[addr] = s->data[*top];
    *top -= 1;
}

void add(v_stack_t *s) {
    int *top = &s->top;

    int res = s->data[*top-1] + s->data[*top];

    printf("%i + %i = %i\n", s->data[*top-1], s->data[*top], res);

    *top -= 1;
    s->data[*top] = res;
}

void sub(v_stack_t *s) {
    int *top = &s->top;

    int res = s->data[*top-1] - s->data[*top];

    printf("%i - %i = %i\n", s->data[*top-1], s->data[*top], res);

    *top -= 1;
    s->data[*top] = res;
}

void neg(v_stack_t *s) {
    printf("-%i\n", s->data[s->top]);
    s->data[s->top] *= -1;
}

void eq(v_stack_t *s) {
    int *top = &s->top;

    if (s->data[*top-1] == s->data[*top]) {
        printf("%i == %i  TRUE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = -1;
    } else {
        printf("%i == %i  FALSE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = 0;
    }

    *top -= 1;
}

void gt(v_stack_t *s) {
    int *top = &s->top;

    if (s->data[*top-1] > s->data[*top]) {
        printf("%i > %i  TRUE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = -1;
    } else {
        printf("%i > %i  FALSE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = 0;
    }

    *top -= 1;
}

void lt(v_stack_t *s) {
    int *top = &s->top;

    if (s->data[*top-1] < s->data[*top]) {
        printf("%i < %i  TRUE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = -1;
    } else {
        printf("%i < %i  FALSE\n", s->data[*top-1], s->data[*top]);

        s->data[*top-1] = 0;
    }

    *top -= 1;
}

void and(v_stack_t *s) {
    int *top = &s->top;

    int res = s->data[*top-1] & s->data[*top];

    printf("%i & %i = %i\n", s->data[*top-1], s->data[*top], res);

    *top -= 1;
    s->data[*top] = res;
}

void or(v_stack_t *s) {
    int *top = &s->top;

    int res = s->data[*top-1] | s->data[*top];

    printf("%i | %i = %i\n", s->data[*top-1], s->data[*top], res);

    *top -= 1;
    s->data[*top] = res;
}

void not(v_stack_t *s) {
    int *top = &s->top;

    printf("!%i\n", s->data[*top]);

    s->data[*top] = !s->data[*top];
}

/*
 * My father who art in heaven, hallowed be thy name,
 * forgive me for this sin as I forgive
 * sinners against the free software movement
 * amen
 */
void (*ops[9]) (v_stack_t *) = { add, sub, neg, eq, gt, lt, and, or, not };

void interpret(tree_t *head, int act, int expect) {
    if (!head) {
        printf("+++ End of tree\n");
        return;
    }


    switch (expect) {
        case NUM:
            if (head->tok.type != NUM) {
                fprintf(stderr, "Error: expected integer in %s at %i:%i\n",
                        head->tok.env.filename,
                        head->tok.env.row,
                        head->tok.env.col);
                exit(1);
            }
        default:
            break;
    }

    switch (act) {
        case PUSH:
            push(&global_stack, head->tok.intvalue);
            break;
        case POP:
            pop(&global_stack, head->tok.intvalue);
            break;
        case ADD:
        case SUB:
        case NEG:
        case EQ:
        case GT:
        case LT:
        case AND:
        case OR:
        case NOT:
            ops[act](&global_stack);
            break;
        default:
            break;
    }

    switch (head->tok.type) {
        case PUSH:
            interpret(head->next, PUSH, NUM);
            break;
        case POP:
            interpret(head->next, POP, NUM);
            break;
        case NUM:
            interpret(head->next, -1, -1);
            break;
        case ADD:
        case SUB:
        case NEG:
        case EQ:
        case GT:
        case LT:
        case AND:
        case OR:
        case NOT:
            interpret(head->next, head->tok.type, -1);
            break;
        default:
            puts("??? No type");
            break;
    }
}
