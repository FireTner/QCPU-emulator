// Include when using libs
#pragma once

#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdio.h> // debugging
#include <stdbool.h> // _Bool declaration

#define uint8_t unsigned char // one byte
#define uint16_t unsigned short // one word
#define int16_t short // one signed word

// QCPU struct definition
typedef struct _QCPU
{
    uint8_t pc; // program counter 
    uint8_t poi; // pointer
    uint8_t acc; // accumulator
    uint8_t *regs; // registers
    uint8_t *dCache; // data memory
    uint8_t *iCache; // instruction memory
    void (*storageLoad)(uint8_t*, uint8_t); // storing to storage function
    void (*storageStore)(uint8_t*, uint8_t); // loading from storage function
    uint8_t (*portIn)(uint8_t); // loads data from port
    void (*portOut)(uint8_t, uint8_t); // loads data to port
    _Bool running; // is program running?
    uint8_t _Flags; // current flags
    uint8_t selFlags; // selected flags

} QCPU;

// initializating qcpu 
QCPU* QCPU_init(uint8_t (*portIn)(uint8_t), void (*portOut)(uint8_t, uint8_t), void (*storageLoad)(uint8_t*, uint8_t), void (*storageStore)(uint8_t*, uint8_t));

// stepping qcpu once
_Bool QCPU_step(QCPU *CPU);

uint8_t* QCPU_makeStorage(const unsigned int size);

void QCPU_loadProgram(uint8_t* memory, const char* filePath);

#define _MSC 0
#define _SST 2
#define _SLD 4
#define _SLP 6
#define _PST 8
#define _PLD 10
#define _CND 12
#define _LIM 14
#define _RST 16
#define _AST 18
#define _INC 20
#define _RSH 22
#define _ADD 24
#define _SUB 26
#define _XOR 28
#define _POI 30

#define _HLT 32

#define _NOP 1
#define _JMP 3
#define _MST 5
#define _MLD 7

#define NCOUT 32
#define ZERO 64
#define UNDERFLOW 128

#define R(REG) (REG << 5)
#define A(ADDR) (ADDR << 3)
#define P(PORT) (PORT << 5)

// Miscellenious
void MSC(QCPU *CPU, uint8_t inst);

// Storage Store Data
void SST(QCPU *CPU, uint8_t inst);

// Storage Load Data
void SLD(QCPU *CPU, uint8_t inst);

// Storage Load Program
void SLP(QCPU *CPU, uint8_t inst);

// Port Store
void PST(QCPU *CPU, uint8_t inst);

// Port Load
void PLD(QCPU *CPU, uint8_t inst);

// Condition Select
void CND(QCPU *CPU, uint8_t inst);

// Load Immediate
void LIM(QCPU *CPU, uint8_t inst);

// Register Store Accumulator
void RST(QCPU *CPU, uint8_t inst);

// Accumulator Store Register
void AST(QCPU *CPU, uint8_t inst);

// Increment Register ; 
void INC(QCPU *CPU, uint8_t inst);

// Right Shift Register ;
void RSH(QCPU *CPU, uint8_t inst);

// Add Acumulator To Register And Store To Acumulator ;
void ADD(QCPU *CPU, uint8_t inst);

// Substract Register From Accumulator And Store It To Accumulator ;
void SUB(QCPU *CPU, uint8_t inst);

// XOR Register And Accumulator And Store It To Accumulator ;
void XOR(QCPU *CPU, uint8_t inst);

// For Next Instruction OR Memory Address With Register ;
void POI(QCPU *CPU, uint8_t inst);

// No Operation
void NOP(QCPU *CPU, uint8_t inst);

// Jump
void JMP(QCPU *CPU, uint8_t inst);

// Store Acc To Memory
void MST(QCPU *CPU, uint8_t inst);

// Load To Acc From Memory
void MLD(QCPU *CPU, uint8_t inst);

void (*inst_table[])(QCPU*, uint8_t);
void (*ext_inst_table[])(QCPU*, uint8_t);