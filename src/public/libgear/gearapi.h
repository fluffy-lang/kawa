#ifndef KAWA_GEARAPI_H
#define KAWA_GEARAPI_H

#include "datatypes.h"
#include "sllexer.h"

#include "geff.h"

typedef struct hashmap_t KHashMap;

typedef struct KCompiler KCompiler;
typedef struct KLabel KLabel;
typedef struct KModule KModule;

typedef enum KCompilerState KCompilerState;

//typedef void (*KWriter)(KModule* kModule);

struct KLabel
{
    char*   name;
    ADDRESS address;
};

struct KModule
{
    struct GEFF_SECTION section;
    MEMORY              data;
    dsize               position;
    duint64             capacity;
};

enum KCompilerState {
    KCS_PANIC       = 1 << 0,
    KCS_NEXT_TOKEN  = 1 << 1,
    KCS_GENERATE    = 1 << 2,
    KCS_RELEASE     = 1 << 3
};

enum KCompilerSubState {

    STAGE0,         // DIRECTIVE | KEYWORD | LABEL

    KWD_STAGE1_1,   // {
    KWD_STAGE1_2,   // LIST
    KWD_STAGE1_3,   // }
    KWD_STAGE1_4,   // REGISTER
    KWD_STAGE1_5,   // REGISTER | CONSTANT

    KWD_STAGE2,         // PUNCTUATOR ,
    STAGE3,


//    KCSS_WAIT_DIRECTIVE     = 1 << 0,
//    KCSS_WAIT_KEYWORD       = 1 << 1,
//    KCSS_WAIT_REGISTER      = 1 << 2,
//    KCSS_WAIT_LIST          = 1 << 3,
//    KCSS_WAIT_CONSTANT      = 1 << 4,
//    KCSS_WAIT_PUNCTUATOR    = 1 << 5,
//    KCSS_WAIT_ENDL          = 1 << 6
};

KCompiler* kcNewCompiler();

void        kcSetCurrentModuleName(KCompiler compiler, char* name);
char*       kcGetCurrentModuleName(KCompiler* compiler);

void        kcSetPreviousToken(KCompiler* compiler, SLToken token);
SLToken*    kcGetPreviousToken(KCompiler* compiler);
void        kcSetCurrentToken(KCompiler* compiler, SLToken token);
SLToken*    kcGetCurrentToken(KCompiler* compiler);

void    kcSetState      (KCompiler* compiler, dint state);
dint    kcGetState      (KCompiler* compiler);
void    kcSetSubState   (KCompiler* compiler, dint state);
dint    kcGetSubState   (KCompiler* compiler);

int         kcCreateModule  (KCompiler* compiler, char* moduleName);
KModule*    kcGetModule     (KCompiler* compiler, char* moduleName);

void    mNewLabel(KCompiler* compiler, KLabel* label);
KLabel* mGetLabel(KCompiler* compiler, char* name);

void mWrite(KModule* module, MEMORY data, duint size);
void mModulePrint(KModule* module);

#endif //KAWA_GEARAPI_H
