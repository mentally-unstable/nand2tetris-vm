// hello
#ifndef ARGS_INCLUDE
#define ARGS_INCLUDE

typedef struct {
    char *in;
    char *out;
    int dir;
} args_t;

args_t *parse_args(int argc, char **argv);
void usage(char *cmd);

#endif
