#include "lru.h"
#include "cache.h"

void initDataLRU( void ){
	mask[0][0] = 0x3f;
	mask[0][1] = 0x38;
	mask[1][0] = 0x1f;
	mask[1][1] = 0x06;
	mask[2][0] = 0x2b;
	mask[2][1] = 0x01;
	mask[3][0] = 0x34;
	mask[3][1] = 0x3f;

}

void accessDataLRU( int way ) {
		

}

int getDataVictim( void ) {


}

void accessInstLRU( int way ) {


}

int getInstVictim( void ) {


}
