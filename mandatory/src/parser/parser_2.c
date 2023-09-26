#include "minirt.h"
#include "bvh.h"
#include "object.h"

int	ambient_data(char **data, t_world *world)
{
	double	ratio;
	t_color	rgb;
	int		atod_errno;

	atod_errno = 0;
	if (world->is_ambient_in_map == true)
		return (-1);
	else
		world->is_ambient_in_map = true;
	if (count_element_2pt_arr(data) != 3)
		return (-1);
	ratio = ft_atod(data[1], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (data_to_rgb(data[2], &rgb) == -1)
		return (-1);
	set_camera_image(rgb, ratio, &world->cam);
	return (1);
}

int	camera_data(char **data, t_world *world)
{
	t_point3	look_from;
	t_vec3		dir;
	double		hfov;

	if (world->is_camera_in_map == true)
		return (-1);
	else
		world->is_camera_in_map = true;
	if (count_element_2pt_arr(data) != 4)
		return (-1);
	if (data_to_point(data[1], &look_from) == -1)
		return (-1);
	if (data_to_point(data[2], &dir) == -1)
		return (-1);
	dir = vec3_unit(dir);
	if (check_nan_in_vec3(dir))
		return (-1);
	hfov = ft_atoi(data[3]);
	if (hfov < 0 || hfov > 180)
		return (-1);
	set_camera_pos(look_from, dir, hfov, &world->cam);
	return (1);
}

int	light_data(char **data, t_list **list, t_world *world)
{
	t_hittable	*new_object;
	t_point3	center;
	double		ratio;
	t_color		rgb;
	int			atod_errno;

	atod_errno = 0;
	if (world->is_light_in_map == true)
		return (-1);
	else
		world->is_light_in_map = true;
	if (count_element_2pt_arr(data) != 4
		|| data_to_point(data[1], &center) == -1)
		return (-1);
	ratio = ft_atod(data[2], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR
		|| data_to_rgb(data[3], &rgb) == -1)
		return (-1);
	new_object = (t_hittable *)xmalloc(sizeof(t_hittable));
	new_object->object = light_constructor(center, ratio, rgb);
	new_object->center = ((t_sphere *)new_object->object)->center;
	new_object->hit = sphere_hit;
	new_object->b_box = sphere_b_box;
	ft_lstadd_back(list, ft_lstnew(new_object));
	return (1);
}
