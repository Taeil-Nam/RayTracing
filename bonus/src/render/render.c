#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

t_color	anti_aliasing_path(int i, int j, t_minirt *minirt, t_hittable *bvh)
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

t_color	anti_aliasing_phong(int i, int j, t_minirt *minirt, t_hittable *bvh, t_sphere *l)
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
		color = vec3_add(color, phong_color(r, &minirt->cam, bvh, l));
	}
	return (color);
}

void	write_color(t_color color, t_data *image, int i, int j)
{
	double	scale;
	int		pixel;

	scale = 1.0 / (SAMPLE_PER_PIXEL);
	color.x = clamp(sqrt(scale * color.x), 0.0, 0.999);
	color.y = clamp(sqrt(scale * color.y), 0.0, 0.999);
	color.z = clamp(sqrt(scale * color.z), 0.0, 0.999);
	pixel = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8)
		+ ((int)(255.999 * color.z));
	my_mlx_pixel_put(image, i, DEFAULT_IMAGE_HGT - j - 1, pixel);
}

void	path_trace(t_hittable *bvh, t_minirt *minirt)
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
			color = anti_aliasing_path(i, j, minirt, bvh);
			write_color(color, &minirt->data, i++, j);
		}
		j--;
	}
}

void	phong_trace(t_hittable *bvh, t_minirt *minirt, t_sphere **light_lst)
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
			if (light_lst[0] == NULL)
				color = anti_aliasing_phong(i, j, minirt, bvh, light_lst[0]);
			else
			{
				while (light_lst[s] != NULL)
					color = vec3_add(color, anti_aliasing_phong(i, j, minirt, bvh, light_lst[s++]));
				color = vec3_mul_scalar(color, 1 / (double)s);
			}
			write_color(color, &minirt->data, i++, j);
		}
		j--;
	}
}
