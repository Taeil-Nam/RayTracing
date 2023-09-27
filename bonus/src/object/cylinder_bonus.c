/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:32 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:30:33 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_bonus.h"

t_aabb	cylinder_b_box(void *object)
{
	t_cylinder	*cy;
	t_aabb		cy_box;
	t_point3	c_top;

	cy = (t_cylinder *)object;
	c_top = vec3_add(cy->center, vec3_mul_scalar(cy->axis, cy->height));
	cy_box.p_min.x = fmin(cy->center.x - cy->diameter * 0.5,
			c_top.x - cy->diameter * 0.5);
	cy_box.p_min.y = fmin(cy->center.y - cy->diameter * 0.5,
			c_top.y - cy->diameter * 0.5);
	cy_box.p_min.z = fmin(cy->center.z - cy->diameter * 0.5,
			c_top.z - cy->diameter * 0.5);
	cy_box.p_max.x = fmax(cy->center.x + cy->diameter * 0.5,
			c_top.x + cy->diameter * 0.5);
	cy_box.p_max.y = fmax(cy->center.y + cy->diameter * 0.5,
			c_top.y + cy->diameter * 0.5);
	cy_box.p_max.z = fmax(cy->center.z + cy->diameter * 0.5,
			c_top.z + cy->diameter * 0.5);
	return (cy_box);
}

void	cal_abc_cy(double constants[3], t_ray *r, t_cylinder *cy)
{
	t_vec3	ray_d;
	t_vec3	oc;

	ray_d = r->dir;
	oc = vec3_sub(r->orig, cy->center);
	constants[0] = vec3_dot(ray_d, ray_d) - pow(vec3_dot(ray_d, cy->axis), 2);
	constants[1] = vec3_dot(ray_d, oc) - vec3_dot(ray_d, cy->axis)
		* vec3_dot(oc, cy->axis);
	constants[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->axis), 2)
		- pow(cy->diameter * 0.5, 2);
}

bool	cylinder_side_hit(t_ray *r, t_hit_rec *rec, t_cylinder *cy)
{
	t_vec3	outward_normal;
	double	constants[3];
	double	p_height;

	cal_abc_cy(constants, r, cy);
	if (quadratic_formular(constants, rec) == false)
		return (false);
	p_height = vec3_dot(vec3_sub(ray_at(*r, rec->root), cy->center), cy->axis);
	if (p_height > cy->height || p_height < 0)
		return (false);
	rec->t = rec->root;
	rec->max_t = rec->t;
	rec->p = ray_at(*r, rec->t);
	outward_normal = vec3_unit(vec3_sub(vec3_sub(rec->p, cy->center),
				vec3_mul_scalar(cy->axis, p_height)));
	set_face_normal(r, outward_normal, rec);
	get_cylinder_uv(outward_normal, rec, p_height, cy);
	if (cy->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &cy->mat.t.bmp_img)));
	rec->mat = &cy->mat;
	return (true);
}

bool	cylinder_cap_hit(t_ray *r, t_hit_rec *rec,
	t_cylinder *cy, t_point3 center)
{
	double		numer;
	double		denomi;
	double		root;

	numer = vec3_dot(cy->axis, vec3_sub(center, r->orig));
	denomi = vec3_dot(cy->axis, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < rec->min_t || rec->max_t < root)
		return (false);
	if (vec3_length(vec3_sub(ray_at(*r, root), center))
		> cy->diameter * 0.5)
		return (false);
	rec->t = root;
	rec->max_t = rec->t;
	rec->p = ray_at(*r, rec->t);
	set_face_normal(r, cy->axis, rec);
	get_cylinder_uv(cy->axis, rec,
		vec3_length(vec3_sub(cy->center, center)), cy);
	if (cy->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &cy->mat.t.bmp_img)));
	rec->mat = &cy->mat;
	return (true);
}

bool	cylinder_hit(t_ray *r, t_hit_rec *rec, void *object)
{
	t_cylinder	*cy;
	t_point3	p_top;
	bool		side;
	bool		top;
	bool		bottom;

	cy = (t_cylinder *)object;
	p_top = vec3_add(cy->center, vec3_mul_scalar(cy->axis, cy->height));
	side = cylinder_side_hit(r, rec, cy);
	top = cylinder_cap_hit(r, rec, cy, p_top);
	bottom = cylinder_cap_hit(r, rec, cy, cy->center);
	return (side || top || bottom);
}
