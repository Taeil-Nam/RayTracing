/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:18 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:19 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "bvh_bonus.h"

int	init_sphere(t_hittable *new_object, char **data)
{
	t_point3	center;
	double		radius;
	int			atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 3)
		return (-1);
	if (data_to_point(data[1], &center) == -1)
		return (-1);
	radius = ft_atod(data[2], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	new_object->object = (t_sphere *)xmalloc(sizeof(t_sphere));
	new_object->type = sphere;
	((t_sphere *)(new_object->object))->center = center;
	((t_sphere *)(new_object->object))->radius = radius;
	return (1);
}

int	init_plane(t_hittable *new_object, char **data)
{
	t_point3	p;
	t_vec3		normal;

	if (count_element_2pt_arr(data) != 3)
		return (-1);
	if (data_to_point(data[1], &p) == -1)
		return (-1);
	if (data_to_point(data[2], &normal) == -1)
		return (-1);
	if (check_nan_in_vec3(normal) || !is_value_btw_one(normal))
		return (-1);
	new_object->object = (t_plane *)xmalloc(sizeof(t_plane));
	new_object->type = plane;
	((t_plane *)(new_object->object))->p = p;
	((t_plane *)(new_object->object))->n = vec3_unit(normal);
	return (1);
}

int	init_cylinder(t_hittable *new_object, char **data)
{
	t_point3	center;
	t_vec3		axis;
	double		diameter;
	double		height;
	int			atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 5)
		return (-1);
	if (data_to_point(data[1], &center) == -1)
		return (-1);
	if (data_to_point(data[2], &axis) == -1)
		return (-1);
	diameter = ft_atod(data[3], &atod_errno);
	height = ft_atod(data[4], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR || check_nan_in_vec3(axis)
		|| !is_value_btw_one(axis))
		return (-1);
	new_object->object = (t_cylinder *)xmalloc(sizeof(t_cylinder));
	new_object->type = cylinder;
	((t_cylinder *)(new_object->object))->center = center;
	((t_cylinder *)(new_object->object))->axis = vec3_unit(axis);
	((t_cylinder *)(new_object->object))->diameter = diameter;
	((t_cylinder *)(new_object->object))->height = height;
	return (1);
}

int	init_object(t_hittable *hittable, char *obj_line)
{
	int		ret;
	char	**data;

	data = ft_split_white(obj_line);
	if (data == NULL || data[0] == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (ft_strequal(SPHERE, data[0]))
		ret = init_sphere(hittable, data);
	else if (ft_strequal(PLANE, data[0]))
		ret = init_plane(hittable, data);
	else if (ft_strequal(CYLINDER, data[0]))
		ret = init_cylinder(hittable, data);
	else if (ft_strequal(CONE, data[0]))
		ret = init_cone(hittable, data);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
