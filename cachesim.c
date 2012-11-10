//===============================================
// cachesim.c
//
// Cache simulator
//===============================================

#include "traceread.h"
#include "L2.h"
#include "cachestats.h"
#include "cache.h"

int main()
{
    //init trace struct
    Trace t;
    t.traceType = 0;
    t.address = 0;
	
	// Instruction Cache Stats
	CacheStats L1Istats;
	
	// Data Cache stats
	CacheStats L1Dstats;
	
	//init L2 cache stats
	CacheStats L2stats;
	
	cache_i_init(&L1I);
	cache_d_init(&L1D);
	L2_init(&L2stats);

    open_trace("traces/test1.trace");

    while(!next_trace(&t))
        printf("Action: %d Addr: %x\n", t.traceType, t.address);
		

    close_trace();
}

