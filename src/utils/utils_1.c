#include <math.h>

unsigned int	custom_rand(void)
{
	static unsigned long long int	seed = 1;
	const unsigned long long int	a = 6364136223846793005ULL;
	const unsigned long long int	c = 1ULL << 30;
	const unsigned long long int	m = 1ULL << 62;

	seed = (a * seed + c) % m;
<<<<<<< HEAD
	return ((unsigned int)(seed >> 31));
=======
	return ((unsigned int)(seed >> 32));
>>>>>>> aaf162c6471155903583324caba62616e41d849b
}

double	random_double(void)
{
<<<<<<< HEAD
	return (custom_rand() / (2147483647 + 1.0));
}

double	random_double_mm(double min, double max)
{
	return (min + ((max - min) * random_double()));
=======
	return (custom_rand() / (4294967295 + 1.0));
>>>>>>> aaf162c6471155903583324caba62616e41d849b
}
