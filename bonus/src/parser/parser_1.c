#include "minirt.h"
#include "bvh.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void	check_extention(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 1] != 't')
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 2] != 'r')
		minirt_str_error_exit(ERR_INV_FILE);
	if (filename[len - 3] != '.')
		minirt_str_error_exit(ERR_INV_FILE);
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
		return (1);
	cnt = count_element_2pt_arr(data);
	if (cnt == 3)
		ret = object_constructor(data, list, minirt);
	else if (cnt == 1)
		ret = world_constructor(data[0], list, minirt);
	else
		ret = -1;
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
	int			len;
	char		*line;

	check_extention(filename);
	rt_fd = open(filename, O_RDONLY);
	if (rt_fd == -1)
		minirt_error_exit();
	while (1)
	{
		line = get_next_line(rt_fd);
		if (line == NULL)
			break ;
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (data_processing(line, list, minirt) == -1)
		{
			free(line);
			ft_lstclear(list, free_hittables);
			return (-1);
		}
		free(line);
	}
	return (1);
}
