//===============================================
// cachesim.c
//
// Cache simulator
//===============================================

#include "traceread.h"

int main()
{
    //init trace struct
    Trace t;
    t.traceType = 0;
    t.address = 0;

    open_trace("traces/test1.trace");

    while(!next_trace(&t))
        printf("Action: %d Addr: %x\n", t.traceType, t.address);

    close_trace();
}

