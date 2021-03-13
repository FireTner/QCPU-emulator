#pragma once

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