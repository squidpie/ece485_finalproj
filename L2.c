#include "L2.h"
#include <stdio.h>

uint32_t _L2_service(uint32_t address, CacheStats * statsAddr, int RW) {
	
	static CacheStats * L2_stats;
	uint32_t mask = 0xF << 28;
	uint32_t reversed = 0x0;
	int shift = 28;
	int i;
	
	if (statsAddr != NULL) { 
		L2_stats = statsAddr;
		return 0;
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
	
	if (RW) {
		for(i = 4; i > 0;  i--) {
			reversed += ((address & mask) >> shift);
			shift -= 8;
			mask = mask >> 4;
		}
		
		shift = 4;
		
		for (i = 4; i > 0; i--) {
			reversed += ((address & mask) << shift);
			shift += 8;
			mask = mask >> 4;
		}
	}	
	return reversed;
}
