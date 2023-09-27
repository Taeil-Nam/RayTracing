/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:56 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:31:57 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "object_bonus.h"
#include "bvh_bonus.h"
#include "vec3_bonus.h"
#include "ray_bonus.h"

t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth)
{
	t_hit_rec	rec;
	t_color		basic;
	t_ray		scattered;
	t_color		attenuation;
	t_color		emit;

	basic.x = 0;
	basic.y = 0;
	basic.z = 0;
	rec.depth = depth;
	if (depth <= 0)
		return (basic);
	rec.min_t = 0.001;
	rec.max_t = INFINITY;
	if (!hit_bvh(&rec, &r, bvh))
		return (cam->a_background);
	emit = vec3_mul_scalar(rec.mat->emit(&rec, &rec.p, &rec.mat->t), LUMEN);
	if (!rec.mat->scatter(&r, &rec, &attenuation, &scattered))
		return (emit);
	return (vec3_add(emit, vec3_mul_vec3(attenuation,
				ray_color(scattered, cam, bvh, depth - 1))));
}
