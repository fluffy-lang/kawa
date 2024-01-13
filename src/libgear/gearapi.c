#include "gearapi.h"
#include "gearapi_p.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define BZERO(p, s) memset(p, 0, s)
#define REALLOC(p, s) realloc(p, s)
#define MALLOC(s) malloc(s)
#define FREE(p) free(p)

// TODO: Replace later
#define DVM_BSWAP64( var ) \
    (var) = ( ( (var) << 8u  ) & 0xFF00FF00FF00FF00ull ) | ( ( (var) >> 8u  ) & 0x00FF00FF00FF00FFull );  \
    (var) = ( ( (var) << 16u ) & 0xFFFF0000FFFF0000ull ) | ( ( (var) >> 16u ) & 0x0000FFFF0000FFFFull );  \
    (var) = ( (var) << 32u ) | ( ( (var) >> 32u ) & 0xFFFFFFFFull )

KCompiler* kcNewCompiler()
{
    KCompiler* compiler = MALLOC( sizeof( KCompiler ) );

    hashmap_t* moduleList = MALLOC( sizeof( hashmap_t ) );
    hashmap_create(32, moduleList);

    hashmap_t* labelList = MALLOC( sizeof( hashmap_t ) );
    hashmap_create(1024, labelList);

    compiler->moduleList    = ( KHashMap* )moduleList;
    compiler->labelList     = ( KHashMap* )labelList;
    compiler->currentModule = "text";
    compiler->state         = KCS_NEXT_TOKEN;
    compiler->subState      = STAGE0;

    kcCreateModule( compiler, kcGetCurrentModuleName( compiler ) );

    return compiler;
}

void kcSetCurrentModuleName(KCompiler compiler, char* name) {
    compiler.currentModule = name;
}

char* kcGetCurrentModuleName(KCompiler* compiler) {
    return compiler->currentModule;
}

void kcSetCurrentToken(KCompiler* compiler, SLToken token) {
    compiler->currentToken = token;
}

SLToken* kcGetCurrentToken(KCompiler* compiler) {
    return &compiler->currentToken;
}

void kcSetPreviousToken(KCompiler* compiler, SLToken token) {
    compiler->previousToken = token;
}

SLToken* kcGetPreviousToken(KCompiler* compiler) {
    return &compiler->previousToken;
}

void kcSetState(KCompiler* compiler, dint state) {
    compiler->state = state;
}

dint kcGetState(KCompiler* compiler) {
    return compiler->state;
}

void kcSetSubState(KCompiler* compiler, dint state) {
    compiler->subState = state;
}

dint kcGetSubState(KCompiler* compiler) {
    return compiler->subState;
}

int kcCreateModuleImpl(KCompiler* compiler, char* moduleName);
int kcCreateModule(KCompiler* compiler, char* moduleName)
{
    if (hashmap_get(
            (hashmap_t*)compiler->moduleList,
            moduleName,
            strlen(moduleName))
            ) {
        return 1;
    }

    KModule* dataModule = kcGetModule(compiler, "data");
    if (dataModule == NULL) {
        kcCreateModuleImpl(compiler, "data");

        dataModule = kcGetModule(compiler, "data");
        mWrite(dataModule, "data", sizeof("data"));
    }

    int result = kcCreateModuleImpl(compiler, moduleName);
    KModule* module = kcGetModule(compiler, moduleName);

    module->section.name = dataModule->position;
    mWrite(dataModule, moduleName, strlen(moduleName) + 1);

    return result;
}

int kcCreateModuleImpl(KCompiler* compiler, char* moduleName)
{
    KModule* m = MALLOC( sizeof(struct KModule) );
    BZERO( m, sizeof(struct KModule) );

    m->capacity = KB( 4 );
    m->data     = MALLOC( m->capacity );
    BZERO( m->data, m->capacity );

    m->section.signature = GEFF_SIGNATURE_SECTION;

    return hashmap_put((hashmap_t*)compiler->moduleList,
                       moduleName,strlen(moduleName),
                       m);
}

KModule* kcGetModule(KCompiler* compiler, char* moduleName)
{
    KModule* module = hashmap_get((hashmap_t*)compiler->moduleList,
                                  moduleName,
                                  strlen(kcGetCurrentModuleName(compiler)));
    return module;
}

void mNewLabel(KCompiler* compiler, KLabel* label)
{
    void* value = hashmap_get((hashmap_t*)compiler->labelList,
                              label->name, strlen(label->name));

    if (value != NULL) {
        kcSetState(compiler, kcGetState(compiler) | KCS_PANIC);
        return;
    }

    hashmap_put((hashmap_t*)compiler->labelList, label->name, strlen(label->name), label);
}

KLabel* mGetLabel(KCompiler* compiler, char* name)
{
    KLabel* label = (KLabel*)hashmap_get((hashmap_t*)compiler->labelList,
                                name, strlen(name));
    return label;
}

void mWrite(KModule* module, MEMORY data, duint size)
{
//    if (module == NULL)
//        return;

    duint newPosition = module->position + size;
    if (newPosition > module->capacity) {
        module->capacity *= 2;
        REALLOC(module->data, module->capacity);
    }

    ADDRESS address             = module->data + module->position;
    module->position            = newPosition;
    module->section.sectionSize += size;

    memcpy(address, data, size);
}

void mModulePrint(KModule* module)
{
    for (duint64 i = 0; i < (module->section.sectionSize / 8); ++i) {
        duint64 tp = ((duint64*)module->data)[i];
        DVM_BSWAP64(tp);
        printf("FM: %016llx\n", tp);
    }
}

