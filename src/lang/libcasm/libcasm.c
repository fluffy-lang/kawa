#include "libcasm.h"

#include <slreader.h>
#include <sllexer.h>

#include "casm-dictionary.h"

#include "parser.h"
#include "code-gen.h"

static SLLexerContext* ctx = NULL;

void load()
{
    ctx = sl_createLexerContext(lexList, lexStageLst);
    sl_openFile(ctx, "I:/casm.asm");

    KCompiler c; // hide struct and make init func
    c.currentModule = createModule("text");
    c.state     = KCS_NEXT_TOKEN;
    c.subState  = STAGE0;

    while (c.state != KCS_RELEASE) {
        step(&c, ctx);
    }

    mModulePrint(c.currentModule);

    sl_closeFile(ctx);
    sl_freeLexerContext(ctx);
}

void unload()
{

}
