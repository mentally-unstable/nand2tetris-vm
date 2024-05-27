// hello
#ifndef ASM_HEADER
#define ASM_HEADER

char *preamble = "@255\nD=A\n@SP\nM=D\n";

char *postamble = "(END)\n@END\n0;JMP\n";

char *add_T1_T2 = "// XXX ADD\n"
                  "@SP\nA=M\nD=M\n@T1\nM=D\n"
                  "@SP\nA=M\nA=A-1\nD=M\n@T2\nM=D\n"
                  "@T1\nD=D+M\n@T2\nM=D\n@SP\nM=M-1\n"
                  "@T2\nD=M\n@SP\nA=M\nM=D\n";

char *sub_T1_T2 = "// XXX SUB\n"
                  "@SP\nA=M\nD=M\n@T1\nM=D\n"
                  "@SP\nA=M\nA=A-1\nD=M\n@T2\nM=D\n"
                  "@T1\nD=D-M\n@T2\nM=D\n@SP\nM=M-1\n"
                  "@T2\nD=M\n@SP\nA=M\nM=D\n";

char *mul_T1_T2 = "// XXX MUL\n"
                "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
                "@SP\nA=M\nD=M\n@T2\nM=D\n"
                "@T3\nM=1\n"
                "@T1\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@ANEG\nD;JLT\n"
                "(CHECK)\n"
                "@T2\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@BNEG\nD;JLT\n"
                "@LOOP\n0;JMP\n"
                "(ZERO)\n"
                "@SP\nA=M\nM=0\n@DONE\n0;JMP\n"
                "(ANEG)\n"
                "@T1\nD=M\nM=!M\nM=M+1\n@T4\nM=!M\n@CHECK\n0;JMP\n"
                "(BNEG)\n"
                "@T2\nD=M\nM=!M\nM=M+1\n@T4\nM=!M\n@LOOP\n0;JMP\n"
                "(LOOP)\n"
                "@T3\nD=M\n@T2\nD=D-M\n@DONE\nD;JGT\n"
                "@T1\nD=M\n@T5\nD=D+M\nM=D\n@T3\nM=M+1\n@LOOP\n0;JMP\n"
                "(DONE)\n"
                "@T5\nD=M\n@SP\nM=M-1\nA=M\nM=D\n"
                "@T4\nD=M\n@NEGATE\nD;JLT\n@FINISH\n0;JMP\n"
                "(NEGATE)\n"
                "@SP\nA=M\nM=!M\nM=M+1\n"
                "(FINISH)\n";

char *div_T1_T2 = "// XXX DIV\n"
                  "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
                  "@SP\nA=M\nD=M\n@T2\nM=D\n"
                  "@T3\nM=0\n"
                  "@T1\nD=M\n@0\nD=D-A\n@ZERO\nD;JEQ\n@ANEG\nD;JLT\n"
                  "(CHECK)\n"
                  "@T2\nD=M\n@0\nD=D-A\n@ERR\nM=1\n@END\nD;JEQ\n@BNEG\nD;JLT\n"
                  "@LOOP\n0;JMP\n"
                  "(ZERO)\n"
                  "@SP\nA=M\nM=0\n@DONE\n0;JMP\n"
                  "(ANEG)\n"
                  "@T1\nD=M\nM=!M\nM=M+1\n@T4\nM=!M\n@CHECK\n0;JMP\n"
                  "(BNEG)\n"
                  "@T2\nD=M\nM=!M\nM=M+1\n@T4\nM=!M\n"
                  "@T1\nD=M\n@T5\nM=D\n@LOOP\n0;JMP\n"
                  "(LOOP)\n"
                  "@T2\nD=M\n@T5\nM=M-D\n"
                  "D=M\n@DONE\nD;JLT\n"
                  "@T3\nM=M+1\n@LOOP\n0;JMP\n"
                  "(DONE)\n"
                  "@T3\nD=M\n@SP\nM=M-1\nA=M\nM=D\n"
                  "@T4\nD=M\n@NEGATE\nD;JLT\n@FINISH\n0;JMP\n"
                  "(NEGATE)\n"
                  "@SP\nA=M\nM=!M\nM=M+1\n"
                  "(FINISH)\n";

char *negate = "// XXX NEG\n@SP\nA=M\nM=!M\nM=M+1\n";

