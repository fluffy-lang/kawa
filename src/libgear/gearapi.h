#ifndef KAWA_GEARAPI_H
#define KAWA_GEARAPI_H

typedef void(*gRegister)();

struct GProvider
{
    gRegister langReg;
};

struct GAnalyze
{

};

#endif //KAWA_GEARAPI_H
