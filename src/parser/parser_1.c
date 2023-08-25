#include "minirt.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void	check_extention(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
	{
		printf("Error\nminiRT: invalid file format: .rt\n");
		exit(-1);
	}
	if (filename[len - 1] != 't')
	{
		printf("Error\nminiRT: invalid file format: .rt\n");
		exit(-1);
	}
	if (filename[len - 2] != 'r')
	{
		printf("Error\nminiRT: invalid file format: .rt\n");
		exit(-1);
	}
	if (filename[len - 3] != '.')
	{
		printf("Error\nminiRT: invalid file format: .rt\n");
		exit(-1);
	}
}

int	data_processing(char *line, t_list **list, t_camera *camera)
{
	char	**data;
	int		ret;

	data = ft_split(line, ' ');
	if (data == NULL)
	{
		perror("miniRT:");
		exit(-1);
	}
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
	int			len;
	char		*line;

	check_extention(filename);
	rt_fd = open(filename, O_RDONLY);
	if (rt_fd == -1)
	{
		perror("Error\nminiRT");
		exit(-1);
	}
	while (1)
	{
		line = get_next_line(rt_fd);
		if (line == NULL)
			break ;
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strequal(line, "\n") == 1)
			continue ;
		if (data_processing(line, list, camera) == -1)
		{
			//free -> node free하는 것 생각보다 까다로움 타고타고 들어가야함
			return (-1);
		}
		free(line);
	}
	return (1);
}
