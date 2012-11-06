//===============================================
// traceread.c
//
// 
//===============================================

#include "traceread.h"

int open_trace(char *filename)
{
    if(!(tracestream = fopen(filename, "r")))
        return NULL;
}

void close_trace(void)
{
    fclose(tracestream);
}

int next_trace(Trace* t)
{
    //Get next line from file
    fgets(tracebuffer, TRACELINELENGTH, tracestream);

    //Check if EOF reached
    if(feof(tracestream))
        return -1;

    //Parse line into Trace
    sscanf(tracebuffer, "%d %x", &t->traceType, &t->address);

    return 0;
}

