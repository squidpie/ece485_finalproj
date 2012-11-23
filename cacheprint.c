#include <stdio.h>

#include "cache.h"

static void print_datacache(void);
static void print_instrcache(void);
static void print_icacheset(uint16_t index, InstrCacheSet * set);

void cache_print(void)
{
    printf("L1 Data Cache Contents: \n");        
    print_datacache();
    printf("L1 Instruction Cache Contents: \n");        
    print_instrcache();
}

//Static cache print functions
static void print_datacache(void)
{

}

static void print_instrcache(void)
{
    int i = 0;

    printf("Index\t\tLRU\t\t|Set 1\tTag\tData|Set2\tTag\tData\n");
    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
        //If any line in the set is valid, print the set
        if(L1I.sets[i].lines[0].tag & VALID || L1I.sets[i].lines[1].tag & VALID)
            print_icacheset(i, &L1I.sets[i]);
    }
}

static void print_icacheset(uint16_t index, InstrCacheSet * set)
{
   printf("0x%X\t\t%d\t\t\t0x%X\t0x%X\t0x%X\t0x%X\n",
    index, set->set_info, set->lines[0].tag, set->lines[0].data, set->lines[1].tag, set->lines[1].data);
}
