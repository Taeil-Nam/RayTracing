#include "minirt.h"
#include "texture.h"

int	init_solid(t_texture *tex, char **data)
{
	t_color	rgb;

	if (count_element_2pt_arr(data) != 2)
		return (-1);
	if (data_to_rgb(data[1], &rgb) == -1)
		return (-1);
	//bmp image 씌우기
	tex->rgb = rgb;
	tex->bmp_img = NULL;
	tex->img = NULL;
	tex->tex_type = solid;
	tex->value = solid_value;
	return (1);
}

int	init_texture(t_texture *tex, char *line)
{
	int		ret;
	char	**data;

	data = ft_split_white(line);
	if (data == NULL || data[0] == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (ft_strequal(SOLID, data[0]))
		ret = init_solid(tex, data);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
