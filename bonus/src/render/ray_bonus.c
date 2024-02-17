#include "minirt_bonus.h"

t_point3	ray_at(t_ray ray, double t)
{
	t_point3	ray_at;

	ray_at = vec3_add(ray.orig, vec3_mul_scalar(ray.dir, t));
	return (ray_at);
}

t_ray	get_ray(t_camera *cam, double s, double t)
{
	t_ray	ret;

	ret.orig = cam->center;
	ret.dir.x = cam->lower_left_corner.x + cam->horizontal.x * s + \
				cam->vertical.x * t - cam->center.x;
	ret.dir.y = cam->lower_left_corner.y + cam->horizontal.y * s + \
				cam->vertical.y * t - cam->center.y;
	ret.dir.z = cam->lower_left_corner.z + cam->horizontal.z * s + \
				cam->vertical.z * t - cam->center.z;
	return (ret);
}
