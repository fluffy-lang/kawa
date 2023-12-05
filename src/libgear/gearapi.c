#include "gearapi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define BZERO(p, s) memset(p, 0, s)
#define REALLOC(p, s) realloc(p, s)
#define MALLOC(s) malloc(s)
#define FREE(p) free(p)

KModule* createModule(char* moduleName)
{
    hashmap_t* hashmap = MALLOC( sizeof( hashmap_t ) );
    hashmap_create(1024, hashmap);

    KModule* m = MALLOC( sizeof(struct KModule) );
    BZERO( m, sizeof(struct KModule) );

    strcpy( m->section.name, moduleName );
    m->labelList = (KHashMap*)hashmap;
    m->capacity = KB( 4 );
    m->data     = MALLOC( m->capacity );
    BZERO( m->data, m->capacity );

    return m;
}

void mNewLabel(KModule* module, KLabel* label)
{
    hashmap_put((hashmap_t*)module->labelList, label->name, strlen(label->name), label);
}

KLabel* mGetLabel(KModule* module, char* name)
{
    KLabel* label = (KLabel*)hashmap_get((hashmap_t*)module->labelList,
                                name, strlen(name));
    return label;
}

void mWrite(KModule* module, MEMORY data, duint size)
{
    duint newPosition = module->position + size;
    if (newPosition > module->capacity) {
        module->capacity *= 2;
        REALLOC(module->data, module->capacity);
    }

    ADDRESS address     = module->data + module->position;
    module->position    = newPosition;

    memcpy(address, data, size);
}

void mWriteInstruction(KModule* module, duint64 instruction)
{
    if (module->position != 0 && !(module->position % 8) ) {
        duint64 opcode = ((duint64*)module->data)[(module->position / 8) - 1];

        if ( !(opcode >> 63) && !(instruction >> 63) ) {
            instruction >>= 32;
            instruction |= opcode;
            module->position -= 8;
        }
        mWrite(module, &instruction, sizeof(duint64));
        module->position += 4;
    } else {
        if ( (module->position % 8) ) {
            module->position -= 4;
            mWrite(module, &instruction, sizeof(duint64));
        } else {
            mWrite(module, &instruction, sizeof(duint64));
        }
    }
}

void mModulePrint(KModule* module)
{
    for (duint64 i = 0; i < module->position / 8; ++i) {
        printf("FM: %016llx\n", ((duint64*)module->data)[i]);
    }
}

