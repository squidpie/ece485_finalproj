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

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
        L1I.sets[i].line_tags[0] = 0;
        L1I.sets[i].line_tags[1] = 0;

        L1I.sets[i].set_info = 0;        
    }
	
	L1I.stats = statsAddr;
}

void cache_d_init(CacheStats * statsAddr)
{
    int i = 0;

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
        L1D.sets[i].line_tags[0] = 0;
        L1D.sets[i].line_tags[1] = 0;
        L1D.sets[i].line_tags[2] = 0;
        L1D.sets[i].line_tags[3] = 0;

        L1D.sets[i].set_info = 0;        
    }
	
	L1D.stats = statsAddr;
}


/* takes input of address and outputs data
 TODO: address decomposition needs work
 TODO: LRU functions not implemented yet
 TODO: Written without Psuedocode, 
	   this should be remedied and then this algorithim verified
*/
uint8_t cache_read(int address){
	uint16_t readTag = (address & TAG) >> TAG_OFFSET;
	uint16_t index = (address &  INDEX) >> INDEX_OFFSET;
	uint8_t offset = address & OFFSET;
	uint8_t data;

	int hit = 0;
	int victim;
	
	L1D.stats->cache_read++;
	
	//Search set at index for read tag
	for (i = 0; i < DCACHE_ASSOC; i++){
		if (readTag == (L1D.sets[index].line[i].tag)) {
		
			// tag is valid, process read request
			hit = 1;
			L1D.stats->cache_read_hits++;
			//update_LRU(L1D.sets[index], i);
			
			//Return data
			data = L1D.sets[index].line[i].data[offset];
		}
	}

	// If cache miss, evict and write to cache, get data from L2
	if (!hit) {
		L1D.stats->cache_read_misses++;
		
		// get victim if miss wasn't from invalid state
		victim = 0 //evict_LRU(L1D.sets[index]);
		
		// update victim line tag and set MESI to exclusive, get data from L2
		L1D.sets[index].line[victim].tag = readTag;
		L2_read(address, &L1D.sets[index].line[victim].data);
		
		// Return data
		data = L1D.sets[index].line[victim].data[offset];
	}
	
	return data;
}
