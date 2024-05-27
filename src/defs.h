// hello
#ifndef DEFS_INCLUDE
#define DEFS_INCLUDE

#define LINE_LEN 80
#define IDEN_LEN 64

typedef struct {
    int type;
    char *iden;
    int where;
    char *value;
} state_t;

enum {
    PUSH,
    POP,

    ADD,
    SUB,
    MUL,
    DIV,
    NEG,
    EQ,
    LT,
    GT,

    AND,
    OR,
    NOT,

    FUNC,
    CALL,
    RETURN,
    GOTO,
    IF_GOTO,
    IF,
    LABEL,
};

enum {
    LOCAL,
    CONSTANT,
    ARGUMENT,
    THIS,
    THAT,
    STATIC,
    TEMP,
    POINTER,
};

#endif
