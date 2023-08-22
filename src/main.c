#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include "minirt.h"
#include "vec3.h"

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

int print_image()
{
	int		color;
	t_vars	vars;
	t_data	image;

	int img_width = 1920;
	int img_height = 1080;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	for (int i = 0 ; i < img_height - 1 ; ++i)
	{
		for (int j = 0 ; j < img_width - 1; ++j)
		{
			double r = (double)(img_width - j) / (img_width - 1);
			double g = (double)(i) / (img_height - 1);
			double b = 1;
			color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
			my_mlx_pixel_put(&image, j, i, color);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0); // close button press event
	mlx_loop(vars.mlx);
	return (0);
}

/* vec3 test function */
void	vec3_test(void)
{
	t_vec3	v1, v2, v3;

	v1.x = v1.y = v1.z = 1;
	v2.x = v2.y = v2.z = 2;
	v3.x = v3.y = v3.z = 3;

	/* vec3_1 */
	v1 = vec3_add(v2, v3);
	vec3_print(v1);
	v1 = vec3_sub(v3, v2);
	vec3_print(v1);
	v1 = vec3_mul_vec3(v3, v2);
	vec3_print(v1);
	v1 = vec3_mul_scalar(v2, 5);
	vec3_print(v1);
}

// main function!
int	main()
{
	/* vec3 test */
	vec3_test();

	/* main logic */
	print_image();
	return (0);
}
