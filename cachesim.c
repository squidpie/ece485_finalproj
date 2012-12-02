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
	int i;
	// set traceFile to null, parse cla for verbose and custom trace file
	strcpy(traceFile, "\0");
	for(i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i],"-v"))
		{
			// Enable debug print messages
			DEBUG = 1;
		}
		else if (!strcmp(argv[i],"-t")) 
		{
			// assign trace file
			strcpy(traceFile,argv[i+1]);
		}	
	}
	// if no trace file was assigned, assign default trace
	if (!strcmp(traceFile,"\0"))
	{
		strcpy(traceFile, "traces/default.trace");
	}

	//init trace struct
    Trace t;
    t.traceType = 0;
    t.address = 0;

	uint8_t data;	

    uint64_t traceCounter = 0;

	initDataLRU();
    //Init debug mode
    //DEBUG = 1;

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
	    switch (t.traceType) {
				case READ:
                    data = cache_read(t.address);
				    debug_printf("t%lu\t: L1 Data Read. Address: 0x%X Data: %d\n", traceCounter, t.address, data);
                    break;
                case WRITE:
					data = (t.address & 0xFF000000) >> 28;
				    cache_write(t.address,data);
                    debug_printf("t%lu\t: L1 Data Write. Address: 0x%X Data: %d\n", traceCounter, t.address, data);
                    break;
                case FETCH:
                    data = cache_fetch(t.address);
                    debug_printf("t%lu\t: L1 Instruction Fetch. Address: 0x%X Data: %d\n", traceCounter, t.address, data);
                    break;
                case INVALIDATE:
                    debug_printf("t%lu\t: Invalidate from L2. Address: 0x%X\n", traceCounter, t.address);
                    cache_invalidate(t.address);
                    break;
                case CLEAR:
                    debug_printf("t%lu\t: Cache Cleared\n", traceCounter);
                    break;
                case PRINT:
                    debug_printf("t%lu\t: Printing Cache\n", traceCounter);
                    cache_print();
                    break;
                default:
                    debug_printf("Invald case!\n");
			}
        traceCounter++;
    }
    close_trace();

    //Print stats
    printf("L1 Instruction Cache:\n");
    cachestat_print(&L1Istats);
    printf("L1 Data Cache:\n");
    cachestat_print(&L1Dstats);

}

