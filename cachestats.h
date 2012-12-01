//===============================================
// cachestats.h
//
// Defines structure to store cache usage stats
//===============================================

#ifndef __CACHESTATS_H__
#define __CACHESTATS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {

    uint64_t cache_reads;
    uint64_t cache_writes;

    uint64_t cache_read_hits;
    uint64_t cache_read_misses;

    uint64_t cache_write_hits;
    uint64_t cache_write_misses;

} CacheStats;

void cachestat_print(CacheStats *s);
void cachestat_init(CacheStats *s);

#endif //__CACHESTATS_H__
