#ifndef KAWA_OBJECTWRITER_H
#define KAWA_OBJECTWRITER_H

#include "datatypes.h"

#include "gearapi.h"

#define OBJECT_TYPE_RAW     ( 0x00 )
#define OBJECT_TYPE_GEFF    ( 0x01 )

void writeObject(KCompiler* compiler, char* file, duint32 type);

#endif //KAWA_OBJECTWRITER_H
