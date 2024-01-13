#include "objectwriter.h"

#include "geff.h"

#include "gearapi_p.h"

#include <stdio.h>
#include <time.h>

#include "hashmap.h"

// TODO: Replace later
#define DVM_BSWAP64( var ) \
    (var) = ( ( (var) << 8u  ) & 0xFF00FF00FF00FF00ull ) | ( ( (var) >> 8u  ) & 0x00FF00FF00FF00FFull );  \
    (var) = ( ( (var) << 16u ) & 0xFFFF0000FFFF0000ull ) | ( ( (var) >> 16u ) & 0x0000FFFF0000FFFFull );  \
    (var) = ( (var) << 32u ) | ( ( (var) >> 32u ) & 0xFFFFFFFFull )

#define DVM_BSWAP32( var ) \
    (var) = ( ( (var) << 8 ) & 0x00FF0000 ) | ( ( (var) >> 8 ) & 0x0000FF00 ); \
    (var) = ( (var) << 24 ) | ( (var) >> 24 )

#define DVM_BSWAP16( var ) \
    ( (var) = ( (var) << 8 ) | ( (var) >> 8 ) )

int writeSectionHeaders(void* const context, struct hashmap_element_s* const e) {
    FILE* f = context;

    KModule* module                 = e->data;
    struct GEFF_SECTION section     = module->section;

    DVM_BSWAP64(section.signature);
    DVM_BSWAP32(section.crc32);
    DVM_BSWAP64(section.name);
    DVM_BSWAP64(section.sectionSize);
    DVM_BSWAP64(section.virtualAddress);
    DVM_BSWAP32(section.flags);

    fwrite(&section, sizeof( struct GEFF_SECTION ), 1, f);

    return 0;
}

int writeSectionHeadersAndData(void* const context, struct hashmap_element_s* const e) {
    FILE* f = context;

    KModule* module                 = e->data;
    struct GEFF_SECTION section     = module->section;

    DVM_BSWAP64(section.signature);
    DVM_BSWAP32(section.crc32);
    DVM_BSWAP64(section.name);
    DVM_BSWAP64(section.sectionSize);
    DVM_BSWAP64(section.virtualAddress);
    DVM_BSWAP32(section.flags);

    fwrite(&section, sizeof( struct GEFF_SECTION ), 1, f);
    fwrite(module->data, module->section.sectionSize, 1, f);

//    duint64 iSize = sectionSize / 8;
//    for (int i = 0; i < iSize; ++i) {
//        duint64 inst = ((duint64*)module->data)[i];
//        fwrite(&inst, sizeof(duint64), 1, f);
//    }

    return 0;
}

void writeObject(KCompiler* compiler, char* file, duint32 type)
{
    FILE* f = fopen(file, "w");

    struct GEFF_HEADER header = {
            GEFF_SIGNATURE_HEADER,
            GEFF_TYPE_OBJ,
            time(NULL),
            0,
            (duint16)hashmap_num_entries((hashmap_t*)compiler->moduleList),
            sizeof( struct GEFF_HEADER )
    };

    DVM_BSWAP64(header.signature);
    DVM_BSWAP64(header.geffVersion);
    DVM_BSWAP16(header.type);
//  = DVM_BSWAP16(header.machine);
    DVM_BSWAP64(header.timeDateStamp);
    DVM_BSWAP16(header.sizeOptionalHeader);
    DVM_BSWAP16(header.sectionNumber);
    DVM_BSWAP64(header.sectionTablePointer);

    fwrite(&header, sizeof( struct GEFF_HEADER ), 1, f);
    hashmap_iterate_pairs((hashmap_t*)compiler->moduleList, writeSectionHeaders, f);
    hashmap_iterate_pairs((hashmap_t*)compiler->moduleList, writeSectionHeadersAndData, f);

    fclose(f);
}
