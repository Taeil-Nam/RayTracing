/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_minirt_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:34 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:35 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "bvh_bonus.h"
#include <fcntl.h>

int	check_extention_and_open(const char *filename)
{
	int	len;
	int	rt_fd;

	len = ft_strlen(filename);
	if (len < 3)
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 1] != 't')
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 2] != 'r')
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 3] != '.')
		minirt_str_error_exit(ERR_INV_FILE);
	rt_fd = open(filename, O_RDONLY);
	if (rt_fd == -1)
		minirt_error_exit();
	return (rt_fd);
}

int	data_processing(char *line, t_list **list, t_minirt *minirt)
{
	char	**data;
	int		ret;
	int		cnt;

	data = ft_split(line, '|');
	if (data == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (data[0] == NULL)
	{
		ft_double_free(data);
		return (1);
	}
	else
	{
		cnt = count_element_2pt_arr(data);
		if (cnt == 3)
			ret = object_constructor(data, list, minirt);
		else if (cnt == 1)
			ret = world_constructor(data[0], list, minirt);
		else
			ret = -1;
	}
	ft_double_free(data);
	return (ret);
}

void	free_hittables(void *hittable)
{
	t_hittable	*tmp;

	tmp = (t_hittable *)hittable;
	free(tmp->object);
	free(tmp);
}

int	minirt_parser(const char *filename, t_list **list, t_minirt *minirt)
{
	int			rt_fd;
	char		*line;

	rt_fd = check_extention_and_open(filename);
	while (1)
	{
		line = get_next_line(rt_fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (data_processing(line, list, minirt) == -1)
		{
			free(line);
			ft_lstclear(list, free_hittables);
			return (-1);
		}
		free(line);
	}
	if (minirt->is_ambient_in_map == false || minirt->is_camera_in_map == false)
	{
		ft_lstclear(list, free_hittables);
		return (-1);
	}
	return (1);
}
