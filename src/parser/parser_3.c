#include "minirt.h"
#include "bvh.h"
#include "object.h"

int	sphere_data(char **data, t_list **list)
{
	t_hittable	*new_object;
	t_point3	center;
	double		radius;
	t_color		rgb;
	int			atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 4)
		return (-1);
	if (data_to_point(data[1], &center) == -1)
		return (-1);
	radius = ft_atod(data[2], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (data_to_rgb(data[3], &rgb) == -1)
		return (-1);
	new_object = (t_hittable *)malloc(sizeof(t_hittable));
	new_object->object = sphere_constructor(center, radius, rgb);
	//new_object->hit = sphere_hit;
	ft_lstadd_back(list, ft_lstnew(new_object));
	return (1);
}

// int	plane_data(char **data, t_list **list);
// int	cylinder_data(char **data, t_list **list);