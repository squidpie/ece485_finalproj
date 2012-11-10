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
	
	stats = statsAddr;
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
	
	stats = statsAddr;
}

void cache_read(int address){
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
			hit = 1;
			L1D.stats->cache_read_hits++;
			data = L1D.sets[index].data[i] & offset_mask;
			update_LRU(L1D.sets[index], i);
		}
	}

	// If cache miss, evict and write to cache, get data from L2
	if (!hit) {
		L1D.stats->cache_read_misses++;
		if (victim < 0) victim = evict_LRU(L1D.sets[index]);
		L1D.sets[index].line_tags[victim] = readTag;
		L1D.sets[index].data[victim] = L2_read(address);
		data = L1D.sets[index].data[victim] & offset_mask;
	}
	
	return data;
}