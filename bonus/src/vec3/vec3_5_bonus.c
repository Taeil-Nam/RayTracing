/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:33:03 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:33:04 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_bonus.h"

t_vec3	vec3_instant(double x, double y, double z)
{
	t_vec3	instant;

	instant.x = x;
	instant.y = y;
	instant.z = z;
	return (instant);
}

void	vec3_init(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
