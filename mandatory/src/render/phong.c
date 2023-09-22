#include "minirt.h"
#include "object.h"
#include "bvh.h"
#include "vec3.h"
#include "ray.h"

t_color	diffuse_color(t_hit_rec *rec, t_sphere *l, t_ray *p_to_light)
{
	double	theta;
	t_color	diffuse;

	theta = clamp(vec3_dot(rec->normal, p_to_light->dir), 0, 1);
	diffuse = vec3_mul_scalar(l->mat.t.rgb, theta);
	return (diffuse);
}

t_color	specular_color(t_ray *r, t_ray *p_to_light, t_hit_rec *rec, t_sphere *l)
{
	t_vec3		view_r;
	t_vec3		reflect_r;
	double		spec;

	view_r = vec3_unit(vec3_mul_scalar(r->dir, -1));
	reflect_r = vec3_reflect(vec3_mul_scalar(p_to_light->dir, -1), rec->normal);
	spec = pow(fmax(vec3_dot(view_r, reflect_r), 0.0), KSN);
	return (vec3_mul_scalar(vec3_mul_scalar(l->mat.t.rgb, KS), spec));
}

bool	is_in_shadow(t_hittable *bvh, t_hit_rec *rec,
		t_ray *p_to_light, t_sphere *l)
{
	t_hit_rec	light_rec;
	double		length;

	length = vec3_length(vec3_sub(l->center, p_to_light->orig));
	light_rec.min_t = 0.001;
	light_rec.max_t = length;
	if (hit_bvh(&light_rec, p_to_light, bvh)
		&& light_rec.mat->mat_type != light
		&& light_rec.mat != rec->mat)
		return (true);
	return (false);
}

t_color	phong_color(t_ray r, t_common common, t_sphere *l)
{
	t_hit_rec	rec;
	t_color		phong;
	t_color		ads[3];
	t_ray		p_to_light;
	t_color		p_color;

	ads[0] = vec3_mul_scalar(common.cam->a_background, common.cam->a_ratio);
	rec.min_t = 0.001;
	rec.max_t = INFINITY;
	if (!hit_bvh(&rec, &r, common.bvh) || rec.mat->mat_type == light)
		return (ads[0]);
	p_color = rec.mat->t.value(&rec, rec.mat->t.rgb);
	if (l == NULL)
		return (vec3_mul_vec3(ads[0], p_color));
	p_to_light.orig = rec.p;
	p_to_light.dir = vec3_unit(vec3_sub(l->center, p_to_light.orig));
	if (is_in_shadow(common.bvh, &rec, &p_to_light, l))
		return (vec3_add(vec3_instant(0, 0, 0), vec3_mul_scalar(p_color, 0.1)));
	ads[1] = diffuse_color(&rec, l, &p_to_light);
	ads[2] = specular_color(&r, &p_to_light, &rec, l);
	phong = vec3_add(vec3_mul_vec3(vec3_add(ads[0], ads[1]), p_color), ads[2]);
	return (phong);
}
