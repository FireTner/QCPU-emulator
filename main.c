#include "qcpu\qcpu.h"
#include "qcpu\qcpu-idef.h"
// #include <synchapi.h>

/*

Subleq?

128-256

*/

uint8_t Program[] = {
    _CND | ZERO,
    _LIM | R(1), 1,
    _INC | R(1),
    _AST | R(1),
    _PLD | P(1),
    _JMP | A(3)
};

uint8_t *storage;

uint8_t PortIn(uint8_t Port)
{

}

void PortOut(uint8_t Port, uint8_t Data)
{
    printf("PO: %2x\n", Data);
}

void StorageStore(uint8_t* Dest, uint8_t Addr)
{

}

void StorageLoad(uint8_t* Dest, uint8_t Addr)
{
    memcpy(Dest, storage+Addr, 32);
}


int main() {
    storage = malloc(256);
    memcpy(storage, Program, sizeof(Program));
    
    QCPU *cpu = QCPU_init(PortIn, PortOut, StorageLoad, StorageStore);
    
    while(cpu->running)
    {
        QCPU_step(cpu);
    }
}