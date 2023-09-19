#include "parser.h"
#include "bvh.h"

int	ambient_data(char **data, t_minirt *minirt)
{
	double	ratio;
	t_color	rgb;
	int		atod_errno;

	atod_errno = 0;
	if (minirt->is_ambient_in_map == false)
		minirt->is_ambient_in_map = true;
	else
		return (-1);
	if (count_element_2pt_arr(data) != 3)
		return (-1);
	ratio = ft_atod(data[1], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (data_to_rgb(data[2], &rgb) == -1)
		return (-1);
	set_camera_image(rgb, ratio, &minirt->cam);
	return (1);
}

t_sphere	*light_initializer(t_point3 center, double ratio, t_color rgb)
{
	t_sphere	*new_light;

	new_light = (t_sphere *)xmalloc(sizeof(t_sphere));
	new_light->center = center;
	new_light->radius = DEFAULT_SIZE;
	new_light->mat.mat_type = light;
	new_light->mat.emit = emit_light;
	new_light->mat.scatter = scatter_light;
	new_light->mat.t.bmp_img.img_ptr = NULL;
	new_light->mat.t.img.img_ptr = NULL;
	new_light->mat.t.rgb = vec3_mul_scalar(rgb, ratio);
	new_light->mat.t.tex_type = solid;
	new_light->mat.t.value = solid_value;
	return (new_light);
}

int	light_data(char **data, t_list **list)
{
	t_hittable	*new_object;
	t_point3	center;
	double		ratio;
	t_color		rgb;
	int			atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 4)
		return (-1);
	if (data_to_point(data[1], &center) == -1)
		return (-1);
	ratio = ft_atod(data[2], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (data_to_rgb(data[3], &rgb) == -1)
		return (-1);
	new_object = (t_hittable *)xmalloc(sizeof(t_hittable));
	new_object->object = light_initializer(center, ratio, rgb);
	new_object->center = ((t_sphere *)new_object->object)->center;
	new_object->hit = sphere_hit;
	new_object->b_box = sphere_b_box;
	ft_lstadd_back(list, ft_lstnew(new_object));
	return (1);
}
