#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth)
{
	t_hit_rec	rec;
	t_color		basic;
	t_ray		scattered;
	t_color		attenuation;
	t_color		emit;

	basic.x = 0;
	basic.y = 0;
	basic.z = 0;
	rec.depth = depth;
	if (depth <= 0)
		return (basic);
	if (!hit_bvh(&rec, 0.001, INFINITY, &r, bvh))
		return (vec3_mul_scalar(cam->a_background, cam->a_ratio));
	emit = vec3_mul_scalar(rec.mat->emit(&rec, &rec.p, &rec.mat->t), 2);
	if (!rec.mat->scatter(&r, &rec, &attenuation, &scattered))
		return (emit);
	return (vec3_add(emit, vec3_mul_vec3(attenuation,
				ray_color(scattered, cam, bvh, depth - 1))));
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

void	trace(t_data *image, t_hittable *bvh, t_camera *cam)
{
	t_color	color;
	t_ray	r;
	int		i;
	int		j;
	int		s;

	j = DEFAULT_IMAGE_HGT - 1;
	while (j >= 0)
	{
		printf("\rScanlines remaining : %d\n", j); // 1줄 줄여야되는 경우 평가할 때 지우기
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			vec3_init(&color);
			s = 0;
			while (s++ < SAMPLE_PER_PIXEL)
			{
				r = get_ray(cam,
						(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
						(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
				color = vec3_add(color, ray_color(r, cam, bvh, DEPTH));
			}
			write_color(color, image, i++, j);
		}
		j--;
	}
}

int	print_image(t_hittable *bvh, t_camera *cam)
{
	int		pixel;
	double	sample_per_pixel;
	t_vars	vars;
	t_data	image;

	minirt_init(&image, &vars);
	trace(&image, bvh, cam);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list		*list;
	t_camera	cam;
	t_hittable	*bvh;
	t_hittable	**hittables;

	list = NULL;
	if (argc != 2)
		return (0);
	if (minirt_parser(argv[1], &list, &cam) == -1)
	{
		printf("Error\nminiRT: map Error!\n");
		return (-1);
	}
	hittables = list_to_hittable_arr(list);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &cam);
	return (0);
}
