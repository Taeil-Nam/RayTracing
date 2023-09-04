#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

/*
void	leaks()
{
	system("leaks -q $PPID");
}
*/

int	print_image(t_hittable *bvh, t_camera *cam, t_sphere **light_lst)
{
	int		pixel;
	double	sample_per_pixel;
	t_vars	vars;
	t_data	image;

	minirt_init(&image, &vars);
	path_trace(&image, bvh, cam);
	//phong_trace(&image, bvh, cam, light_lst);
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
	t_sphere	**light_lst;

	//atexit(leaks);
	list = NULL;
	if (argc != 2)
		minirt_str_error_exit(ERR_ARGV_MSG);
	if (minirt_parser(argv[1], &list, &cam) == -1)
		minirt_str_error_exit(ERR_MAP);
	hittables = list_to_hittable_arr(list);
	light_lst = make_light_lst(hittables);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &cam, light_lst);
	//free_all(bvh, hittables, light_lst);
	return (0);
}
