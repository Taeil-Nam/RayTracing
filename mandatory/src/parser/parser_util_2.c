#include "minirt.h"

bool	check_nan_in_vec3(t_vec3 v)
{
	if (isnan(v.x) == 1 || isnan(v.y) == 1 || isnan(v.z) == 1)
		return (true);
	return (false);
}
