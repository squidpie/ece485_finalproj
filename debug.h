//===============================================
// debug.h 
// 
// Definition of debugging helper functions
//===============================================

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdarg.h>
#include <stdio.h>

int DEBUG;

void debug_printf(const char *fmt, ...);

#endif //__DEBUG_H__
