//===============================================
// cachestats.c
//
// Implements cache stat functions
//===============================================

#include "cachestats.h"
#include "debug.h"

void cachestat_print(CacheStats *s)
{
    printf("=====================================\n");
    printf("Cache Statistics:\n");

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
}

void cachestat_init(CacheStats *s)
{
   memset(s, 0, sizeof(CacheStats)); 
}
