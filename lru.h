#ifndef _LRU_H
#define _LRU_H

#define DATA_ACC_1	0x

uint_8 dataMask[4][2];

void initDataLRU( void );

void accessDataLRU( int );
int getDataVictim( void );

void accessInstLRU( int ):
int getInstVictim( void);


#endif
