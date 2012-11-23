//===============================================
// cache.c
//
// Implementation of cache model
//===============================================

#include "cache.h"

//Cache Initialization
void cache_i_init(CacheStats * statsAddr)
{
    int i = 0;
	int j = 0;

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
		for (j = 0; j < ICACHE_ASSOC; j ++) {
			L1I.sets[i].lines[j].tag = 0;
			memset(L1I.sets[i].lines[j].data,0,64) ;
		}
        L1I.sets[i].set_info = 0;        
    }
	printf("L1I address = %X\n", statsAddr);	
	L1I.stats = statsAddr;
}

void cache_d_init(CacheStats * statsAddr)
{
    int i = 0;
	int j = 0;

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
		for (j = 0; j < DCACHE_ASSOC; j++) { 
        	L1D.sets[i].lines[j].tag  = 0;
       	memset(L1D.sets[i].lines[j].data,0,64);
		}
        L1D.sets[i].set_info = 0;        
    }
	
	L1D.stats = statsAddr;
}


/* takes input of address and outputs data
*/
uint8_t cache_read(int address){
	uint16_t readTag = (address & TAG) >> TAG_SHIFT;
	uint16_t index = (address &  INDEX) >> INDEX_SHIFT;
	uint8_t offset = address & OFFSET;
	uint8_t data;

	int hit = 0;
	int victim;
	int i = 0;

	L1D.stats->cache_reads++;
	
	//Search set at index for read tag
	for (i = 0; i < DCACHE_ASSOC; i++){
		if (readTag == (L1D.sets[index].lines[i].tag)) {
		
			// tag is valid, process read request
			hit = 1;
			L1D.stats->cache_read_hits++;
			//update_LRU(L1D.sets[index], i);
			
			//Return data
			data = L1D.sets[index].lines[i].data[offset];
		}
	}

	// If cache miss, evict and write to cache, get data from L2
	if (!hit) {
		L1D.stats->cache_read_misses++;
		
		// get victim if miss wasn't from invalid state
		victim = 0; //evict_LRU(L1D.sets[index]);
		
		// update victim line tag and set MESI to exclusive, get data from L2
		L1D.sets[index].lines[victim].tag = readTag;
		L2_read(address, &L1D.sets[index].lines[victim].data);
		
		// Return data
		data = L1D.sets[index].lines[victim].data[offset];
	}
	
	return data;
}
