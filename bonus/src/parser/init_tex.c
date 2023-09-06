#include "minirt.h"
#include "texture.h"

int	init_solid(t_texture *tex, char **data, t_minirt *minirt)
{
	t_color	rgb;

	if (count_element_2pt_arr(data) != 2)
		return (-1);
	if (data_to_rgb(data[1], &rgb) == -1)
		return (-1);
	//bmp image 씌우기
	tex->rgb = rgb;
	tex->bmp_img.img_ptr = NULL;
	tex->img.img_ptr = NULL;
	tex->tex_type = solid;
	tex->value = solid_value;
	return (1);
}

int	init_checker(t_texture *tex, char **data, t_minirt *minirt)
{
	t_color	rgb;

	if (count_element_2pt_arr(data) != 2)
		return (-1);
	if (data_to_rgb(data[1], &rgb) == -1)
		return (-1);
	//bmp image 씌우기
	tex->rgb = rgb;
	tex->bmp_img.img_ptr = NULL;
	tex->img.img_ptr = NULL;
	tex->tex_type = checker;
	tex->value = checker_value;
	return (1);
}
int	init_image(t_texture *tex, char **data, t_minirt *minirt)
{
	if (count_element_2pt_arr(data) != 2)
		return (-1);
	tex->img.img_ptr = mlx_xpm_file_to_image(minirt->vars.mlx, data[1], 
							&tex->img.img_width, &tex->img.img_height);
	if (tex->img.img_ptr == NULL)
		return (-1);
	//bmp 처리
	tex->bmp_img.img_ptr = NULL;
	tex->tex_type = image;
	tex->value = img_value;
	return (1);
}

int	init_texture(t_texture *tex, char *line, t_minirt *minirt)
{
	int		ret;
	char	**data;

	data = ft_split_white(line);
	if (data == NULL || data[0] == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (ft_strequal(SOLID, data[0]))
		ret = init_solid(tex, data, minirt);
	else if (ft_strequal(CHECKER, data[0]))
		ret = init_checker(tex, data, minirt);
	else if (ft_strequal(IMAGE, data[0]))
		ret = init_image(tex, data, minirt);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
