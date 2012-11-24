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


int main()
{
    //init trace struct
    Trace t;
    t.traceType = 0;
    t.address = 0;

	uint8_t data;	

	// Instruction Cache Stats
	CacheStats L1Istats;
	
	// Data Cache stats
	CacheStats L1Dstats;
	
	//init L2 cache stats
	CacheStats L2stats;
	cache_i_init(&L1Istats);
	cache_d_init(&L1Dstats);
	L2_init(&L2stats);
   open_trace("traces/test1.trace");

    while(!next_trace(&t))
    {
        printf("Action: %d Addr: %x\n", t.traceType, t.address);
	    switch (t.traceType) {
				case READ:
                    data = cache_read(t.address);
				    printf("L1 Data Read: %d\n", data);
                    break;
                case WRITE:
						  data = (t.address & 0xFF000000) >> 28;
						  cache_write(t.address,data);
                    printf("Write Data: %d\n", data);
                    break;
                case FETCH:
                    printf("L1 Instruction Fetch\n");
                    break;
                case INVALIDATE:
                    printf("Invalidate from L2\n");
                    break;
                case CLEAR:
                    printf("Cache Cleared\n");
                    break;
                case PRINT:
                    cache_print();
                    break;
                default:    
                    printf("Invald case!\n");
			}
    }
    close_trace();
}

