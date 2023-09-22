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

int	data_processing(char *line, t_list **list, t_camera *camera)
{
	char	**data;
	int		ret;

	data = ft_split_white(line);
	if (data == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (data[0] == NULL)
		ret = 1;
	else if (ft_strequal(AMBIENT, data[0]))
		ret = ambient_data(data, camera);
	else if (ft_strequal(CAMERA, data[0]))
		ret = camera_data(data, camera);
	else if (ft_strequal(LIGHT, data[0]))
		ret = light_data(data, list);
	else if (ft_strequal(SPHERE, data[0]))
		ret = sphere_data(data, list);
	else if (ft_strequal(PLANE, data[0]))
		ret = plane_data(data, list);
	else if (ft_strequal(CYLINDER, data[0]))
		ret = cylinder_data(data, list);
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

int	minirt_parser(const char *filename, t_list **list, t_camera *camera)
{
	int			rt_fd;
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
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strequal(line, "\n") == 1)
			continue ;
		if (data_processing(line, list, camera) == -1)
		{
			free(line);
			ft_lstclear(list, free_hittables);
			return (-1);
		}
		free(line);
	}
	return (1);
}
