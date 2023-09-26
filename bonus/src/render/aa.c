#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

t_color	aa_path(int i, int j, t_minirt *minirt, t_hittable *bvh)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < minirt->sample_per_pixel)
	{
		r = get_ray(&minirt->cam,
				(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
				(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, ray_color(r, &minirt->cam, bvh, minirt->depth));
	}
	return (color);
}

t_color	aa_phong(int i, int j, t_common *common)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < common->minirt->sample_per_pixel)
	{
		r = get_ray(&common->minirt->cam,
				(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
				(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, phong_color(r, common));
	}
	return (color);
}
