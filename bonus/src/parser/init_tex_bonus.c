/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:26 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:27 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "texture_bonus.h"

int	init_solid(t_texture *tex, char **data, t_minirt *minirt)
{
	t_color	rgb;

	if (count_element_2pt_arr(data) != 3)
		return (-1);
	if (data_to_rgb(data[1], &rgb) == -1)
		return (-1);
	if (ft_strequal(data[2], NO_BMP) != 1)
	{
		tex->bmp_img.img_ptr = mlx_xpm_file_to_image(minirt->vars.mlx, data[2],
				&tex->bmp_img.img_width, &tex->bmp_img.img_height);
		if (tex->bmp_img.img_ptr == NULL)
			return (-1);
		tex->bmp_img.data = (unsigned char *)mlx_get_data_addr(
				tex->bmp_img.img_ptr, &tex->bmp_img.bytes_per_pixel,
				&tex->bmp_img.bytes_per_scanline, &tex->bmp_img.endian);
		tex->bmp_img.bytes_per_pixel /= 8;
	}
	else
		tex->bmp_img.img_ptr = NULL;
	tex->rgb = rgb;
	tex->img.img_ptr = NULL;
	tex->tex_type = solid;
	tex->value = solid_value;
	return (1);
}

int	init_checker(t_texture *tex, char **data, t_minirt *minirt)
{
	t_color	rgb;

	if (count_element_2pt_arr(data) != 3)
		return (-1);
	if (data_to_rgb(data[1], &rgb) == -1)
		return (-1);
	if (ft_strequal(data[2], NO_BMP) != 1)
	{
		tex->bmp_img.img_ptr = mlx_xpm_file_to_image(minirt->vars.mlx, data[2],
				&tex->bmp_img.img_width, &tex->bmp_img.img_height);
		if (tex->bmp_img.img_ptr == NULL)
			return (-1);
		tex->bmp_img.data
			= (unsigned char *)mlx_get_data_addr(tex->bmp_img.img_ptr,
				&tex->bmp_img.bytes_per_pixel,
				&tex->bmp_img.bytes_per_scanline, &tex->bmp_img.endian);
		tex->bmp_img.bytes_per_pixel /= 8;
	}
	else
		tex->bmp_img.img_ptr = NULL;
	tex->rgb = rgb;
	tex->img.img_ptr = NULL;
	tex->tex_type = checker;
	tex->value = checker_value;
	return (1);
}

int	init_image(t_texture *tex, char **data, t_minirt *minirt)
{
	if (count_element_2pt_arr(data) != 3)
		return (-1);
	tex->img.img_ptr = mlx_xpm_file_to_image(minirt->vars.mlx, data[1],
			&tex->img.img_width, &tex->img.img_height);
	if (tex->img.img_ptr == NULL)
		return (-1);
	tex->img.data = (unsigned char *)mlx_get_data_addr(
			tex->img.img_ptr, &tex->img.bytes_per_pixel,
			&tex->img.bytes_per_scanline, &tex->img.endian);
	tex->img.bytes_per_pixel /= 8;
	tex->bmp_img.img_ptr = NULL;
	if (ft_strequal(data[2], NO_BMP) != 1)
	{
		tex->bmp_img.img_ptr = mlx_xpm_file_to_image(minirt->vars.mlx, data[2],
				&tex->bmp_img.img_width, &tex->bmp_img.img_height);
		if (tex->bmp_img.img_ptr == NULL)
			return (-1);
		tex->bmp_img.data = (unsigned char *)mlx_get_data_addr(
				tex->bmp_img.img_ptr, &tex->bmp_img.bytes_per_pixel,
				&tex->bmp_img.bytes_per_scanline, &tex->bmp_img.endian);
		tex->bmp_img.bytes_per_pixel /= 8;
	}
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
