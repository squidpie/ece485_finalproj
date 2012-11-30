//===============================================
// cachesim.c
//
// Cache simulator
//===============================================

#include "traceread.h"
#include "trace.h"
#include "L2.h"
#include "cachestats.h"
#include "cache.h"
#include "debug.h"



int main(int argc, char ** argv)
{
	char traceFile[1024];
    argc > 1 ? strcpy(traceFile,argv[1]): strcpy(traceFile,"traces/default.trace");
	//init trace struct
    Trace t;
    t.traceType = 0;
    t.address = 0;

	uint8_t data;	

    //Init debug mode
    DEBUG = 1;

	// Instruction Cache Stats
	CacheStats L1Istats;
	
	// Data Cache stats
	CacheStats L1Dstats;
	
	//init L2 cache stats
	CacheStats L2stats;


    //init stats structs
    cachestat_init(&L1Istats);
    cachestat_init(&L1Dstats);
    cachestat_init(&L2stats);


	cache_i_init(&L1Istats);
	cache_d_init(&L1Dstats);
	L2_init(&L2stats);
    open_trace(traceFile);


    debug_printf("Reading trace file: %s\n", traceFile);
    
    while(!next_trace(&t))
    {
        debug_printf("Action: %d Addr: %X\n", t.traceType, t.address);
	    switch (t.traceType) {
				case READ:
                    data = cache_read(t.address);
				    debug_printf("L1 Data Read. Address: 0x%X Data: %d\n", t.address, data);
                    break;
                case WRITE:
					data = (t.address & 0xFF000000) >> 28;
				    cache_write(t.address,data);
                    debug_printf("L1 Data Write. Address: 0x%X Data: %d\n", t.address, data);
                    break;
                case FETCH:
                    data = cache_fetch(t.address);
                    debug_printf("L1 Instruction Fetch. Address: 0x%X Data: %d\n", t.address, data);
                    break;
                case INVALIDATE:
                    debug_printf("Invalidate from L2. Address: 0x%X\n", t.address);
                    break;
                case CLEAR:
                    debug_printf("Cache Cleared\n");
                    break;
                case PRINT:
                    cache_print();
                    break;
                default:    
                    debug_printf("Invald case!\n");
			}
    }
    close_trace();

    //Print stats
    printf("L1 Instruction Cache:\n");
    cachestat_print(&L1Istats);
    printf("L1 Data Cache:\n");
    cachestat_print(&L1Dstats);

}

