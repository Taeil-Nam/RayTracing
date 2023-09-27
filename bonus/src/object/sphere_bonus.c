/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:49 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:30:51 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_bonus.h"

t_aabb	sphere_b_box(void *object)
{
	t_sphere	*sp;
	t_aabb		sp_box;

	sp = (t_sphere *)object;
	sp_box.p_min.x = sp->center.x - sp->radius;
	sp_box.p_min.y = sp->center.y - sp->radius;
	sp_box.p_min.z = sp->center.z - sp->radius;
	sp_box.p_max.x = sp->center.x + sp->radius;
	sp_box.p_max.y = sp->center.y + sp->radius;
	sp_box.p_max.z = sp->center.z + sp->radius;
	return (sp_box);
}

bool	sphere_hit(t_ray *r, t_hit_rec *rec, void *object)
{
	t_sphere	*sp;
	t_vec3		oc;
	t_vec3		normal;
	double		constants[3];

	sp = (t_sphere *)object;
	oc = vec3_sub(r->orig, sp->center);
	constants[0] = vec3_squared(r->dir);
	constants[1] = vec3_dot(oc, r->dir);
	constants[2] = vec3_squared(oc) - sp->radius * sp->radius;
	if (quadratic_formular(constants, rec) == false)
		return (false);
	rec->t = rec->root;
	rec->max_t = rec->t;
	rec->p = ray_at(*r, rec->t);
	normal = vec3_unit(vec3_sub(rec->p, sp->center));
	set_face_normal(r, normal, rec);
	get_sphere_uv(normal, rec);
	if (sp->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &sp->mat.t.bmp_img)));
	rec->mat = &sp->mat;
	return (true);
}
