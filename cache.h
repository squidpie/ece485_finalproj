//===============================================
// cache.h
//
// Definition of cache module
//===============================================

#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdint.h>

//Constants
#define ICACHE_NUMSETS 16384
#define DCACHE_NUMSETS 16384

// Cache Data Structure

// Constants for instruction cache masking
#define I_LRU 1 << 0    //mask for lru bit
#define I_VALID0 1 << 1 //mask for valid bit 0
#define I_VALID1 1 << 2 //mask for valid bit 1

// Constants for data cache masking
#define D_LRU01 1 << 0  //mask for LRU bit 01
#define D_LRU02 1 << 1  //mask for LRU bit 02
#define D_LRU03 1 << 2  //mask for LRU bit 03
#define D_LRU12 1 << 3  //mask for LRU bit 12
#define D_LRU13 1 << 4  //mask for LRU bit 13
#define D_LRU23 1 << 5  //mask for LRU bit 23

#define D_TAG 0x0FFF      //mask for tag bits
#define D_MESI 0xC000     //mask for mesi bits
#define D_MESI0 1 << 14  //mask for mesi bit 0
#define D_MESI1 1 << 15  //mask for mesi bit 1

typedef struct {

    uint16_t line_tags[2];      //12 bits tag, high order 4 bits always 0
    uint8_t set_info;           //valid and LRU bits 

} InstrCacheSet;

typedef struct {

    uint16_t line_tags[4];      //low order 12 bits for tag, 2 high order bits for mesi
    uint8_t set_info;           //LRU bits

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
void cache_i_init(void);
void cache_d_init(void);

// Cache Functions
uint32_t cache_read(int address);
void cache_write(int address);
void cache_fetch(int address);
void cache_invalidate(int address);
void cache_clear(void);
void cache_print(void);

// Priate Methods

// Private Variables
static L1InstrCache L1I;
static L1DataCache L1D;

#endif //__CACHE_H__
