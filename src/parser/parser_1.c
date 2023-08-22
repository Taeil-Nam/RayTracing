#include "minirt.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int	data_processing(char *line, t_list **list, t_camera *camera)
{
	char	**data;
	int		ret;

	data = ft_split(line, ' ');
	if (data == NULL)
	{
		perror(strerror(errno));
		exit(-1);
	}
	if (ft_strequal(AMBIENT, data[0]))
		ret = ambient_data(data, camera);
	else if (ft_strequal(CAMERA, data[0]))
		ret = camera_data(data, camera);
	else if (ft_strequal(LIGHT, data[0]))
		ret = light_data(data, list);
	else if (ft_strequal(SPHERE, data[0]))
		ret = sphere_data(data, list);
	// else if (ft_strequal(PLANE, data[0]))
	// 	ret = plane_data(data, list);
	// else if (ft_strequal(CYLINDER, data[0]))
	// 	ret = cylinder_data(data, list);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}

int	minirt_parser(const char *filename, t_list **list, t_camera *camera)
{
	int			rt_fd;
	char		*line;

	rt_fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(rt_fd);
		if (line == NULL)
			break ;
		if (data_processing(line, list, camera) == -1)
		{
			//free -> node free하는 것 생각보다 까다로움 타고타고 들어가야함
			return (-1);
		}
		free(line);
	}
	return (1);
}
