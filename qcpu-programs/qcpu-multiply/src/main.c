#include <qcpu-emu.h>

/*
; Layout:
; for y:
;   result += x
;
; R1 = X
; R2 = Y

.Start:
    CND 0b010
    LIM $1, ;X
    LIM $2, ;Y
    LIM $3, 0x01
.Loop:
; Result += X
    AST $4
    ADD $1
    RST $4
; Y--
    AST $2
    SUB $3
; If Y == 0 Then HLT
    JMP .End
; After Mult
.End
    MSC 1
*/

uint8_t Program[] =
{
_LIM | R(1), 2, // X
_LIM | R(2), 32, // Y
_LIM | R(3), 1,
_LIM | R(4), 0,

// R += X
_AST | R(4),
_ADD | R(1),
_RST | R(4),

// Y--
_AST | R(2),
_SUB | R(3),
_RST | R(2),

// If Y == 0 Then HLT
_CND | 2,
_JMP | A(18),
_CND,
_JMP | A(8),

// After Mult
_AST | R(4),
_PST | P(0),
_MSC | 1
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
    cpu->acc = 0;

    while(cpu->running)
    {
        QCPU_step(cpu);
        printf("%x\n", cpu->regs[4]);
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