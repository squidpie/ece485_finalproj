//===============================================
// traceread.h
//
// Trace reader module
//===============================================

#ifndef __TRACEREAD_H__
#define __TRACEREAD_H__

#include <stdio.h>
#include <string.h>

#include "trace.h"

#define TRACELINELENGTH 40

static FILE *tracestream;
static char tracebuffer[TRACELINELENGTH];

int open_trace( char *filename );
void close_trace();
int read_next(Trace *t);

static int parse_line(char *buffer, Trace *t);

static const char *tok_delim = "\t \n\r";

static char straction[256];
static char straddr[256];

#endif //__TRACEREAD_H__
