/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:31 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:31:34 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* near_zero, print, reflect, instant, init */

#include <stdio.h>
#include <math.h>
#include "vec3.h"

bool	vec3_near_zero(t_vec3 v)
{
	const double	s = 1e-8;

	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

void	vec3_print(t_vec3 v)
{
	printf("vecter | x = %.3f, y = %.3f, z = %.3f\n", v.x, v.y, v.z);
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul_scalar(n, vec3_dot(v, n) * 2)));
}

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
