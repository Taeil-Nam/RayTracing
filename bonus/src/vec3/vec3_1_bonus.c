/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:59 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:33:13 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_bonus.h"

t_vec3	vec3_add(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x + right.x;
	v.y = left.y + right.y;
	v.z = left.z + right.z;
	return (v);
}

t_vec3	vec3_sub(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x - right.x;
	v.y = left.y - right.y;
	v.z = left.z - right.z;
	return (v);
}

t_vec3	vec3_mul_vec3(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x * right.x;
	v.y = left.y * right.y;
	v.z = left.z * right.z;
	return (v);
}

t_vec3	vec3_mul_scalar(t_vec3 left, double right)
{
	t_vec3	v;

	v.x = left.x * right;
	v.y = left.y * right;
	v.z = left.z * right;
	return (v);
}
