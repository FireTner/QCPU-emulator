#include "qcpu-binutils.h"

int main()
{
    writeBinFile("fib.bin", Program, sizeof(Program));
    return 0;
}