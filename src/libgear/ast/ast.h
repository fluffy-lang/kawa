#ifndef KAWA_AST_H
#define KAWA_AST_H

#include "sllexer.h"

typedef struct ASTPrototype ASTPrototype;
typedef struct ASTArgs ASTArgs;

typedef struct ASTExpr ASTExpr;
typedef struct ASTVar ASTVar;


struct ASTPrototype
{
    SLSourceLocation    name;
    SLSourceLocation    args;
    duint32             flags;
};

struct ASTVar
{
    enum {
        ASTVarTypeUndefined,

        ASTVarTypeU8,
        ASTVarTypeU16,
        ASTVarTypeU32,
        ASTVarTypeU64,

        ASTVarTypeS8,
        ASTVarTypeS16,
        ASTVarTypeS32,
        ASTVarTypeS64,

        ASTVarTypeF32,
        ASTVarTypeF64
    } type;

    union {
        duint8  u8;
        duint16 u16;
        duint32 u32;
        duint64 u64;

        dint8   s8;
        dint16  s16;
        dint32  s32;
        dint64  s64;

        float   f32;
        double  f64;
    };
};



#endif //KAWA_AST_H
