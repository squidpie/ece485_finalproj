#include "lru.h"
#include "cache.h"

void initDataLRU( void ){
	// init set and clear masks for Data LRU state transition
	dataMask[0][0] = 0x3f;
	dataMask[0][1] = 0x38;
	dataMask[1][0] = 0x1f;
	dataMask[1][1] = 0x06;
	dataMask[2][0] = 0x2b;
	dataMask[2][1] = 0x01;
	dataMask[3][0] = 0x34;
	dataMask[3][1] = 0x00;

}

void accessDataLRU( int way, DataCacheSet * set ) {
		// apply set and clear mask to LRU state
		set->set_info  = set->set_info & dataMask[way][0] | dataMask[way][1];
		more_debug_printf("New Data LRU state: 0x%x\n",set->set_info);

}

int getDataVictim( DataCacheSet * set ) {
	int victim;
	// Check specific bit positions for 1's and 0's and return victim
	if (!(set->set_info & 0x38)) 
	{
		victim = 0;
	}
	else if (((set->set_info & 0x20) == 0x20) && (!(set->set_info & 0x03)))
	{
		victim = 1;
	}
	else if ((((set->set_info & 0x14) == 0x14)) && (!(set->set_info & 0x1)))
	{
		victim = 2;
	}
	else 
	{
		victim = 3; 
	}
	more_debug_printf("Evicted Data LRU way: %d\n", victim);
	accessDataLRU(victim, set);
	return victim;

}

void accessInstLRU( int way, InstrCacheSet * set ) {
	set->set_info = (~way & 0x1);
	more_debug_printf("New Instr LRU State: %d\n", set->set_info);

}

int getInstVictim( InstrCacheSet * set ) {
	more_debug_printf("Evicted Instr LRU way: %d\n", set->set_info);
	int victim = set->set_info;
	accessInstLRU(victim, set);
	return victim;

}