char *eq_T1_T2 = "// XXX EQ\n"
            "@SP\nA=M\nD=M\n@T2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
            "@T2\nD=D-M\n@TRUE\nD;JEQ\nD=0\n"
            "(SET)\n"
            "@T1\nM=D\n@SP\nM=M-1\n@T1\nD=M\n@SP\nA=M\nM=D\n@DONE\n0;JMP\n"
            "(TRUE)\n"
            "D=-1\n@SET\n0;JMP\n"
            "(DONE)\n";

char *gt_T1_T2 = "// XXX EQ\n"
            "@SP\nA=M\nD=M\n@T2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
            "@T2\nD=D-M\n@TRUE\nD;JGT\nD=0\n"
            "(SET)\n"
            "@T1\nM=D\n@SP\nM=M-1\n@T1\nD=M\n@SP\nA=M\nM=D\n@DONE\n0;JMP\n"
            "(TRUE)\n"
            "D=-1\n@SET\n0;JMP\n"
            "(DONE)\n";

char *lt_T1_T2  = "// XXX EQ\n"
            "@SP\nA=M\nD=M\n@T2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
            "@T2\nD=D-M\n@TRUE\nD;JLT\nD=0\n"
            "(SET)\n"
            "@T1\nM=D\n@SP\nM=M-1\n@T1\nD=M\n@SP\nA=M\nM=D\n@DONE\n0;JMP\n"
            "(TRUE)\n"
            "D=-1\n@SET\n0;JMP\n"
            "(DONE)\n";

char *and_T1_T2 = "// XXX AND\n"
            "@SP\nA=M\nD=M\n@T2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
//                   v
            "@T1\nD=D&M\n@SP\nA=M\nM=D\n";

char *or_T1_T2 = "// XXX OR\n"
            "@SP\nA=M\nD=M\n@T2\nM=D\n"
            "@SP\nA=M\nA=A-1\nD=M\n@T1\nM=D\n"
//                   v
            "@T1\nD=D|M\n@SP\nA=M\nM=D\n";

char *not_T1 = "// XXX NOT\n"
               "@SP\nA=M\nD=M\n@T1\nM=D\n"
               "@T1\nD=!M\n"
               "@SP\nA=M\nM=D\n";

char *push_const = "// XXX PUSH NUM\n" "@SP\nM=M+1\n@%s\nD=A\n@SP\nA=M\nM=D\n";
char *push_seg = "// XXX PUSH SEG\n"
                 "@SP\nM=M+1\n"
                 "@%s\nD=A\n@%s\nA=D+A\n"
                 "D=A\n@SP\nA=M\nM=D\n";

char *push_static = "/// XXX PUSH STATIC\n"
                "@SP\nM=M+1\n@%s\nD=M\n"
                "@SP\nA=M\nM=D\n";


char *pop_seg = "// XXX POP SEG\n"
                "@SP\nA=M\nD=M\n@T1\nM=D\n"
                "@%s\nD=M\n@%s\nD=D+A\n@T2\nM=D\n"
                "@T1\nD=M\n@T2\nA=M\nM=D\n"
                "@SP\nM=M-1\n";

char *pop_static = "// XXX POP STATIC\n"
                "@SP\nA=M\nD=M\n@%s\nM=D\n"
                "@SP\nM=M-1\n";

// XXX CONTROL FLOW

#define call_func "/// XXX XXX CALL %s\n"
                // push segs
char *prepare_stack = "@%d\nD=A\n@5\nD=D-A\n" // D = n - 5
                      "@SP\nD=M-D\n@ARG\nM=D\n" // ARG = SP - D
                      "@SP\nD=A\n@LCL\nM=D\n"
                      "@%s\n0;JMP\n(%s)\n"; // func   func$return

char *decl_func = "/// XXX XXX DECL %s\n"
                  "(%s)\n"; // func
                // push local 0 * n

char *return_func = "/// RETURN XXX XXX\n"
                    "@LCL\nD=M\n@frame\nM=D\n"
                    "@5\nD=A\n@frame\nD=M-D\n@ret\nM=D\n"
                    // pop seg ARG
                    "@ARG\nD=M\n@1\nD=D+A\n@SP\nM=D\n"
                    "@frame\nD=M\n@1\nD=D-A\n@THAT\nM=D\n"
                    "@frame\nD=M\n@2\nD=D-A\n@THIS\nM=D\n"
                    "@frame\nD=M\n@3\nD=D-A\n@ARG\nM=D\n"
                    "@frame\nD=M\n@4\nD=D-A\n@LCL\nM=D\n"

#endif
