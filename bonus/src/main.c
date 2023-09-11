#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

int	print_image(t_hittable *bvh, t_minirt *minirt, t_sphere **light_lst)
{
	int		pixel;
	double	sample_per_pixel;

	if (minirt->illumination == PATH)
		path_trace(bvh, minirt);
	else
		phong_trace(bvh, minirt, light_lst);
	mlx_put_image_to_window(minirt->vars.mlx, minirt->vars.win, minirt->data.img, 0, 0);
	mlx_key_hook(minirt->vars.win, key_hook, &minirt->vars);
	mlx_hook(minirt->vars.win, 17, 0, exit_hook, 0);
	mlx_loop(minirt->vars.mlx);
	return (0);
}

void	minirt_init(t_minirt *minirt)
{
	minirt->vars.mlx = mlx_init();
	minirt->vars.win = mlx_new_window(minirt->vars.mlx,
						DEFAULT_IMAGE_WID, DEFAULT_IMAGE_HGT, "miniRT");
	minirt->data.img = mlx_new_image(minirt->vars.mlx,
						DEFAULT_IMAGE_WID, DEFAULT_IMAGE_HGT);
	minirt->data.addr = mlx_get_data_addr(minirt->data.img, 
								&minirt->data.bits_per_pixel,
								&minirt->data.line_length, &minirt->data.endian);
	minirt->sample_per_pixel = 10;
	minirt->depth = DEPTH;
	minirt->illumination = PATH;
	minirt->mode = RENDERING;
	minirt->is_ambient_in_map = false;
	minirt->is_camera_in_map = false;
}

int	main(int argc, char *argv[])
{
	t_list		*list;
	t_hittable	*bvh;
	t_hittable	**hittables;
	t_sphere	**light_lst;
	t_minirt	minirt;

	list = NULL;
	if (argc != 2)
		minirt_str_error_exit(ERR_ARGV_MSG);
	minirt_init(&minirt);
	if (minirt_parser(argv[1], &list, &minirt) == -1)
		minirt_str_error_exit(ERR_MAP);
	hittables = list_to_hittable_arr(list);
	light_lst = make_light_lst(hittables);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &minirt, light_lst);
	return (0);
}
