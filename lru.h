#ifndef _LRU_H
#define _LRU_H

#include "cache.h"
#include "debug.h"

uint8_t dataMask[4][2];

void initDataLRU( void );

void accessDataLRU( int, DataCacheSet * );
int getDataVictim( DataCacheSet * );

void accessInstLRU( int, InstrCacheSet * );
int getInstVictim( InstrCacheSet *);


#endif //_LRU_H
