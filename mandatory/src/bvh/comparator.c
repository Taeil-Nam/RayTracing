/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:38 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:29:40 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int	compare_x(t_hittable *left, t_hittable *right)
{
	t_aabb		left_b;
	t_aabb		right_b;
	double		left_min_x;
	double		right_min_x;

	left_b = left->b_box(left->object);
	right_b = right->b_box(right->object);
	left_min_x = left_b.p_min.x;
	right_min_x = right_b.p_min.x;
	if (left_min_x == right_min_x)
		return (0);
	else if (left_min_x < right_min_x)
		return (-1);
	return (1);
}

int	compare_y(t_hittable *left, t_hittable *right)
{
	t_aabb		left_b;
	t_aabb		right_b;
	double		left_min_y;
	double		right_min_y;

	left_b = left->b_box(left->object);
	right_b = right->b_box(right->object);
	left_min_y = left_b.p_min.y;
	right_min_y = right_b.p_min.y;
	if (left_min_y == right_min_y)
		return (0);
	else if (left_min_y < right_min_y)
		return (-1);
	return (1);
}

int	compare_z(t_hittable *left, t_hittable *right)
{
	t_aabb		left_b;
	t_aabb		right_b;
	double		left_min_z;
	double		right_min_z;

	left_b = left->b_box(left->object);
	right_b = right->b_box(right->object);
	left_min_z = left_b.p_min.z;
	right_min_z = right_b.p_min.z;
	if (left_min_z == right_min_z)
		return (0);
	else if (left_min_z < right_min_z)
		return (-1);
	return (1);
}
