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

t_color	black_color(void)
{
	t_color	black;

	black.x = 0;
	black.y = 0;
	black.z = 0;
	return (black);
}
