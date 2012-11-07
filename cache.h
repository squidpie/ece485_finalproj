//===============================================
// cache.h
//
// Definition of cache module
//===============================================

void cache_read(int address);
void cache_write(int address);
void cache_fetch(int address);
void cache_invalidate(int address);
void cache_clear(void);
void cache_print(void);
