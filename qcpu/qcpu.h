#pragma once

#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdio.h> // debugging

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
QCPU* QCPU_init(uint8_t (*portIn)(uint8_t), void (*portOut)(uint8_t, uint8_t), void (*storageLoad)(uint8_t*, uint8_t), void (*storageStore)(uint8_t*, uint8_t))
{
// allocating the QCPU
    QCPU* r = (QCPU*) malloc(sizeof(QCPU));
    r->dCache = (uint8_t*) malloc(32);
    r->iCache = (uint8_t*) malloc(32);
    r->regs = (uint8_t*) malloc(8);
// setting QCPUs function
    r->portIn = portIn;
    r->portOut = portOut;
    r->storageLoad = storageLoad;
    r->storageStore = storageStore;
// initializing pc and setting QCPU to running
    r->pc = 0;
    r->running = 1;
// loading iCache
    r->storageLoad(r->iCache, 0);
    return r;
}

// including actual instructions
#include "qcpu-insts.h"

// stepping qcpu once
_Bool QCPU_step(QCPU *CPU)
{
// getting instruction and its the opcode
    uint8_t inst = CPU->iCache[CPU->pc++]; 
    uint8_t opcode = inst & 0x1F;

// executing instruction
    if(opcode & 1)
        ext_inst_table[(opcode>>1) & 0x3](CPU, (inst & 0xF8) >> 3);
    else
        inst_table[opcode>>1](CPU, (inst & 0xE0) >> 5);
    
// if it isnt pointer than we set pointer register to 0
    if(opcode != 0x1E)
        CPU->poi = 0;

// clear register 0 as it is supposed to be 0 always and return if cpu is still running
    CPU->regs[0] = 0;
    return CPU->running;
}