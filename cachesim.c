//===============================================
// cachesim.c
//
// Cache simulator
//===============================================

#include "traceread.h"

int main()
{
    printf("Hello, world!\n");

    Trace t;

    open_trace("traces/test1.trace");

    next_trace(&t);

    printf("Trace: %d\n", t.traceType);
}

