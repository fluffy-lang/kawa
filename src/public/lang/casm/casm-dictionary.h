#ifndef KAWA_CASM_DICTIONARY_H
#define KAWA_CASM_DICTIONARY_H

#include "sllexer.h"
#include "slrules.h"

#define CAR_FORMAT_I
#define CAR_FORMAT_R
#include "opcodes.h"

//#define (o, ff) ( ( ff << 8 ) | o )

const SLLexStage lexStageLst[] = {
//        sl_retNextLine,
        sl_skipAnyWhitespace,
        sl_setLocation,
        sl_retNextLine,
        sl_lexemeHandler,
        sl_mathString,
        sl_matchNumber,
        sl_checkEOF,
        sl_retASCII,
        NULL
};

const SLLexList lexList[] = {
        SL_SET_LEXEME(",", T_PUNCTUATOR, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("bits", T_DIRECTIVE, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("section", T_DIRECTIVE, 1, NULL),

        SL_SET_LEXEME("global", T_DIRECTIVE, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("extern", T_DIRECTIVE, SL_TOKEN_INFO_NONE, NULL),

        SL_SET_LEXEME("db", T_DIRECTIVE, SL_TOKEN_INFO_NONE, NULL),

        // Base
        SL_SET_LEXEME("mov", T_KEYWORD, OP_MOV, NULL),
        SL_SET_LEXEME("push", T_KEYWORD, OP_PUSH, NULL),
        SL_SET_LEXEME("pop", T_KEYWORD, OP_POP, NULL),
        SL_SET_LEXEME("swp", T_KEYWORD, OP_SWP, NULL),
        SL_SET_LEXEME("ld", T_KEYWORD, OP_LD, NULL),
        SL_SET_LEXEME("st", T_KEYWORD, OP_ST, NULL),
        SL_SET_LEXEME("bk", T_KEYWORD, OP_BK, NULL),

        // Interrupts
        SL_SET_LEXEME("hwi", T_KEYWORD, OP_HWI, NULL),
        SL_SET_LEXEME("swi", T_KEYWORD, OP_SWI, NULL),

        // Special
        SL_SET_LEXEME("enter", T_KEYWORD, OP_ENTER, NULL),
        SL_SET_LEXEME("leave", T_KEYWORD, OP_LEAVE, NULL),
        SL_SET_LEXEME("inv", T_KEYWORD, OP_INV, NULL),

        // Integer arithmetic
        SL_SET_LEXEME("add", T_KEYWORD, OP_ADD, NULL),
        SL_SET_LEXEME("sub", T_KEYWORD, OP_SUB, NULL),

        SL_SET_LEXEME("inc", T_KEYWORD, OP_INC, NULL),
        SL_SET_LEXEME("dec", T_KEYWORD, OP_DEC, NULL),

        SL_SET_LEXEME("mul", T_KEYWORD, OP_MUL, NULL),
        SL_SET_LEXEME("div", T_KEYWORD, OP_DIV, NULL),
        SL_SET_LEXEME("imul", T_KEYWORD, OP_IMUL, NULL),
        SL_SET_LEXEME("idiv", T_KEYWORD, OP_IDIV, NULL),
        SL_SET_LEXEME("mod", T_KEYWORD, OP_MOD, NULL),

        SL_SET_LEXEME("shl", T_KEYWORD, OP_SHL, NULL),
        SL_SET_LEXEME("shr", T_KEYWORD, OP_SHR, NULL),
        SL_SET_LEXEME("rol", T_KEYWORD, OP_ROL, NULL),
        SL_SET_LEXEME("ror", T_KEYWORD, OP_ROR, NULL),

        // Logic
        SL_SET_LEXEME("and", T_KEYWORD, OP_AND, NULL),
        SL_SET_LEXEME("nand", T_KEYWORD, OP_NAND, NULL),
        SL_SET_LEXEME("or", T_KEYWORD, OP_OR, NULL),
        SL_SET_LEXEME("nor", T_KEYWORD, OP_NOR, NULL),
        SL_SET_LEXEME("xor", T_KEYWORD, OP_XOR, NULL),
        SL_SET_LEXEME("not", T_KEYWORD, OP_NOT, NULL),
        SL_SET_LEXEME("neg", T_KEYWORD, OP_NEG, NULL),

        // Compare
        SL_SET_LEXEME("cmp", T_KEYWORD, OP_CMP, NULL),
        SL_SET_LEXEME("icmp", T_KEYWORD, OP_ICMP, NULL),

        // Flow
        SL_SET_LEXEME("jmp", T_KEYWORD, OP_JMP, NULL),
        SL_SET_LEXEME("jeq", T_KEYWORD, OP_JEQ, NULL),
        SL_SET_LEXEME("jne", T_KEYWORD, OP_JNE, NULL),
        SL_SET_LEXEME("jle", T_KEYWORD, OP_JLE, NULL),
        SL_SET_LEXEME("jge", T_KEYWORD, OP_JGE, NULL),
        SL_SET_LEXEME("jlt", T_KEYWORD, OP_JLT, NULL),
        SL_SET_LEXEME("jgt", T_KEYWORD, OP_JGT, NULL),
        SL_SET_LEXEME("jls", T_KEYWORD, OP_JLS, NULL),
        SL_SET_LEXEME("jhs", T_KEYWORD, OP_JHS, NULL),
        SL_SET_LEXEME("jlo", T_KEYWORD, OP_JLO, NULL),
        SL_SET_LEXEME("jhi", T_KEYWORD, OP_JHI, NULL),

        SL_SET_LEXEME("call", T_KEYWORD, OP_CALL, NULL),
        SL_SET_LEXEME("ceq", T_KEYWORD, OP_CEQ, NULL),
        SL_SET_LEXEME("cne", T_KEYWORD, OP_CNE, NULL),
        SL_SET_LEXEME("cle", T_KEYWORD, OP_CLE, NULL),
        SL_SET_LEXEME("cge", T_KEYWORD, OP_CGE, NULL),
        SL_SET_LEXEME("clt", T_KEYWORD, OP_CLT, NULL),
        SL_SET_LEXEME("cgt", T_KEYWORD, OP_CGT, NULL),
        SL_SET_LEXEME("cls", T_KEYWORD, OP_CLS, NULL),
        SL_SET_LEXEME("chs", T_KEYWORD, OP_CHS, NULL),
        SL_SET_LEXEME("clo", T_KEYWORD, OP_CLO, NULL),
        SL_SET_LEXEME("chi", T_KEYWORD, OP_CHI, NULL),

        SL_SET_LEXEME("rjmp", T_KEYWORD, OP_RJMP, NULL),
        SL_SET_LEXEME("rjeq", T_KEYWORD, OP_RJEQ, NULL),
        SL_SET_LEXEME("rjne", T_KEYWORD, OP_RJNE, NULL),
        SL_SET_LEXEME("rjle", T_KEYWORD, OP_RJLE, NULL),
        SL_SET_LEXEME("rjge", T_KEYWORD, OP_RJGE, NULL),
        SL_SET_LEXEME("rjlt", T_KEYWORD, OP_RJLT, NULL),
        SL_SET_LEXEME("rjgt", T_KEYWORD, OP_RJGT, NULL),
        SL_SET_LEXEME("rjls", T_KEYWORD, OP_RJLS, NULL),
        SL_SET_LEXEME("rjhs", T_KEYWORD, OP_RJHS, NULL),
        SL_SET_LEXEME("rjlo", T_KEYWORD, OP_RJLO, NULL),
        SL_SET_LEXEME("rjhi", T_KEYWORD, OP_RJHI, NULL),

        SL_SET_LEXEME("rcall", T_KEYWORD, OP_RCALL, NULL),
        SL_SET_LEXEME("rceq",  T_KEYWORD, OP_RCEQ, NULL),
        SL_SET_LEXEME("rcne",  T_KEYWORD, OP_RCNE, NULL),
        SL_SET_LEXEME("rcle",  T_KEYWORD, OP_RCLE, NULL),
        SL_SET_LEXEME("rcge",  T_KEYWORD, OP_RCGE, NULL),
        SL_SET_LEXEME("rclt",  T_KEYWORD, OP_RCLT, NULL),
        SL_SET_LEXEME("rcgt",  T_KEYWORD, OP_RCGT, NULL),
        SL_SET_LEXEME("rcls",  T_KEYWORD, OP_RCLS, NULL),
        SL_SET_LEXEME("rchs",  T_KEYWORD, OP_RCHS, NULL),
        SL_SET_LEXEME("rclo",  T_KEYWORD, OP_RCLO, NULL),
        SL_SET_LEXEME("rchi",  T_KEYWORD, OP_RCHI, NULL),

        SL_SET_LEXEME("ret", T_KEYWORD, OP_RET, NULL),

        SL_SET_LEXEME("r0", T_REGISTER, 0, NULL),
        SL_SET_LEXEME("r1", T_REGISTER, 1, NULL),
        SL_SET_LEXEME("r2", T_REGISTER, 2, NULL),
        SL_SET_LEXEME("r3", T_REGISTER, 3, NULL),
        SL_SET_LEXEME("r4", T_REGISTER, 4, NULL),
        SL_SET_LEXEME("r5", T_REGISTER, 5, NULL),
        SL_SET_LEXEME("r6", T_REGISTER, 6, NULL),
        SL_SET_LEXEME("r7", T_REGISTER, 7, NULL),
        SL_SET_LEXEME("r8", T_REGISTER, 8, NULL),
        SL_SET_LEXEME("r9", T_REGISTER, 9, NULL),
        SL_SET_LEXEME("r10", T_REGISTER, 10, NULL),
        SL_SET_LEXEME("r11", T_REGISTER, 11, NULL),
        SL_SET_LEXEME("r12", T_REGISTER, 12, NULL),
        SL_SET_LEXEME("r13", T_REGISTER, 13, NULL),
        SL_SET_LEXEME("r14", T_REGISTER, 14, NULL),
        SL_SET_LEXEME("r15", T_REGISTER, 15, NULL),
        SL_SET_LEXEME("r16", T_REGISTER, 16, NULL),
        SL_SET_LEXEME("r17", T_REGISTER, 17, NULL),
        SL_SET_LEXEME("r18", T_REGISTER, 18, NULL),
        SL_SET_LEXEME("r19", T_REGISTER, 19, NULL),
        SL_SET_LEXEME("r20", T_REGISTER, 20, NULL),
        SL_SET_LEXEME("r21", T_REGISTER, 21, NULL),
        SL_SET_LEXEME("r22", T_REGISTER, 22, NULL),
        SL_SET_LEXEME("r23", T_REGISTER, 23, NULL),
        SL_SET_LEXEME("r24", T_REGISTER, 24, NULL),
        SL_SET_LEXEME("r25", T_REGISTER, 25, NULL),
        SL_SET_LEXEME("r26", T_REGISTER, 26, NULL),
        SL_SET_LEXEME("r27", T_REGISTER, 27, NULL),
        SL_SET_LEXEME("r28", T_REGISTER, 28, NULL),
        SL_SET_LEXEME("r29", T_REGISTER, 29, NULL),
        SL_SET_LEXEME("r30", T_REGISTER, 30, NULL),
        SL_SET_LEXEME("r31", T_REGISTER, 31, NULL),

        SL_END_LEXEME
};

#endif //KAWA_CASM_DICTIONARY_H
