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

void next_trace(Trace* t)
{
    fgets(tracebuffer, TRACELINELENGTH, tracestream);
    
    parse_line(tracebuffer, t);    
}

int parse_line(char *buffer, Trace *t)
{
   strcmp(buffer[0], "0");

    t->traceType = WRITE;
    t->address = 0;
}
