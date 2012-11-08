#include "L2.h"
#include <stdio.h>

uint32_t _L2_service(uint32_t address, CacheStats * pStats, int RW) {
	
	static CacheStats * stats;
	uint32_t mask = 0xF << 31;
	uint32_t reversed = 0x0;
	int i = 31;
	int adjust = 0;
	
	if (pStats != NULL) { 
		stats = pStats;
		return 0;
	}
	
	if (RW) stats->cache_reads++;
	else stats->cache_writes++;
	
	double weight = (double)rand()/(double)RAND_MAX;
	
	if ((weight - L2_HIT_RATE) < 0) {
		if (RW) stats->cache_read_hits++;
		else stats->cache_write_hits++;
	}
	else {
		if (RW) stats->cache_read_misses++;
		else stats->cache_write_misses++;
	}
	
	for(i = 31; i > 0;  i--) {
		printf("I: %d\n",i);
		printf("START: reversed: %X	  mask: %X\n",reversed, mask);
		reversed += ((address & mask) >> (i - adjust++));
		mask = mask >> 4;
		printf("END: reversed: %X	mask: %X\n",reversed, mask);
	}
	return reversed;
}
