/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:01 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:02 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "object_bonus.h"
#include "bvh_bonus.h"
#include "vec3_bonus.h"
#include "ray_bonus.h"

bool	is_in_shadow(t_hittable *bvh, t_hit_rec *rec,
		t_ray *p_to_light, t_sphere *l)
{
	t_hit_rec	light_rec;
	double		length;

	length = vec3_length(vec3_sub(l->center, p_to_light->orig));
	light_rec.min_t = 0.001f;
	light_rec.max_t = length;
	if (hit_bvh(&light_rec, p_to_light, bvh)
		&& light_rec.mat->mat_type != light
		&& light_rec.mat != rec->mat)
		return (true);
	return (false);
}

t_color	specular_and_diffuse(t_ray *r, t_ray *p_to_light
							, t_hit_rec *rec, t_sphere *l)
{
	t_vec3		view_r;
	t_vec3		reflect_r;
	double		spec;
	double		theta;
	t_color		diffuse;

	theta = clamp(vec3_dot(rec->normal, p_to_light->dir), 0.0, 1.0);
	diffuse = vec3_mul_scalar(l->mat.t.rgb, theta);
	view_r = vec3_unit(vec3_mul_scalar(r->dir, -1));
	reflect_r = vec3_reflect(vec3_mul_scalar(p_to_light->dir, -1), rec->normal);
	spec = pow(fmax(vec3_dot(view_r, reflect_r), 0.0), KSN);
	return (vec3_add(diffuse,
			vec3_mul_scalar(vec3_mul_scalar(l->mat.t.rgb, KS), spec)));
}

t_color	get_brightness(t_ray *r, t_hit_rec *rec, t_common *common)
{
	t_color	brightness;
	t_color	p_color;
	t_ray	p_to_light;
	int		i;

	i = 0;
	p_color = rec->mat->t.value(rec, &rec->mat->t.img, rec->mat->t.rgb);
	vec3_init(&brightness, 0, 0, 0);
	while ((common->light_lst[i]) != NULL)
	{
		p_to_light.orig = rec->p;
		p_to_light.dir = vec3_unit(
				vec3_sub(common->light_lst[i]->center, p_to_light.orig));
		if (is_in_shadow(common->bvh, rec, &p_to_light, common->light_lst[i]))
		{
			brightness = vec3_add(brightness,
					vec3_mul_scalar(vec3_mul_vec3(p_color,
							common->minirt->cam.a_background), 0.1));
			i++;
			continue ;
		}
		brightness = vec3_add(brightness, specular_and_diffuse(r,
					&p_to_light, rec, common->light_lst[i++]));
	}
	return (vec3_add(brightness, common->minirt->cam.a_background));
}

t_color	phong_color(t_ray r, t_common *common)
{
	t_hit_rec	rec;
	t_color		phong;
	t_color		ambient;
	t_color		p_color;

	ambient = common->minirt->cam.a_background;
	rec.min_t = 0.001;
	rec.max_t = INFINITY;
	if (!hit_bvh(&rec, &r, common->bvh) || rec.mat->mat_type == light)
		return (ambient);
	p_color = rec.mat->t.value(&rec, &rec.mat->t.img, rec.mat->t.rgb);
	phong = vec3_mul_vec3(get_brightness(&r, &rec, common), p_color);
	return (phong);
}
