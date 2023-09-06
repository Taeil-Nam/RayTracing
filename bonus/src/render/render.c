#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

t_color	anti_aliasing_path(int i, int j, t_camera *cam, t_hittable *bvh)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < SAMPLE_PER_PIXEL)
	{
		r = get_ray(cam,
						(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
						(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, ray_color(r, cam, bvh, DEPTH));
	}
	return (color);
}

t_color	anti_aliasing_phong(int i, int j, t_camera *cam, t_hittable *bvh, t_sphere *l)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < SAMPLE_PER_PIXEL)
	{
		r = get_ray(cam,
		(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
		(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, phong_color(r, cam, bvh, l));
	}
	return (color);
}

void	path_trace(t_data *image, t_hittable *bvh, t_camera *cam)
{
	t_color	color;
	int		i;
	int		j;

	j = DEFAULT_IMAGE_HGT - 1;
	while (j >= 0)
	{
		printf("\rScanlines remaining : %d\n", j);
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			color = anti_aliasing_path(i, j, cam, bvh);
			write_color(color, image, i++, j);
		}
		j--;
	}
}

void	phong_trace(t_data *image, t_hittable *bvh, t_camera *cam, t_sphere **light_lst)
{
	t_color	color;
	t_ray	r;
	int		i;
	int		j;
	int		s;

	j = DEFAULT_IMAGE_HGT - 1;
	while (j >= 0)
	{
		printf("\rScanlines remaining : %d\n", j);
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			vec3_init(&color, 0, 0, 0);
			s = 0;
			while (light_lst[s] != NULL)
				color = anti_aliasing_phong(i, j, cam, bvh, light_lst[s++]);
			color = vec3_mul_scalar(color, 1 / (double)s);
			write_color(color, image, i++, j);
		}
		j--;
	}
}
