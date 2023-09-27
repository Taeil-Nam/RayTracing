/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:14 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:16 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "material_bonus.h"

int	init_diffuse(t_material *mat, char **data)
{
	if (count_element_2pt_arr(data) != 1)
		return (-1);
	mat->mat_type = diffuse;
	mat->emit = emit_general;
	mat->scatter = scatter_diffuse;
	mat->fuzz = 0;
	mat->ir = 0;
	return (1);
}

int	init_metal(t_material *mat, char **data)
{
	double	fuzz;
	int		atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 2)
		return (-1);
	fuzz = ft_atod(data[1], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	if (fuzz > 1)
		fuzz = 1;
	mat->mat_type = metal;
	mat->emit = emit_general;
	mat->scatter = scatter_metal;
	mat->fuzz = fuzz;
	mat->ir = 0;
	return (1);
}

int	init_dielectric(t_material *mat, char **data)
{
	double	ir;
	int		atod_errno;

	atod_errno = 0;
	if (count_element_2pt_arr(data) != 2)
		return (-1);
	ir = ft_atod(data[1], &atod_errno);
	if (atod_errno == ATOD_FORMAT_ERR)
		return (-1);
	mat->mat_type = dielectric;
	mat->emit = emit_general;
	mat->scatter = scatter_dielectric;
	mat->fuzz = 0;
	mat->ir = ir;
	return (1);
}

int	init_material(t_material *mat, char *mat_line)
{
	int		ret;
	char	**data;

	data = ft_split_white(mat_line);
	if (data == NULL || data[0] == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (ft_strequal(DIFFUSE, data[0]))
		ret = init_diffuse(mat, data);
	else if (ft_strequal(METAL, data[0]))
		ret = init_metal(mat, data);
	else if (ft_strequal(DIELECTRIC, data[0]))
		ret = init_dielectric(mat, data);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
