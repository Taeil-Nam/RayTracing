#include "ray.h"

t_point3	ray_at(t_ray ray, double t)
{
	t_point3	ray_at;

	ray_at = vec3_add(ray.orig, vec3_mul_scalar(ray.dir, t));
	return (ray_at);
}
