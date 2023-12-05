#include "code-gen.h"

#include "formats.h"
#include "car-gen.h"

#include "slconfig.h"

#include "parser.h"

#include "gearapi.h"

#include "parser/directive.h"
#include "parser/keyword.h"

void defineSubState(KCompiler* compiler, car_opcodeStruct* opcodeStruct);

static car_opcodeStruct carOpcodeStruct = {0, NO_REG, 0, 0};

duint64 generate(KCompiler* compiler)
{
    duint64 opcode = car_EmitOp(carOpcodeStruct);

    SL_BZERO(&carOpcodeStruct, sizeof(car_opcodeStruct));
    carOpcodeStruct.regDst = NO_REG;

    mWriteInstruction(compiler->currentModule, opcode);

    return opcode;
}

void step(KCompiler* compiler, SLLexerContext* ctx)
{
//    SLToken token;

    if (compiler->state & KCS_NEXT_TOKEN) {
        compiler->currentToken = sl_getNextToken(ctx);

        compiler->state &= ~KCS_NEXT_TOKEN;
    }

    if (compiler->state & KCS_GENERATE) {
        generate(compiler);

        compiler->state &= ~KCS_GENERATE;
    }

    if (compiler->currentToken.type == T_EOF) {
        generate(compiler);
        compiler->state = KCS_RELEASE;
        return;
    }

    switch ( compiler->subState ) {
        case STAGE0: {
            kStage0(compiler, &carOpcodeStruct);
            break;
        }
        case KWD_STAGE1_1: {
            kStage1_1(compiler, &carOpcodeStruct);
            break;
        }
        case KWD_STAGE1_4: {
            kStage1_4(compiler, &carOpcodeStruct);
            break;
        }
        case KWD_STAGE2: {
            kStage2(compiler,  &carOpcodeStruct);
            break;
        }
//        case STAGE3: {
//            kStage3(compiler, &carOpcodeStruct);
//            break;
//        }
        default:
            printf("WHAT THE SUKA FUCK MOTHER FUCK?!");
            break;
    }
}
