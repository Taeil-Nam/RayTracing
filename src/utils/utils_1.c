#include <math.h>

unsigned int	custom_rand(void)
{
	static unsigned long	seed = 1UL;
	const unsigned long		a = 1103515245UL;
	const unsigned long		c = 12345UL;
	const unsigned long		m = 1UL << 31;

	seed = (a * seed + c) % m;
	return (seed);
}

double	random_double(void)
{
	return (custom_rand() / (2147483647 + 1.0));
}

double	random_double_mm(double min, double max)
{
	return (min + ((max - min) * random_double()));
}
