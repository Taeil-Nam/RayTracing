/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:37 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:38 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec)
{
	rec->front_face = vec3_dot(r->dir, o_n) < 0;
	if (rec->front_face)
		rec->normal = o_n;
	else
		rec->normal = vec3_mul_scalar(o_n, -1);
}

void	swap_d(double *left, double *right)
{
	double	tmp;

	tmp = *right;
	*right = *left;
	*left = tmp;
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		perror("Error\nxmalloc");
		exit(1);
	}
	return (p);
}
