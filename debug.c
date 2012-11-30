//===============================================
// debug.c
//
// Definition of debugging helper functions
//===============================================

#include "debug.h"

void debug_printf(const char *fmt, ...)
{
    va_list args;

    if(DEBUG)
    {    
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);        
    }
}
