//===============================================
// cache.h
//
// Definition of cache module
//===============================================

#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdint.h>

#include "cachestats.h"

//Constants
#define ICACHE_NUMSETS 16384
#define DCACHE_NUMSETS 16384

#define ICACHE_ASSOC    2
#define DCACHE_ASSOC    4

// Cache Data Structure

// Constants for instruction cache masking
#define I_LRU 1 << 0    //mask for lru bit

// Constants for data cache masking
#define D_LRU01 1 << 0  //mask for LRU bit 01
#define D_LRU02 1 << 1  //mask for LRU bit 02
#define D_LRU03 1 << 2  //mask for LRU bit 03
#define D_LRU12 1 << 3  //mask for LRU bit 12
#define D_LRU13 1 << 4  //mask for LRU bit 13
#define D_LRU23 1 << 5  //mask for LRU bit 23

// Mask constants for finding Tag and Index values 
#define TAG     0xFFF00000      //mask for tag bits
#define INDEX   0xFFFC0         //mask for cache index
#define OFFSET  0x3F			// Mask for data index
#define VALID   0x8000		    // mask for valid from tag

#define TAG_SHIFT   24
#define INDEX_SHIFT 6

typedef struct {
	uint16_t tag;		// Tag is lower 12 bits, Valid is MSB
	uint8_t data[64];   // Byte addressable data 
} line;

typedef struct {

   line lines[2];		    // Line entries 
	uint8_t set_info;       // LRU bits 

} InstrCacheSet;

typedef struct {

    line lines[4];          //low order 12 bits for tag, 2 high order bits for mesi
    uint8_t set_info;       //LRU bits

} DataCacheSet;

typedef struct {

    InstrCacheSet sets[ICACHE_NUMSETS];
	CacheStats * stats;

} L1InstrCache;

typedef struct {

    DataCacheSet sets[DCACHE_NUMSETS]; 
	CacheStats  * stats;

} L1DataCache;

// Public Methods
// Initialization
void cache_i_init(CacheStats *statsAddr);
void cache_d_init(CacheStats *statsAddr);



// Cache Functions
uint32_t cache_read(int address);
void cache_write(int address, uint8_t data);
uint32_t cache_fetch(int address);
void cache_invalidate(int address);
void cache_clear(void);
void cache_print(void);

// Priate Methods

// Private Variables
static L1InstrCache L1I;
static L1DataCache L1D;

#endif //__CACHE_H__
