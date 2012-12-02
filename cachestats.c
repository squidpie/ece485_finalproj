//===============================================
// cachestats.c
//
// Implements cache stat functions
//===============================================

#include "cachestats.h"
#include "debug.h"

void cachestat_print(CacheStats *s)
{
	 float accessTotal = s->cache_reads + s->cache_writes;
	 float hitTotal = s->cache_read_hits + s->cache_write_hits;
	 float missTotal = s->cache_read_misses + s->cache_write_misses;
	 float hitRate = (hitTotal/accessTotal) * 100;

    printf("=====================================\n");
    printf("Cache Statistics:\n");
	 printf("Total Accesses: %d\n",(int)(accessTotal));
	 printf("Total Hits: %d\n", (int)(hitTotal));
	 printf("Total Misses: %d\n", (int)(missTotal));
	 printf("Cache Hit Rate: %.2f%%\n\n", hitRate);
    printf("Total Reads: %lu\n", s->cache_reads);
    printf("Read Hits: %lu\n", s->cache_read_hits);
    printf("Read Misses: %lu\n", s->cache_read_misses);
    printf("\n");
    printf("Total Writes: %lu\n", s->cache_writes);
    printf("Write Hits: %lu\n", s->cache_write_hits);
    printf("Write Misses: %lu\n", s->cache_write_misses);
    debug_printf("\n");
    debug_printf("Total Invalidates: %lu\n", s->cache_invalidates);
    printf("=====================================\n");
    printf("\n");
}

void cachestat_init(CacheStats *s)
{
   memset(s, 0, sizeof(CacheStats)); 
}
