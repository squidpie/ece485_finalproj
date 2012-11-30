//===============================================
// cachestats.c
//
// Implements cache stat functions
//===============================================

#include "cachestats.h"

void cachestat_print(CacheStats *s)
{
    printf("=====================================\n");
    printf("Cache Statistics:\n");

    printf("Total Reads: %d\n", s->cache_reads);
    printf("Read Hits: %d\n", s->cache_read_hits);
    printf("Read Misses: %d\n", s->cache_read_misses);

    printf("Total Writes: %d\n", s->cache_writes);
    printf("Write Hits: %d\n", s->cache_write_hits);
    printf("Write Misses: %d\n", s->cache_write_misses);
    printf("=====================================\n");
}

void cachestat_init(CacheStats *s)
{
   memset(s, 0, sizeof(CacheStats)); 
}
