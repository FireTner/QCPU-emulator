#include <stdint.h>
#include <stdio.h>
#include "..\qcpu\qcpu-idef.h"
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

void writeBinFile(const char* filePath, const uint8_t* program, const size_t size)
{
    FILE* binFile = fopen(filePath, "w");
    fwrite(program, size, 1, binFile);
    fclose(binFile);
}

uint8_t* readBinFile(const char* filePath)
{
    FILE* binFile = fopen(filePath, "r");
    fseek(binFile, 0L, SEEK_END);
    const size_t size = ftell(binFile);
    rewind(binFile);
    uint8_t* program = malloc(size);
    fread(program, size, 1, binFile);
    fclose(binFile);
    return program;
}

int main()
{
    writeBinFile("fib.bin", Program, sizeof(Program));
    return 0;
}