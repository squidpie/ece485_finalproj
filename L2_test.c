#include "L2.h"
#include "cachestats.h"


#include <stdlib.h>
#include <stdio.h>


int main (int argc, char * argv) {
	int i;
	CacheStats stats;
	uint32_t address = 0x12345678;
	uint32_t L2_data = 0;
	stats.cache_reads = 0;
	stats.cache_read_misses = 0;
	stats.cache_read_hits = 0;
	stats.cache_writes = 0;
	stats.cache_write_misses = 0;
	stats.cache_write_hits = 0;
	
	L2_init(&stats);
	
	srand( (unsigned)time(NULL) );
	
	for (i = 0; i < 10; i++ ){
		L2_write(address, L2_data);
		L2_data = L2_read(address);
		printf("L2 access to %X returned %X\n",address, L2_data);
		address += rand();
	}
	
	printf("Reads: %llu\nR Misses: %llu\nR Hits: %llu\nWrites: %llu\nW Misses: %llu\nW Hits: %llu\n", stats.cache_reads, stats.cache_read_misses, stats.cache_read_hits, stats.cache_writes, stats.cache_write_misses, stats.cache_write_hits);
	return 0;
}