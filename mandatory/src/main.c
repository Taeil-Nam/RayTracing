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

void	write_phong_color(t_color color, t_data *image, int i, int j)
{
	double	scale;
	int		pixel;

	color.x = clamp((color.x), 0.0, 0.999);
	color.y = clamp((color.y), 0.0, 0.999);
	color.z = clamp((color.z), 0.0, 0.999);
	pixel = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8)
		+ ((int)(255.999 * color.z));
	my_mlx_pixel_put(image, i, DEFAULT_IMAGE_HGT - j - 1, pixel);
}

void	path_trace(t_data *image, t_hittable *bvh, t_camera *cam)
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
		printf("\rScanlines remaining : %d\n", j); // 1줄 줄여야되는 경우 평가할 때 지우기
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			r = get_ray(cam,
							(double)(i) / (DEFAULT_IMAGE_WID - 1),
							(double)(j) / (DEFAULT_IMAGE_HGT - 1));
			vec3_init(&color);
			s = 0;
			while (light_lst[s] != NULL)
				color = vec3_add(color, phong_color(r, cam, bvh, light_lst[s++]));
			color = vec3_mul_scalar(color, 1 / (double)s);
			write_phong_color(color, image, i++, j);
		}
		j--;
	}
}


int	print_image(t_hittable *bvh, t_camera *cam, t_sphere **light_lst)
{
	int		pixel;
	double	sample_per_pixel;
	t_vars	vars;
	t_data	image;

	minirt_init(&image, &vars);
	//path_trace(&image, bvh, cam);
	phong_trace(&image, bvh, cam, light_lst);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}

t_sphere	**make_light_lst(t_hittable **hittables)
{
	int			count;
	int			i;
	t_sphere	*tmp;
	t_sphere	**light_lst;

	count = 0;
	i = 0;
	while (hittables[i] != NULL)
	{
		tmp = (t_sphere *)(hittables[i++]->object);
		if (tmp->mat.mat_type == light)
			count++;
	}
	light_lst = (t_sphere **)xmalloc(sizeof(t_sphere *) * (count + 1));
	i = 0;
	count = 0;
	while (hittables[i] != NULL)
	{
		tmp = (t_sphere *)(hittables[i++]->object);
		if (tmp->mat.mat_type == light)
			light_lst[count++] = tmp;
	}
	light_lst[count] = NULL;
	return (light_lst);
}

int	main(int argc, char *argv[])
{
	t_list		*list;
	t_camera	cam;
	t_hittable	*bvh;
	t_hittable	**hittables;
	t_sphere	**light_lst;

	list = NULL;
	if (argc != 2)
		return (0);
	if (minirt_parser(argv[1], &list, &cam) == -1)
	{
		printf("Error\nminiRT: map Error!\n");
		return (-1);
	}
	hittables = list_to_hittable_arr(list);
	light_lst = make_light_lst(hittables);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &cam, light_lst);
	return (0);
}
