#include "parser.h"

void kStage0(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (kcGetCurrentToken(compiler)->type) {
        case T_DIRECTIVE: {
            if ( strcmp(kcGetCurrentToken(compiler)->identString, "section") == 0 ) {

            }
            break;
        }
        case T_KEYWORD: {
            carOpcodeStruct->opcode = kcGetCurrentToken(compiler)->tokenInfo & 0xFF;
            kcSetSubState( compiler, KWD_STAGE1_1 );
            break;
        }
        case T_LABEL: {
            duint nameLen = strlen( kcGetCurrentToken(compiler)->identString );

            KLabel* label   = SL_MALLOC( sizeof(KLabel) );
            label->name     = SL_MALLOC( nameLen + 1 );
            label->address  = (ADDRESS)kcGetModule( compiler, kcGetCurrentModuleName(compiler) )->position;

            strcpy(label->name, kcGetCurrentToken(compiler)->identString);

            mNewLabel(compiler, label);
            break;
        }
        case T_ENDL: {
            break;
        }
        case T_EOF: {
            kcSetState(compiler, KCS_RELEASE);
            return;
        }
        default: {
            printf("Expect DIRECTIVE or KEYWORD!\n");
//            exit(1);
            break;
        }
    }
    kcSetState(compiler, kcGetState(compiler) | KCS_NEXT_TOKEN);
}

void kStage1_1(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (kcGetCurrentToken(compiler)->type) {
        case '{': {
            kcSetSubState(compiler, KWD_STAGE1_2);
            break;
        }
        case T_CONSTANT:
        case T_REGISTER: {
            kcSetSubState(compiler, KWD_STAGE1_4);
            return;
        }
        case T_ENDL: {
            kcSetState(compiler, kcGetState(compiler) | KCS_GENERATE);
            kcSetSubState(compiler, STAGE0);
            break;
        }
        default: {
            printf("kStage1_1: BLYAT");
            exit(1);
            break;
        }
    }
    kcSetState(compiler, kcGetState(compiler) | KCS_NEXT_TOKEN);
}

void kStage1_4(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (kcGetCurrentToken(compiler)->type) {
        case T_REGISTER: {
            if (carOpcodeStruct->regDst == NO_REG)
                carOpcodeStruct->regDst = kcGetCurrentToken(compiler)->tokenInfo;
            else
                carOpcodeStruct->regList |= (1u << kcGetCurrentToken(compiler)->tokenInfo);
            kcSetSubState(compiler, KWD_STAGE2);
            break;
        }
        case T_CONSTANT: {
            carOpcodeStruct->immediate = (duint64)kcGetCurrentToken(compiler)->value;
            break;
        }
        case T_ENDL: {
            kcSetState(compiler, kcGetState(compiler) | KCS_GENERATE);
            kcSetSubState(compiler, STAGE0);
            break;
        }
        default: {
            printf("kStage1_4: BLYAT");
            exit(1);
            break;
        }
    }
    kcSetState(compiler, kcGetState(compiler) | KCS_NEXT_TOKEN);
}

void kStage2(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct)
{
    switch (kcGetCurrentToken(compiler)->type) {
        case ',': {
            kcSetSubState(compiler, KWD_STAGE1_1);
            break;
        }
        case T_ENDL: {
            kcSetState(compiler, kcGetState(compiler) | KCS_GENERATE);
            kcSetSubState(compiler, STAGE0);
            break;
        }
        default: {
            printf("kStage2: BLYAT");
            exit(1);
            break;
        }
    }
    kcSetState(compiler, kcGetState(compiler) | KCS_NEXT_TOKEN);
}

