#include "L2.h"

int L2_fetch(double hitRate) {
	double weight = (double)rand()/(double)RAND_MAX;
	return ((weight - hitRate) < 0);
}
