/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:51 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:52 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "bvh_bonus.h"
#include "object_bonus.h"
#include "vec3_bonus.h"
#include "ray_bonus.h"

t_color	aa_path(int i, int j, t_minirt *minirt, t_hittable *bvh)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < minirt->sample_per_pixel)
	{
		r = get_ray(&minirt->cam,
				(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
				(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, ray_color(r, &minirt->cam, bvh, minirt->depth));
	}
	return (color);
}

t_color	aa_phong(int i, int j, t_common *common)
{
	t_ray	r;
	t_color	color;
	int		s;

	s = 0;
	vec3_init(&color, 0, 0, 0);
	while (s++ < common->minirt->sample_per_pixel)
	{
		r = get_ray(&common->minirt->cam,
				(i + random_double()) / (DEFAULT_IMAGE_WID - 1),
				(j + random_double()) / (DEFAULT_IMAGE_HGT - 1));
		color = vec3_add(color, phong_color(r, common));
	}
	return (color);
}
