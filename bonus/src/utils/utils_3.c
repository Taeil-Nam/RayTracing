#include "minirt.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		perror("xmalloc");
		exit(-1);
	}
	return (p);
}
