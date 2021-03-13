#include "qcpu\qcpu.h"
#include "qcpu\qcpu-idef.h"
#include <synchapi.h>

/*
LIM $1
0
LIM $2
1
CND 0
AST $1
ADD $2
RST $1

AST $1
ADD $2
RST $2
JMP 5
*/

uint8_t Program[] = {
_LIM | R(1),
0,
_LIM | R(2),
1,
_CND,
_AST | R(1),
_ADD | R(2),
_RST | R(1),
_PST,

_AST | R(1),
_ADD | R(2),
_RST | R(2),
_PST,

_JMP | A(5)
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
        // printf("%x\n", cpu->_Flags);
    }
}

/*
Example loading .bin

#include "qcpu-binutils/qcpu-binutils.h"

int main()
{
    storage = malloc(256);
    const char* filePath = "fib.bin";
    memcpy(storage, readBinFile(filePath), fsize(filePath));
    
    QCPU *cpu = QCPU_init(PortIn, PortOut, StorageLoad, StorageStore);
    
    while(cpu->running)
    {
        QCPU_step(cpu);
        // printf("%x\n", cpu->_Flags);
    }
}
*/