#include "minirt.h"
#include "object.h"
#include "bvh.h"
#include "vec3.h"
#include "ray.h"

t_color	diffuse_color(t_hit_rec *rec, t_camera *cam, t_sphere *l, t_ray *p_to_light)
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

t_color	phong_color(t_ray r, t_camera *cam, t_hittable *bvh, t_sphere *l)
{
	t_hit_rec	rec;
	t_color		phong;
	t_color		ambient;
	t_ray		p_to_light;
	t_hit_rec	light_rec;

	ambient = vec3_mul_scalar(cam->a_background, cam->a_ratio);
	if (!hit_bvh(&rec, 0.001, INFINITY, &r, bvh) || rec.mat->mat_type == light)
		return (ambient);
	if (l == NULL)
		return (vec3_mul_vec3(ambient, rec.mat->t.value(&rec, &rec.mat->t.img, &rec.mat->t.bmp_img, rec.mat->t.rgb)));
	p_to_light.orig = vec3_add(rec.p, vec3_mul_scalar(rec.normal, 0.0001));
	p_to_light.dir = vec3_unit(vec3_sub(l->center, p_to_light.orig));
	double length = vec3_length(vec3_sub(l->center, p_to_light.orig));
	if (hit_bvh(&light_rec, 0.001, length, &p_to_light, bvh)
		&& light_rec.mat->mat_type != light
		&& light_rec.mat != rec.mat)
		return (vec3_instant(0,0,0));
	t_color	diffuse = diffuse_color(&rec, cam, l, &p_to_light);
	t_color	specular = specular_color(&r, &p_to_light, &rec, l);
	phong = vec3_add(vec3_mul_vec3(vec3_add(ambient, diffuse),
					rec.mat->t.value(&rec, &rec.mat->t.img, &rec.mat->t.bmp_img, rec.mat->t.rgb)) ,specular);
	return (phong);
}
