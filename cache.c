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
uint32_t cache_read(int address){
	uint16_t readTag = address & GET_TAG_FROM_ADDR >> TAG_OFFSET;
	int index = (address &  GET_INDEX_FROM_ADDR) >> INDEX_OFFSET;
	uint32_t offset_mask = 0xFF << ((address & GET_OFFSET_FROM_ADDR) * 8);
	int hit = 0;
	victim = -1;
	
	L1D.stats->cache_read++;
	
	//Search set at index for read tag
	for (i = 0; i < 4; i++){
		if (readTag == (L1D.sets[index].line_tags[i] & D_TAG)) {
		
			// check for invalid MESI state, evict this line if invalid and break to read from L2
			if (!(L1D.sets[index].line_tags[i] & D_MESI)) {
				victim = i;
				break;
			}
			// tag is valid, process read request
			hit = 1;
			L1D.stats->cache_read_hits++;
			update_LRU(L1D.sets[index], i);
			
			//Return data
			data = L1D.sets[index].data[i];
		}
	}

	// If cache miss, evict and write to cache, get data from L2
	if (!hit) {
		L1D.stats->cache_read_misses++;
		
		// get victim if miss wasn't from invalid state
		if (victim < 0) victim = evict_LRU(L1D.sets[index]);
		
		// update victim line tag and set MESI to exclusive, get data from L2
		L1D.sets[index].line_tags[victim] = (readTag + 0x8000);
		L1D.sets[index].data[victim] = L2_read(address);
		
		// Return data
		data = L1D.sets[index].data[victim];
	}
	
	return data;
}
