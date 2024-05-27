// hello
#ifndef TYPES_INCLUDE
#define TYPES_INCLUDE

#define IDEN_LEN 128
#define NUMLEN 64

// keywords
enum {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    NEG,
    EQ,
    GT,
    LT,
    AND,
    OR,
    NOT,

    FUNC, // TODO
    LBL,
    RET,

    CONSTANT,
    ARGUMENT,
    LOCAL,
    THIS,
    THAT,
    POINTER,
};

typedef struct {
    int type;
    int value;
    char *iden;

    int col;
    int row;
} token_t;

typedef struct {
    token_t op;

    void *left;
    void *right;
} sub_t;

typedef struct {
    token_t op;

    void *next;
    sub_t *subtree;
} ast_t;

typedef struct {
    int eof;
    char putback;
    token_t *current;
} state_t;

#ifdef LOCAL_FILE_INFO
#define extern_ /**/
#else
#define extern_ extern
#endif

extern_ FILE *g__code;
extern_ char *g__filename;

#endif
