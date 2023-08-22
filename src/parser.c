#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "material.h"
#include "texture.h"
#include "libft.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

int	ambient_data(char **data, t_camera *cam)
{
	double	ratio;
	t_color	rgb;
	int		atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 3)
		return (-1);
	ratio = ft_atod(data[1], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (data_to_rgb(data[2], &rgb) == -1)
		return (-1);
	set_camera_image(rgb, ratio, cam);
	return (1);
}

int	camera_data(char **data, t_camera *cam)
{
	t_point3	look_from;
	t_vec3		dir;
	double		hfov;

	if (count_element_2pt_arr(data) != 4)
		return (-1);
	if (data_to_point(data[1], &look_from) == -1)
		return (-1);
	if (data_to_point(data[2], &dir) == -1)
		return (-1);
	hfov = ft_atoi(data[3]);
	set_camera_pos(look_from, dir, hfov, cam);
	return (1);
}

int	light_data(char **data, t_list **list);

int	sphere_data(char **data, t_list **list)
{
	t_sphere	*new_sphere;

	if (count_element_2pt_arr(data) != 4)
		return (-1);
	
}
// int	plane_data(char **data, t_list **list);
// int	cylinder_data(char **data, t_list **list);

int	data_processing(char *line, t_list *list, t_camera *camera)
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
	// else
		ret = -1;
	ft_double_free(data);
	return (ret);
}

int	minirt_parser(const char *filename, t_list *list, t_camera *camera)
{
	int			rt_fd;
	char		*line;

	rt_fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(rt_fd);
		if (line == NULL)
		{
			perror("get_next_line error");
			exit(-1);
		}
		if (data_processing(line, list, camera) == -1)
		{
			//free -> node free하는 것 생각보다 까다로움 타고타고 들어가야함
			return (-1);
		}
		free(line);
	}
}