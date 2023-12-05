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

typedef void (*KWriter)(KModule* kModule);

struct KLabel
{
    char*   name;
    ADDRESS address;
};

struct KModule
{
    struct GEFF_SECTION section;
    KHashMap*           labelList;
    MEMORY              data;
    dsize               position;
    duint64             capacity;
};

enum KCompilerState {
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

struct KCompiler
{
    KModule*    currentModule;
    KWriter     writer;

    SLToken     currentToken;

    dint        state;
    dint        subState;
    dint        localState;
};

KModule* createModule(char* moduleName);

void mNewLabel(KModule* module, KLabel* label);
KLabel* mGetLabel(KModule* module, char* name);

void mWrite(KModule* module, MEMORY data, duint size);
void mWriteInstruction(KModule* module, duint64 instruction);
void mModulePrint(KModule* module);

#endif //KAWA_GEARAPI_H
