/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:43 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:44 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
