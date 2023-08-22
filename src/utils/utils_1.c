#include <math.h>
#include <stdlib.h>

#define PHI 0x9e3779b9

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}
