/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:22 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:23 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "bvh_bonus.h"

void	set_cone(t_hittable *new_object, t_point3 center,
		t_point3 top, double radius)
{
	new_object->object = (t_cone *)xmalloc(sizeof(t_cone));
	new_object->type = cone;
	((t_cone *)(new_object->object))->center = center;
	((t_cone *)(new_object->object))->top = top;
	((t_cone *)(new_object->object))->radius = radius;
	((t_cone *)(new_object->object))->axis = vec3_sub(center, top);
	((t_cone *)(new_object->object))->n_axis = vec3_unit(vec3_sub(center, top));
}

int	init_cone(t_hittable *new_object, char **data)
{
	t_point3	center;
	t_point3	top;
	double		radius;
	int			atod_errno;
	int			is_inf;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 5
		|| data_to_point(data[1], &center) == -1
		|| data_to_point(data[2], &top) == -1
		|| check_nan_in_vec3(vec3_unit(vec3_sub(center, top))))
		return (-1);
	radius = ft_atod(data[3], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (ft_strequal(data[4], INF) == 1)
		is_inf = 1;
	else if (ft_strequal(data[4], NOT_INF) == 1)
		is_inf = 0;
	else
		return (-1);
	set_cone(new_object, center, top, radius);
	((t_cone *)(new_object->object))->is_inf = is_inf;
	return (1);
}
