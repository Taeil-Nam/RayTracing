#include "minirt_bonus.h"
#include "bvh_bonus.h"
#include "object_bonus.h"
#include "vec3_bonus.h"
#include "ray_bonus.h"

t_thread	*threads_init(t_hittable *bvh, t_minirt *minirt,
							t_sphere **light_lst, t_common *common)
{
	t_thread	*threads;
	int			i;
	int			start;

	i = 0;
	start = 0;
	if (pthread_mutex_init(&common->print_mutex, NULL) != 0)
		minirt_error_exit();
	common->bvh = bvh;
	common->minirt = minirt;
	common->light_lst = light_lst;
	common->cnt = DEFAULT_IMAGE_HGT - 1;
	threads = (t_thread *)xmalloc(sizeof(t_thread) * THREAD_NUM);
	while (i < THREAD_NUM)
	{
		threads[i].common = common;
		threads[i].h_start = start;
		if (i == THREAD_NUM - 1)
			threads[i].h_end = DEFAULT_IMAGE_HGT - 1;
		else
			threads[i].h_end = start + DEFAULT_IMAGE_HGT / THREAD_NUM - 1;
		start = threads[i].h_end + 1;
		i++;
	}
	return (threads);
}

int	print_image(t_hittable *bvh, t_minirt *minirt, t_sphere **light_lst)
{
	t_thread	*threads;
	t_common	common;

	threads = threads_init(bvh, minirt, light_lst, &common);
	multi_threading(threads, minirt);
	free(threads);
	mlx_put_image_to_window(minirt->vars.mlx,
		minirt->vars.win, minirt->data.img, 0, 0);
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
	minirt->sample_per_pixel = SAMPLE_PER_PIXEL;
	minirt->depth = DEPTH;
	minirt->illumination = PHONG;
	minirt->mode = RENDERING;
	minirt->is_ambient_in_map = false;
	minirt->is_camera_in_map = false;
}

void	leaks(void)
{
	system("leaks -q $PPID");
}

int	main(int argc, char *argv[])
{
	t_list		*list;
	t_hittable	*bvh;
	t_hittable	**hittables;
	t_sphere	**light_lst;
	t_minirt	minirt;

	atexit(leaks);
	list = NULL;
	if (argc != 2)
		minirt_str_error_exit(ERR_ARGV_MSG);
	if (THREAD_NUM > DEFAULT_IMAGE_HGT)
		minirt_str_error_exit("Too small image.");
	minirt_init(&minirt);
	if (minirt_parser(argv[1], &list, &minirt) == -1)
		minirt_str_error_exit(ERR_MAP);
	hittables = list_to_hittable_arr(list);
	light_lst = make_light_lst(hittables);
	bvh = make_bvh(hittables, 0, ft_lstsize(list) - 1);
	ft_lstclear(&list, dummy);
	print_image(bvh, &minirt, light_lst);
	free_mem(bvh, hittables, light_lst);
	return (0);
}
