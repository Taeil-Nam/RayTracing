/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:59 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:01 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "bvh_bonus.h"

int	object_constructor(char **data, t_list **list, t_minirt *minirt)
{
	t_hittable	*new_object;
	int			ret;

	new_object = (t_hittable *)xmalloc(sizeof(t_hittable));
	if (init_object(new_object, data[0]) == -1)
	{
		free_hittables(new_object);
		return (-1);
	}
	if (new_object->type == sphere)
		ret = sphere_initializer(new_object, data, minirt);
	else if (new_object->type == cylinder)
		ret = cylinder_initializer(new_object, data, minirt);
	else if (new_object->type == plane)
		ret = plane_initializer(new_object, data, minirt);
	else if (new_object->type == cone)
		ret = cone_initializer(new_object, data, minirt);
	else
		ret = -1;
	if (ret == -1)
		free_hittables(new_object);
	else
		ft_lstadd_back(list, ft_lstnew(new_object));
	return (ret);
}

int	world_constructor(char *line, t_list **list, t_minirt *minirt)
{
	char	**data;
	int		ret;

	data = ft_split_white(line);
	if (data == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (data[0] == NULL)
		ret = 1;
	else if (ft_strequal(AMBIENT, data[0]))
		ret = ambient_data(data, minirt);
	else if (ft_strequal(CAMERA, data[0]))
		ret = camera_data(data, minirt);
	else if (ft_strequal(LIGHT, data[0]))
		ret = light_data(data, list, minirt);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
