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
		return (cam->a_background);
	emit = rec.mat.emit(&rec, &dum, &rec.mat.t);
	if (!rec.mat.scatter(&r, &rec, &attenuation, &scattered))
		return (emit);
	return vec3_add(emit, vec3_mul_vec3(attenuation, ray_color(scattered,  cam, bvh, depth - 1)));
}

int print_image(t_hittable *bvh, t_camera *cam)
{
	int		pixel;
	int		sample_per_pixel;
	t_vars	vars;
	t_data	image;
	t_color	color;

	int img_width = DEFAULT_IMAGE_WID;
	int img_height = DEFAULT_IMAGE_HGT;

	sample_per_pixel = 10;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

	for (int i = 0 ; i < img_height - 1 ; ++i)
	{
		printf("\rScanlines remaining: %d \n", i);
		for (int j = 0 ; j < img_width - 1; ++j)
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
			pixel = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8) + ((int)(255.999 * color.z));
			my_mlx_pixel_put(&image, j, i, pixel);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0); // close button press event
	mlx_loop(vars.mlx);
	return (0);
}

/* vec3 test function */
double	random_double(void);
void	vec3_test(void)
{
	t_vec3	v1, v2, v3;

	v1.x = v1.y = v1.z = 1;
	v2.x = v2.y = v2.z = 2;
	v3.x = v3.y = v3.z = 3;

	/* vec3_1 */
	printf("=== vec3_1 ===\n");
	v1 = vec3_add(v2, v3);
	vec3_print(v1);
	v1 = vec3_sub(v3, v2);
	vec3_print(v1);
	v1 = vec3_mul_vec3(v3, v2);
	vec3_print(v1);
	v1 = vec3_mul_scalar(v2, 5);
	vec3_print(v1);

	/* vec3_2 */
	printf("=== vec3_2 ===\n");
	v2.x = 2;
	v2.y = 5;
	v2.z = 3;

	v3.x = 3;
	v3.y = 19;
	v3.z = 45;

	printf("v3 length = %.3f\n", vec3_length(v3));
	printf("v3 length_squared = %.3f\n", vec3_squared(v3));
	printf("v2, v3 dot = %.3f\n", vec3_dot(v2, v3));
	printf("v2, v3 cross = "); vec3_print(vec3_cross(v2, v3));
	printf("v3_unit = "); vec3_print(vec3_unit(v3));

	/* vec3_3 */
	printf("random vecter = "); vec3_print(vec3_random());
	printf("random vecter = "); vec3_print(vec3_random());
	printf("random vecter = "); vec3_print(vec3_random());
	printf("random vecter = "); vec3_print(vec3_random());
	printf("random vecter = "); vec3_print(vec3_random());

	printf("random_mm vecter = "); vec3_print(vec3_random_mm(-1, 1));
	printf("random_mm vecter = "); vec3_print(vec3_random_mm(-1, 1));
	printf("random_mm vecter = "); vec3_print(vec3_random_mm(-1, 1));
	printf("random_mm vecter = "); vec3_print(vec3_random_mm(-1, 1));
	printf("random_mm vecter = "); vec3_print(vec3_random_mm(-1, 1));

	printf("random_in unit sphere = "); vec3_print(vec3_random_in_unit_sphere());
	printf("random_in unit sphere = "); vec3_print(vec3_random_in_unit_sphere());
	printf("random_in unit sphere = "); vec3_print(vec3_random_in_unit_sphere());
	printf("random_in unit sphere = "); vec3_print(vec3_random_in_unit_sphere());
	printf("random_in unit sphere = "); vec3_print(vec3_random_in_unit_sphere());

	printf("random_unit = "); vec3_print(vec3_random_unit());
	printf("random_unit = "); vec3_print(vec3_random_unit());
	printf("random_unit = "); vec3_print(vec3_random_unit());
	printf("random_unit = "); vec3_print(vec3_random_unit());
	printf("random_unit = "); vec3_print(vec3_random_unit());
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
		perror("map Error!\n");
		return (0);
	}
	hittables = list_to_hittable_arr(list);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &cam);
	return (0);
}
