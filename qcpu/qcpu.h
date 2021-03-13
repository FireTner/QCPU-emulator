#include <stdint.h> // TODO: Dont use this
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdio.h> // debugging

typedef struct _QCPU
{
    uint8_t pc;
    uint8_t poi;
    uint8_t acc;
    uint8_t *regs;
    uint8_t *dCache;
    uint8_t *iCache;
    void (*storageLoad)(uint8_t*, uint8_t);
    void (*storageStore)(uint8_t*, uint8_t);
    uint8_t (*portIn)(uint8_t);
    void (*portOut)(uint8_t, uint8_t);
    _Bool running;
    uint8_t _Flags; 
    uint8_t selFlags;

} QCPU;

#include "qcpu-insts.h"

QCPU* QCPU_init(uint8_t (*portIn)(uint8_t), void (*portOut)(uint8_t, uint8_t), void (*storageLoad)(uint8_t*, uint8_t), void (*storageStore)(uint8_t*, uint8_t))
{
    QCPU* r = malloc(sizeof(QCPU)); // Allocated Pointer To QCPU
    r->dCache = malloc(32);
    r->iCache = malloc(32);
    r->regs = malloc(8);
    r->portIn = portIn;
    r->portOut = portOut;
    r->storageLoad = storageLoad;
    r->storageStore = storageStore;
    r->pc = 0;
    r->running = 1;
    r->storageLoad(r->iCache, 0);
    return r;
}

_Bool QCPU_step(QCPU *CPU)
{
    uint8_t inst = CPU->iCache[CPU->pc++];
    uint8_t opcode = inst & 0x1F;

    if(opcode & 1)
    {
        // printf("ext: %d;%2x\n", (opcode>>1) & 0x3, (inst & 0xF8));
        ext_inst_table[(opcode>>1) & 0x3](CPU, (inst & 0xF8) >> 3);
    }
    else
    {
        // printf("ins: %d;%2x\n", opcode>>1, (inst & 0xE0) >> 5);
        inst_table[opcode>>1](CPU, (inst & 0xE0) >> 5);
    }
    
    if(opcode != 0x1E)
        CPU->poi = 0;

    CPU->regs[0] = 0;
    return CPU->running;
}