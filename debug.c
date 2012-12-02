//===============================================
// debug.c
//
// Definition of debugging helper functions
//===============================================

#include "debug.h"

void debug_printf(const char *fmt, ...)
{
    va_list args;

    if(DEBUG >= 1)
    {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);        
    }
}
void more_debug_printf(const char *fmt, ...)
{
    va_list args;

    if(DEBUG >= 2)
    {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);        
    }
}
void even_more_debug_printf(const char *fmt, ...)
{
    va_list args;

    if(DEBUG >= 3)
    {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);        
    }
}
