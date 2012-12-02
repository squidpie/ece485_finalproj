#include "L2.h"

void _L2_service(uint32_t address, uint8_t * dataHead,  CacheStats * statsAddr, int RW) {
	
	static CacheStats * L2_stats;
	uint32_t mask = 0xF << 28;
	uint32_t reversed = 0x0;
	int shift = 28;
	uint8_t i;


	if (statsAddr != NULL) { 
		L2_stats = statsAddr;
		return;	
	}

	(RW) ? L2_stats->cache_reads++ : L2_stats->cache_writes++; 
	
	if ((((double)rand()/(double)RAND_MAX) - L2_HIT_RATE) < 0) {
		if (RW) L2_stats->cache_read_hits++;
		else L2_stats->cache_write_hits++;
	}
	else {
		if (RW) L2_stats->cache_read_misses++;
		else L2_stats->cache_write_misses++;
	}
	
	
	if (dataHead != NULL && RW) {
		//dataHead[0] = reversed;
		for (i = 0; i < 64; i++) {
			dataHead[i] = 0; 
		}
		dataHead[(address & OFFSET)] = (address & OFFSET);
	}
}
