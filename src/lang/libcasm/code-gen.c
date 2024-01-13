#include "code-gen.h"

#include "formats.h"
#include "car-gen.h"

#include "slconfig.h"

#include "parser.h"

#include "gearapi.h"

#include "parser/directive.h"
#include "parser/keyword.h"

static car_opcodeStruct carOpcodeStruct = {0, NO_REG, 0, 0};

// TODO: Replace later
#define DVM_BSWAP64( var ) \
    (var) = ( ( (var) << 8u  ) & 0xFF00FF00FF00FF00ull ) | ( ( (var) >> 8u  ) & 0x00FF00FF00FF00FFull );  \
    (var) = ( ( (var) << 16u ) & 0xFFFF0000FFFF0000ull ) | ( ( (var) >> 16u ) & 0x0000FFFF0000FFFFull );  \
    (var) = ( (var) << 32u ) | ( ( (var) >> 32u ) & 0xFFFFFFFFull )


duint64 generate(KCompiler* compiler)
{
    duint64 opcode = car_EmitOp(carOpcodeStruct);
    DVM_BSWAP64( opcode );

    SL_BZERO(&carOpcodeStruct, sizeof(car_opcodeStruct));
    carOpcodeStruct.regDst = NO_REG;

    KModule* module = kcGetModule(compiler, kcGetCurrentModuleName( compiler ) );

    if ( opcode & 1 )
        mWrite(module, &opcode, 8);
    else
        mWrite(module, &opcode, 4);

    return opcode;
}

void step(KCompiler* compiler, SLLexerContext* ctx)
{
    if (kcGetState(compiler) & KCS_NEXT_TOKEN) {
        kcSetPreviousToken( compiler, *kcGetCurrentToken(compiler) );
        kcSetCurrentToken( compiler, sl_getNextToken(ctx) );

        kcSetState( compiler, (kcGetState( compiler ) & ~KCS_NEXT_TOKEN) );
    }

    if (kcGetState(compiler) & KCS_GENERATE) {
        generate(compiler);

        kcSetState( compiler, (kcGetState( compiler ) & ~KCS_GENERATE) );
    }

    if ( kcGetCurrentToken(compiler)->type == T_EOF ) {
        generate(compiler);
        kcSetState( compiler, KCS_RELEASE );
        return;
    }

    switch ( kcGetSubState(compiler) ) {
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
