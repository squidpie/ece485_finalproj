#include <stdio.h>

#include "cache.h"

static void print_datacache(void);
static void print_instrcache(void);
static void print_icacheset(uint16_t index, InstrCacheSet * set);
static void print_dcacheset(uint16_t index, DataCacheSet * set);

void cache_print(void)
{
    printf("L1 Data Cache Contents: \n");        
    print_datacache();
    //printf("L1 Instruction Cache Contents: \n");        
    //print_instrcache();
}

//Static cache print functions
static void print_datacache(void)
{
    int i = 0;
    DataCacheSet currentSet;

    printf("Index\t\tLRU");
    printf(" | \033[1mSet 1\033[0m\tTag\tData");
    printf(" | Set 2\tTag\tData");
    printf(" | Set 3\tTag\tData");
    printf(" | Set 4\tTag\tData\n");

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
        currentSet = L1D.sets[i];
        
        //If any lines are valid, print set
        if(currentSet.lines[0].tag & VALID
            || currentSet.lines[1].tag & VALID
            || currentSet.lines[2].tag & VALID
            || currentSet.lines[3].tag & VALID)
        {
            print_dcacheset(i, &currentSet);
        } 
    }
}

static void print_instrcache(void)
{
    int i = 0;
    InstrCacheSet currentSet;

    printf("Index\t\tLRU");
    printf(" | \033[1mSet 1\033[0m\tTag\tData");
    printf(" | Set 2\tTag\tData");

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
        currentSet = L1I.sets[i];
        //If any line in the set is valid, print the set
        if(currentSet.lines[0].tag & VALID
            || currentSet.lines[1].tag & VALID)
        {
            print_icacheset(i, &currentSet);
        }
    }
}

static void print_icacheset(uint16_t index, InstrCacheSet * set)
{
    printf("0x%X\t\t%d\t\t", index, set->set_info);
    printf("0x%X\t0x%X\t",
        set->lines[0].tag, set->lines[0].data);
    printf("0x%X\t0x%X\t",
        set->lines[1].tag, set->lines[1].data);
}

static void print_dcacheset(uint16_t index, DataCacheSet * set)
{
    printf("0x%X\t\t%d\t\t", index, set->set_info);
    printf("0x%X\t0x%X\t", 
        set->lines[0].tag, set->lines[0].data);
    printf("0x%X\t0x%X\t", 
        set->lines[1].tag, set->lines[1].data);
    printf("0x%X\t0x%X\t", 
        set->lines[2].tag, set->lines[2].data);
    printf("0x%X\t0x%X\t\n", 
        set->lines[3].tag, set->lines[3].data);
}
