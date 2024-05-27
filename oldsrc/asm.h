// hello
#ifndef ASM_HEADER
#define ASM_HEADER

char *preamble = "@255\nD=A\n@SP\nM=D\n";
char *postamble = "(END)\n@END\n0;JMP\n";

char *add = "// XXX ADD\n"
            "@SP\nA=M\nD=M\n@R1\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R2\nM=D\n"
            "@R1\nD=D+M\n@R2\nM=D\n@SP\nM=M-1\n"
            "@R2\nD=M\n@SP\nA=M\nM=D\n";

char *sub = "// XXX SUB\n"
            "@SP\nA=M\nD=M\n@R1\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R2\nM=D\n"
            "@R1\nD=D-M\n@R2\nM=D\n@SP\nM=M-1\n"
            "@R2\nD=M\n@SP\nA=M\nM=D\n";

// relies on @a and @b, sets @c
char *mul_R1_R2 = "// XXX MUL\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R1\nM=D\n"
            "@SP\nA=M\nD=M\n@R2\nM=D\n"
            "@R3\nM=1\n"
            "@R1\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@ANEG\nD;JLT\n"
            "(CHECK)\n"
            "@R2\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@BNEG\nD;JLT\n"
            "@LOOP\n0;JMP\n"
            "(ZERO)\n"
            "@SP\nA=M\nM=0\n@DONE\n0;JMP\n"
            "(ANEG)\n"
            "@R1\nD=M\nM=!M\nM=M+1\n@R4\nM=!M\n@CHECK\n0;JMP\n"
            "(BNEG)\n"
            "@R2\nD=M\nM=!M\nM=M+1\n@R4\nM=!M\n@LOOP\n0;JMP\n"
            "(LOOP)\n"
            "@R3\nD=M\n@R2\nD=D-M\n@DONE\nD;JGT\n"
//                             v
            "@R1\nD=M\n@R5\nD=D+M\nM=D\n@R3\nM=M+1\n@LOOP\n0;JMP\n"
            "(DONE)\n"
            "@R5\nD=M\n@SP\nM=M-1\nA=M\nM=D\n"
            "@R4\nD=M\n@NEGATE\nD;JLT\n@FINISH\n0;JMP\n"
            "(NEGATE)\n"
            "@SP\nA=M\nM=!M\nM=M+1\n"
            "(FINISH)\n";

char *div_R1_R2 = "// XXX DIV\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R1\nM=D\n"
            "@SP\nA=M\nD=M\n@R2\nM=D\n"
            "@R3\nM=0\n"
            "@R1\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@ANEG\nD;JLT\n"
            "(CHECK)\n"
            "@R2\nD=M\n@0\nD=D-A\n@ERR\nM=1\n@END\nD;JEQ\n@BNEG\nD;JLT\n"
            "@LOOP\n0;JMP\n"
            "(ZERO)\n"
            "@SP\nA=M\nM=0\n@DONE\n0;JMP\n"
            "(ANEG)\n"
            "@R1\nD=M\nM=!M\nM=M+1\n@R4\nM=!M\n@CHECK\n0;JMP\n"
            "(BNEG)\n"
            "@R2\nD=M\nM=!M\nM=M+1\n@R4\nM=!M\n"
            "@R1\nD=M\n@R5\nM=D\n@LOOP\n0;JMP\n"
            "(LOOP)\n"
            "@R2\nD=M\n@R5\nM=M-D\n"
            "D=M\n@DONE\nD;JLT\n"
            "@R3\nM=M+1\n@LOOP\n0;JMP\n"
            "(DONE)\n"
            "@R3\nD=M\n@SP\nM=M-1\nA=M\nM=D\n"
            "@R4\nD=M\n@NEGATE\nD;JLT\n@FINISH\n0;JMP\n"
            "(NEGATE)\n"
            "@SP\nA=M\nM=!M\nM=M+1\n"
            "(FINISH)\n";

char *negate = "// XXX NEG\n@SP\nA=M\nM=!M\nM=M+1\n";

char *eq  = "// XXX EQ\n"
            "@SP\nA=M\nD=M\n@b\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R1\nM=D\n"
            "@R2\nD=D-M\n@TRUE\nD;JEQ\nD=0\n"
            "(SET)\n"
            "@R1\nM=D\n@SP\nM=M-1\n@R1\nD=M\n@SP\nA=M\nM=D\n@DONE\n0;JMP\n"
            "(TRUE)\n"
            "D=-1\n@SET\n0;JMP\n"
            "(DONE)\n";

char *and_R1_R2 = "// XXX AND\n"
            "@SP\nA=M\nD=M\n@R2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@R1\nM=D\n"
//                   v
            "@R1\nD=D&M\n@TRUE\nD;JEQ\nD=0\n"
            "(SET)\n"
            "@R1\nM=D\n@SP\nM=M-1\n@R1\nD=M\n@SP\nA=M\n@DONE\n0;JMP\n"
            "(TRUE)\n"
            "D=-1\n@SET\n0;JMP\n"
            "(DONE)\n";

char *pushi_f = "// XXX PUSH NUM\n@SP\nM=M+1\n@%i\nD=A\n@SP\nA=M\nM=D\n";
char *pushs_f = "// XXX PUSH VAR\n@SP\nM=M+1\n@%s\nD=A\n@SP\nA=M\nM=D\n";

char *popi_f = "// XXX POP NUM\n@SP\nA=M\nD=M\n@%i\nM=D\n@SP\nM=M-1\n";
char *pops_f = "// XXX POP VAR\n@SP\nA=M\nD=M\n@%s\nM=D\n@SP\nM=M-1\n";

#endif
