// hello
#include <stdlib.h>
#include <string.h>

#include "fatal.h"
#include "gen.h" // gps
#include "write.h" // + stdio
#include "asm.h"

void cg_push(FILE *out, int from, char *what);
void cg_pop(FILE *out, int from, char *what);
void cg_func_decl(FILE *out, char *name, int lcls);
void cg_func_call(FILE *out, char *name, char *argc);

char *seg_mne(int seg);
char *static_name(char *index);

void cg_state(state_t state, FILE *out) {
    switch (state.type) {
        case FUNC:
            cg_func_decl(out, state.iden, atoi(state.value));
            break;
        case CALL:
            cg_func_call(out, state.iden, state.value);
            break;
        case RETURN:
            fprintf(out, "%s", return_func);
            break;
        case PUSH:
            cg_push(out, state.where, state.value);
            break;
        case POP:
            cg_pop(out, state.where, state.value);
            break;
        case ADD:
            fprintf(out, "%s", add_T1_T2);
            break;
        case SUB:
            fprintf(out, "%s", sub_T1_T2);
            break;
        case MUL:
            fprintf(out, "%s", mul_T1_T2);
            break;
        case DIV:
            fprintf(out, "%s", div_T1_T2);
            break;
        case NEG:
            fprintf(out, "%s", negate);
            break;
        case AND:
            fprintf(out, "%s", and_T1_T2);
            break;
        case OR:
            fprintf(out, "%s", or_T1_T2);
            break;
        case NOT:
            fprintf(out, "%s", not_T1);
            break;
        case EQ:
            fprintf(out, "%s", eq_T1_T2);
            break;
        case GT:
            fprintf(out, "%s", gt_T1_T2);
            break;
        case LT:
            fprintf(out, "%s", lt_T1_T2);
            break;
        default:
            fatal_if( 1, "unknown enum {write.c cg_state}" );
    }
}

void cg_func_decl(FILE *out, char *name, int lcls) {
    char *line = (char *) malloc(strlen(decl_func) + strlen(name));
    sprintf(line, decl_func, name, name);
    fprintf(out, "%s", line);
    // initialize locals
    for (int i = 0; i < lcls; i++) {
        cg_push(out, CONSTANT, "0");
    }
}

void cg_func_call(FILE *out, char *name, char *argc) {
    fprintf(out, call_func, name);

    cg_push(out, CONSTANT, "LCL");
    cg_push(out, CONSTANT, "ARG");
    cg_push(out, CONSTANT, "THIS");
    cg_push(out, CONSTANT, "THAT");

    char *ret_lbl = strncat(strdup(name), "$return", 7);
//    int len = strlen(prepare_move) + strlen(argc) + strlen(ret_lbl);
//    char *line = (char *) malloc(len);
//    sprintf(line, prepare_move, argc, name, ret_lbl);
//    fprintf(out, "%s", line);
    fprintf(out, prepare_stack, argc, name, ret_lbl);
}

void cg_push(FILE *out, int from, char *what) {
//    char *line, *name;
    switch (from) {
        case CONSTANT:
/*            line = (char *) malloc(strlen(push_const) + strlen(what));
            sprintf(line, push_const, what); */
            fprintf(out, push_const, what);
        break;

        case STATIC:
/*            name = static_name(what);
            line = (char *) malloc(strlen(push_static) + strlen(what));
            sprintf(line, push_static, name); */
            name = static_name(what);
            fprintf(out, push_static, name);
        break;

        default:
/*            line = (char *) malloc(strlen(push_seg) + strlen(what));
            sprintf(line, push_seg, what, seg_mne(from)); */
            fprintf(out, push_seg, what, seg_mne(from));
        break;
    }

//    fprintf(out, "%s", line);
}

void cg_pop(FILE *out, int from, char *what) {
/*    char *line, *name, *segment;
    int len; */

    switch (from) {
        case STATIC:
            name = static_name(what);
 /*           len = strlen(pop_static) + strlen(name);
            line = (char *) malloc(len);
            sprintf(line, pop_static, name); */
            fprintf(out, pop_static, name);
        break;
        default:
//            len = strlen(pop_seg) + strlen(segment) + strlen(what);
            segment = seg_mne(from);

/*            line = (char *) malloc(len);
            sprintf(line, pop_seg, segment, what); */
            fprintf(out, pop_seg, segment, what);
    }

//    fprintf(out, "%s", line);
}

void cg_preamble(FILE *out) {
    fprintf(out, "%s", preamble);
}

void cg_postamble(FILE *out) {
    fprintf(out, "%s", postamble);
}

char *seg_mne(int seg) {
    switch (seg) {
        case LOCAL:
            return "LCL";
        case ARGUMENT:
            return "ARG";
        case THIS:
            return "THIS";
        case THAT:
            return "THAT";
        default:
            fatal_if( 1, "unexpected segment {write.c seg_mne}" );
    }
    return NULL; // clang happy
}

char *static_name(char *index) {
    char *name = strdup(g__filename);
    char *with_index = strncat(name, index, 1);
    return with_index;
}
