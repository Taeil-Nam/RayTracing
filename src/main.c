#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

double random_double(void);

// mlx 구조체
typedef struct	s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

// image data 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// close button press event
int exit_hook()
{
	exit(0);
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth)
{
	t_hit_rec	rec;
	t_color		basic;
	t_ray		scattered;
	t_color		attenuation;
	t_color		emit;
	t_point3	dum;

	basic.x = 0;
	basic.y = 0;
	basic.z = 0;
	rec.depth = depth;
	if (depth <= 0)
        return (basic);
	if (!hit_bvh(&rec, 0.001, INFINITY, &r, bvh))
		return (vec3_mul_scalar(cam->a_background, cam->a_ratio));
	emit = vec3_mul_scalar(rec.mat->emit(&rec, &dum, &rec.mat->t), 2);
	if (!rec.mat->scatter(&r, &rec, &attenuation, &scattered))
		return (emit);
	return vec3_add(emit, vec3_mul_vec3(attenuation, ray_color(scattered,  cam, bvh, depth - 1)));
}

int print_image(t_hittable *bvh, t_camera *cam)
{
	int		pixel;
	double	sample_per_pixel;
	t_vars	vars;
	t_data	image;
	t_color	color;

	int img_width = DEFAULT_IMAGE_WID;
	int img_height = DEFAULT_IMAGE_HGT;

	sample_per_pixel = 200;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "miniRT");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

	for (int j = img_height-1; j >= 0; --j)
	{
		printf("\rScanlines remaining : %d\n", j);
		for (int i = 0; i < img_width; ++i)
		{
			color.x = 0;
			color.y = 0;
			color.z = 0;
			for (int s = 0; s < sample_per_pixel; s++)
			{
				double u = (i + random_double()) / (img_width - 1);
                double v = (j + random_double()) / (img_height - 1);
				t_ray r = get_ray(cam, u, v);
				color = vec3_add(color, ray_color(r, cam, bvh, 50));
			}
			double scale = 1.0 / (sample_per_pixel);
			color.x = clamp(sqrt(scale * color.x), 0.0, 0.999);
			color.y = clamp(sqrt(scale * color.y), 0.0, 0.999);
			color.z = clamp(sqrt(scale * color.z), 0.0, 0.999);
			pixel = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8) + ((int)(255.999 * color.z));
			my_mlx_pixel_put(&image, i, img_height - j - 1, pixel);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0); // close button press event
	mlx_loop(vars.mlx);
	return (0);
}

// main function!
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
