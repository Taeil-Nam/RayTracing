#include "minirt.h"
#include "object.h"
#include "bvh.h"
#include "vec3.h"
#include "ray.h"

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
	spec = pow(clamp(vec3_dot(view_r, reflect_r), 0.0, 1.0), KSN);
	return (vec3_add(diffuse,
			vec3_mul_scalar(vec3_mul_scalar(l->mat.t.rgb, KS), spec)));
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

t_color	get_brightness(t_ray *r, t_hit_rec *rec, t_world *world)
{
	t_color		brightness;
	t_color		p_color;
	t_ray		p_to_light;
	t_sphere	*l;

	vec3_init(&brightness, 0, 0, 0);
	l = world->light_lst[0];
	if (l == NULL)
		return (vec3_add(brightness, world->cam.a_background));
	p_color = rec->mat->t.value(rec, rec->mat->t.rgb);
	p_to_light.orig = rec->p;
	p_to_light.dir = vec3_unit(vec3_sub(l->center, p_to_light.orig));
	if (is_in_shadow(world->bvh, rec, &p_to_light, l))
	{
		brightness = vec3_add(brightness,
				vec3_mul_scalar(vec3_mul_vec3(p_color,
						world->cam.a_background), 0.1));
	}
	else
		brightness = vec3_add(brightness, specular_and_diffuse(r,
					&p_to_light, rec, l));
	return (vec3_add(brightness, world->cam.a_background));
}

t_color	phong_color(t_ray r, t_world *world)
{
	t_hit_rec	rec;
	t_color		phong;
	t_color		ambient;
	t_ray		p_to_light;
	t_color		p_color;

	ambient = world->cam.a_background;
	rec.min_t = 0.001;
	rec.max_t = INFINITY;
	if (!hit_bvh(&rec, &r, world->bvh) || rec.mat->mat_type == light)
		return (ambient);
	p_color = rec.mat->t.value(&rec, rec.mat->t.rgb);
	phong = vec3_mul_vec3(get_brightness(&r, &rec, world), p_color);
	return (phong);
}
