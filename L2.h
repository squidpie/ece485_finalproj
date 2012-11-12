#ifndef __L2_H__
#define __L2_H__

#include "cachestats.h"
#include <stdlib.h>


#define L2_read(address)	_L2_service(address, NULL, 1)
#define L2_write(address, data)	_L2_service(address, NULL, 0)
#define L2_init(stats)	_L2_service(0, stats, 0)

#define L2_HIT_RATE	0.8


uint32_t _L2_service(uint32_t, CacheStats *, int);

#endif // __L2_H__
