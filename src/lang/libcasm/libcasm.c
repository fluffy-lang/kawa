#include "libcasm.h"

#include <slreader.h>
#include <sllexer.h>

#include "casm-dictionary.h"

#include "parser.h"
#include "code-gen.h"

#include "objectwriter.h"

static SLLexerContext* ctx = NULL;

void load()
{
    ctx = sl_createLexerContext(lexList, lexStageLst);
    sl_openFile(ctx, "I:/casm.asm");

    KCompiler* c = kcNewCompiler();

    while (kcGetState(c) != KCS_RELEASE) {
        step(c, ctx);
    }

    mModulePrint(kcGetModule(c, kcGetCurrentModuleName(c)));

    writeObject(c, "T:\\Object.geff", OBJECT_TYPE_GEFF);

    sl_closeFile(ctx);
    sl_freeLexerContext(ctx);
}

void unload()
{

}
