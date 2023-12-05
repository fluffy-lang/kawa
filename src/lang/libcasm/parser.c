#include "parser.h"

void kStage0(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (compiler->currentToken.type) {
        case T_DIRECTIVE: {
            if ( strcmp(compiler->currentToken.identString, "section") == 0 ) {

            }
//            compiler->state = STAGE2;
            break;
        }
        case T_KEYWORD: {
            carOpcodeStruct->opcode = compiler->currentToken.tokenInfo & 0xFF;
            compiler->subState = KWD_STAGE1_1;
            break;
        }
        case T_LABEL: {
            duint nameLen = strlen( compiler->currentToken.identString );

            KLabel* label   = SL_MALLOC( sizeof(KLabel) );
            label->name     = SL_MALLOC( nameLen + 1 );
            label->address  = (ADDRESS)compiler->currentModule->position;

            strcpy(label->name, compiler->currentToken.identString);

            mNewLabel(compiler->currentModule, label);
            break;
        }
        case T_ENDL: {
            break;
        }
        case T_EOF: {
            compiler->state = KCS_RELEASE;
            return;
        }
        default: {
            printf("Expect DIRECTIVE or KEYWORD!\n");
//            exit(1);
            break;
        }
    }
    compiler->state |= KCS_NEXT_TOKEN;
}

void kStage1_1(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (compiler->currentToken.type) {
        case '{': {
            compiler->subState = KWD_STAGE1_2;
            break;
        }
        case T_CONSTANT:
        case T_REGISTER: {
            compiler->subState = KWD_STAGE1_4;
            return;
        }
        case T_ENDL: {
            compiler->state    |= KCS_GENERATE;
            compiler->subState  = STAGE0;
            break;
        }
        default: {
            printf("kStage1_1: BLYAT");
            exit(1);
            break;
        }
    }
    compiler->state |= KCS_NEXT_TOKEN;
}

void kStage1_4(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (compiler->currentToken.type) {
        case T_REGISTER: {
            if (carOpcodeStruct->regDst == NO_REG)
                carOpcodeStruct->regDst = compiler->currentToken.tokenInfo;
            else
                carOpcodeStruct->regList |= (1u << compiler->currentToken.tokenInfo);
            compiler->subState = KWD_STAGE2;
            break;
        }
        case T_CONSTANT: {
            carOpcodeStruct->immediate = (duint64)compiler->currentToken.value;
            break;
        }
        case T_ENDL: {
            compiler->state    |= KCS_GENERATE;
            compiler->subState  = STAGE0;
            break;
        }
        default: {
            printf("kStage1_4: BLYAT");
            exit(1);
            break;
        }
    }
    compiler->state |= KCS_NEXT_TOKEN;
}

void kStage2(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (compiler->currentToken.type) {
        case ',': {
            compiler->subState = KWD_STAGE1_1;
            break;
        }
        case T_ENDL: {
            compiler->state    |= KCS_GENERATE;
            compiler->subState  = STAGE0;
            break;
        }
        default: {
            printf("kStage2: BLYAT");
            exit(1);
            break;
        }
    }
    compiler->state |= KCS_NEXT_TOKEN;
}

