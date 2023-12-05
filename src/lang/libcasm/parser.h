#ifndef KAWA_PARSER_H
#define KAWA_PARSER_H

#include "datatypes.h"

#include "gearapi.h"
#include "car-gen.h"
#include "sllexer.h"

void kStage0(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);

void kStage1_1(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage1_2(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage1_3(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage1_4(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);

void kStage2(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage3(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage4(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage5(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage6(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);
void kStage7(KCompiler* compiler, car_opcodeStruct* carOpcodeStruct);

#endif //KAWA_PARSER_H
