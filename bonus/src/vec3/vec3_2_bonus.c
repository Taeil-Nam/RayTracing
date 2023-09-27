/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:33:00 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:33:01 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* length, squared, dot, cross, unit */

#include "vec3_bonus.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_squared(v)));
}

double	vec3_squared(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	vec3_dot(t_vec3 left, t_vec3 right)
{
	return ((left.x * right.x) + (left.y * right.y) + (left.z * right.z));
}

t_vec3	vec3_cross(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = (left.y * right.z) - (left.z * right.y);
	v.y = (left.z * right.x) - (left.x * right.z);
	v.z = (left.x * right.y) - (left.y * right.x);
	return (v);
}

t_vec3	vec3_unit(t_vec3 v)
{
	t_vec3	v_unit;
	double	v_length;

	v_length = vec3_length(v);
	v_unit.x = v.x / v_length;
	v_unit.y = v.y / v_length;
	v_unit.z = v.z / v_length;
	return (v_unit);
}
