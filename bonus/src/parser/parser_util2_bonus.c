#include "parser_bonus.h"

bool	check_nan_in_vec3(t_vec3 v)
{
	if (isnan(v.x) == 1 || isnan(v.y) == 1 || isnan(v.z) == 1)
		return (true);
	return (false);
}

bool	is_value_btw_one(t_vec3 vec)
{
	if (fabs(vec.x) > 1
		|| fabs(vec.y) > 1 || fabs(vec.z) > 1)
		return (false);
	return (true);
}
