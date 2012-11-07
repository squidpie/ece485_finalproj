#include "L2.h"

#include <stdlib.h>

int L2_fetch(double hitRate) {
	int i;
	int retv;
	double action;
	double weights[2] = {hitRate, 1 - hitRate};
	
	// Init random double action between 0 and 1
	action = (double)rand()/(double)RAND_MAX;
	
	// return hit/miss using hitRate probability and random value action
	for (i = 0; i < 2; i++) {
		action -= weights[i];
		if (action < 0) {
			if (i == 0) retv = 1;
			else retv = 0;
			break;
		}
	}
	return retv;
}