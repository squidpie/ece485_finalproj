#include "L2.h"
#include <stdio.h>

uint32_t _L2_service(uint32_t address, CacheStats * pStats, int RW) {
	
	static CacheStats * stats;
	uint32_t mask = 0xF << 28;
	uint32_t reversed = 0x0;
	int i;
	int shift = 28;
	uint32_t temp;
	
	if (pStats != NULL) { 
		stats = pStats;
		return 0;
	}
	
	printf("RW: %d	Address: %X	stats: %d\n",RW,address, stats->cache_writes);
	
	(0) ? stats->cache_reads++ : stats->cache_writes++; 
	
	printf("RW: %d	Address: %X	stats: %d\n",RW,address, stats->cache_writes);
	double weight = (double)rand()/(double)RAND_MAX;
	
	if (((weight - L2_HIT_RATE) < 0)) {
		if (RW) stats->cache_read_hits++;
		else stats->cache_write_hits++;
	}
	else {
		if (RW) stats->cache_read_misses++;
		else stats->cache_write_misses++;
	}
	
	
	if (RW) {
		for(i = 4; i > 0;  i--) {
			temp = ((address & mask) >> shift);
			reversed += temp;
			shift -= 8;
			mask = mask >> 4;
		}
		shift = 4;
		for (i = 4; i > 0; i--) {
			temp = ((address & mask) << shift);
			reversed += temp;
			shift += 8;
			mask = mask >> 4;
		}
	}	
	return reversed;
}
