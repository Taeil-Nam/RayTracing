#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

int	print_image(t_world *world)
{
	t_vars		vars;
	t_data		image;

	minirt_init(&image, &vars);
	phong_trace(&image, world);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}

void	world_init(t_world *world)
{
	world->is_ambient_in_map = false;
	world->is_camera_in_map = false;
	world->is_light_in_map = false;
}

void	leaks(void)
{
	system("leaks -q $PPID");
}

int	main(int argc, char *argv[])
{
	t_list		*list;
	t_hittable	**hittables;
	t_world		world;

	atexit(leaks);
	list = NULL;
	if (argc != 2)
		minirt_str_error_exit(ERR_ARGV_MSG);
	world_init(&world);
	if (minirt_parser(argv[1], &list, &world) == -1)
		minirt_str_error_exit(ERR_MAP);
	hittables = list_to_hittable_arr(list);
	world.light_lst = make_light_lst(hittables);
	world.bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(&world);
	free_mem(&world, hittables);
	return (0);
}
