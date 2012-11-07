//===============================================
// cache.c
//
// Implementation of cache model
//===============================================

#include "cache.h"

//Cache Initialization
void cache_i_init(void)
{
    int i = 0;

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
        L1I.sets[i].line_tags[0] = 0;
        L1I.sets[i].line_tags[1] = 0;

        set_info = 0;        
    }
}

void cache_d_init(void)
{
    int i = 0;

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
        L1D.sets[i].line_tags[0] = 0;
        L1D.sets[i].line_tags[1] = 0;
        L1D.sets[i].line_tags[2] = 0;
        L1D.sets[i].line_tags[2] = 0;

        set_info = 0;        
    }
}
