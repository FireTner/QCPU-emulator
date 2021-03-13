#pragma once

#include <stdio.h>
#include <stdlib.h>

#define uint8_t unsigned char

uint8_t* QCPU_makeStorage(const unsigned int size)
{
    return (uint8_t*) malloc(size);
}

void QCPU_loadProgram(uint8_t* memory, const char* filePath)
{
    FILE* binFile = fopen(filePath, "r");
    fseek(binFile, 0L, SEEK_END);
    const size_t size = ftell(binFile);
    rewind(binFile);
    fread(memory, size, 1, binFile);
    fclose(binFile);
}

void QCPU_writeProgram(const char* filePath, const uint8_t* program, const size_t size)
{
    FILE* binFile = fopen(filePath, "w");
    fwrite(program, size, 1, binFile);
    fclose(binFile);
}