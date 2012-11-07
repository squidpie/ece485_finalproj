//-----------------------------------------------
// trace.h
//
// trace structure definition
//-----------------------------------------------

#ifndef __TRACE_H__
#define __TRACE_H__

enum TraceAction {
    READ = 0,
    WRITE = 1,
    FETCH = 2,
    INVALIDATE = 3,
    CLEAR = 8,
    PRINT = 9
};

typedef struct {
    unsigned int address;
    enum TraceAction traceType;
} Trace;

#endif //__TRACE_H__
