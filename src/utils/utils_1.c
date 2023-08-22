#include <math.h>

unsigned int	custom_rand(void)
{
	static unsigned long long int	seed = 1;
	const unsigned long long int	a = 6364136223846793005ULL;
	const unsigned long long int	c = 1ULL << 30;
	const unsigned long long int	m = 1ULL << 62;

	seed = (a * seed + c) % m;
	return ((unsigned int)(seed >> 32));
}

double	random_double(void)
{
	return (custom_rand() / (4294967295 + 1.0));
}
