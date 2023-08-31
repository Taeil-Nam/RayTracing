/* vec3_random, vec3_random_mm, random_in_unit_sphere, random_unit */

#include "vec3.h"

double	random_double(void);
double	random_double_mm(double min, double max);

t_vec3	vec3_random(void)
{
	t_vec3	v;

	v.x = random_double();
	v.y = random_double();
	v.z = random_double();
	return (v);
}

t_vec3	vec3_random_mm(double min, double max)
{
	t_vec3	v;

	v.x = random_double_mm(min, max);
	v.y = random_double_mm(min, max);
	v.z = random_double_mm(min, max);
	return (v);
}

t_vec3	vec3_random_in_unit_sphere(void)
{
	t_vec3	point;

	while (true)
	{
		point = vec3_random_mm(-1, 1);
		if (vec3_squared(point) >= 1)
			continue ;
		return (point);
	}
}

t_vec3	vec3_random_unit(void)
{
	return (vec3_unit(vec3_random_in_unit_sphere()));
}

