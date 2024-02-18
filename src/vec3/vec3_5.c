#include "vec3.h"

t_vec3	vec3_instant(double x, double y, double z)
{
	t_vec3	instant;

	instant.x = x;
	instant.y = y;
	instant.z = z;
	return (instant);
}

void	vec3_init(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
