//-----------------------------------------------
// trace.c
//
// trace structure definition
//-----------------------------------------------

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
