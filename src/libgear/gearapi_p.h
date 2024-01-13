#ifndef KAWA_GEARAPI_P_H
#define KAWA_GEARAPI_P_H

#include "datatypes.h"
#include "gearapi.h"

struct KCompiler
{
    KHashMap*   moduleList;
    KHashMap*   labelList;
    char*       currentModule;

//    KWriter     writer;

    SLToken     previousToken;
    SLToken     currentToken;

    dint        state;
    dint        subState;
    dint        localState;
};

#endif //KAWA_GEARAPI_P_H
