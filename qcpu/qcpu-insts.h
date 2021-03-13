#pragma once

// Miscellenious
void MSC(QCPU *CPU, uint8_t inst)
{
    CPU->running = (inst != 0); 
}

// Storage Store Data
void SST(QCPU *CPU, uint8_t inst)
{
    CPU->storageStore(CPU->dCache, (inst<<5)|(CPU->poi&0xF8));
}

// Storage Load Data
void SLD(QCPU *CPU, uint8_t inst)
{
    CPU->storageLoad(CPU->dCache, (inst<<5)|(CPU->poi&0xF8));
}

// Storage Load Program
void SLP(QCPU *CPU, uint8_t inst)
{
    CPU->storageLoad(CPU->iCache, (inst<<5)|(CPU->poi&0xF8)); CPU->pc = 0;
}

// Port Store
void PST(QCPU *CPU, uint8_t inst)
{
    CPU->portOut(inst, CPU->acc);
}

// Port Load
void PLD(QCPU *CPU, uint8_t inst)
{
    CPU->acc = CPU->portIn(inst);
}

// Condition Select
void CND(QCPU *CPU, uint8_t inst)
{
    CPU->selFlags = inst;
}

// Load Immediate
void LIM(QCPU *CPU, uint8_t inst)
{
    if(inst == 0)
        CPU->acc = CPU->iCache[CPU->pc++];
    else
        CPU->regs[inst] = CPU->iCache[CPU->pc++];
}

// Register Store Accumulator
void RST(QCPU *CPU, uint8_t inst)
{
    CPU->regs[inst] = CPU->acc;
}

// Accumulator Store Register
void AST(QCPU *CPU, uint8_t inst)
{
    uint16_t result;

    if(inst == 6)
        result = CPU->regs[inst]++;
    else
        result = CPU->regs[inst];

    CPU->_Flags = (!result)<<1 | !(result > 0xFF);
    CPU->acc = result;
}

// Increment Register ; 
void INC(QCPU *CPU, uint8_t inst)
{
    uint16_t result = CPU->regs[inst]+1;

    CPU->_Flags = (!result)<<1 | !(result > 0xFF);
    CPU->acc = result;
}

// Right Shift Register ;
void RSH(QCPU *CPU, uint8_t inst)
{
    CPU->_Flags = (!CPU->regs[inst])<<1 | (CPU->regs[inst]&1)<<2;
    CPU->acc = CPU->regs[inst] >> 1;
}

// Add Acumulator To Register And Store To Acumulator ;
void ADD(QCPU *CPU, uint8_t inst)
{
    uint16_t result = CPU->acc + CPU->regs[inst];

    CPU->_Flags = (!result)<<1 | !(result > 0xFF);
    CPU->acc = result;
}

// Substract Register From Accumulator And Store It To Accumulator ;
void SUB(QCPU *CPU, uint8_t inst)
{
    int16_t result = CPU->acc - CPU->regs[inst];

    CPU->_Flags = (!result)<<1 | !(result < 0);
    CPU->acc = result;
}

// XOR Register And Accumulator And Store It To Accumulator ;
void XOR(QCPU *CPU, uint8_t inst)
{
    uint16_t result = CPU->acc ^ CPU->regs[inst];

    CPU->_Flags = (!result)<<1;
    CPU->acc = result;
}

// For Next Instruction OR Memory Address With Register ;
void POI(QCPU *CPU, uint8_t inst)
{
    CPU->poi = inst;
}

// No Operation
void NOP(QCPU *CPU, uint8_t inst) {}

// Jump
void JMP(QCPU *CPU, uint8_t inst)
{
    if(!((~CPU->_Flags) & CPU->selFlags))
        CPU->pc = inst;
}

// Store Acc To Memory
void MST(QCPU *CPU, uint8_t inst)
{
    CPU->dCache[inst] = CPU->acc;
}

// Load To Acc From Memory
void MLD(QCPU *CPU, uint8_t inst)
{
    CPU->acc = CPU->dCache[inst];
}

void (*inst_table[])(QCPU*, uint8_t) = { MSC, SST, SLD, SLP, PST, PLD, CND, LIM, RST, AST, INC, RSH, ADD, SUB, XOR, POI };
void (*ext_inst_table[])(QCPU*, uint8_t) = { NOP, JMP, MST, MLD };

/*
I1 1100
I2 1010
_O 0010
*/