/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:18 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:30:19 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
