//===============================================
// traceread.c
//
// Reads traces from input file 
//===============================================

#include "traceread.h"

int open_trace(char *filename)
{
    if(!(tracestream = fopen(filename, "r")))
        return 0;
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

    //zero trace values
    t->traceType = 0;
    t->address = 0; 
    
    //Parse line into Trace
    sscanf(tracebuffer, "%d %x", (int*)&t->traceType, &t->address);

    return 0;
}

