//===============================================
// cache.h
//
// Definition of cache module
//===============================================

#include <stdint.h>

//Constants
#define ICACHE_NUMSETS 16384
#define DCACHE_NUMSETS 16384

// Cache Data Structure

typedef struct {

    uint16_t[2] line_tags;    
    uint8_t set_info;

} InstrCacheSet;

typedef struct {

    uint16_t[4] lineTags;
    uint8_t set_info;

} DataCacheSet;


typedef struct {

    InstrCacheSet[ICACHE_NUMSETS] sets;

} L1InstrCache;

typedef struct {

    DataCacheSet[DCACHE_NUMSETS] sets;

} L1DataCache;

// Public Methods
void cache_read(int address);
void cache_write(int address);
void cache_fetch(int address);
void cache_invalidate(int address);
void cache_clear(void);
void cache_print(void);

// Priate Methods

// Private Variables

