#ifndef __L2_H__
#define __L2_H__

#include "cachestats.h"
#include <stdlib.h>


#define L2_read(address, data)	_L2_service(address, data, NULL, 1)
#define L2_write(address, data)	_L2_service(address, NULL, NULL, 0)
#define L2_init(stats)	_L2_service(0, NULL, stats, 0)

#define L2_HIT_RATE	0.8


uint32_t _L2_service(uint32_t, uint8_t *, CacheStats *, int);

#endif // __L2_H__
