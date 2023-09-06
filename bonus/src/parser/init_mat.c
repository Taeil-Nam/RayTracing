#include "minirt.h"
#include "material.h"

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

int	init_material(t_material *mat, char *mat_line)
{
	int		ret;
	char	**data;

	data = ft_split_white(mat_line);
	if (data == NULL || data[0] == NULL)
		minirt_str_error_exit(ERR_MAP);
	if (ft_strequal(DIFFUSE, data[0]))
		ret = init_diffuse(mat, data);
	else
		ret = -1;
	ft_double_free(data);
	return (ret);
}
