#include "material.h"

bool	scatter_diffuse(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	t_vec3	scatter_direction;

	scatter_direction = vec3_add(rec->normal, vec3_random_unit());
	if (vec3_near_zero(scatter_direction))
		scatter_direction = rec->normal;
	scat->orig = rec->p;
	scat->dir = scatter_direction;
	*att = rec->mat->t.value(rec, &rec->mat->t.img, rec->mat->t.rgb);
	return (true);
}

bool	scatter_light(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	return (false);
}

bool	scatter_metal(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	t_vec3	reflected;

	reflected = vec3_reflect(vec3_unit(r->dir), rec->normal);
	scat->orig = rec->p;
	scat->dir = vec3_add(reflected, vec3_mul_scalar(vec3_random_unit(), rec->mat->fuzz));
	*att = rec->mat->t.value(rec, &rec->mat->t.img, rec->mat->t.rgb);
	if (vec3_dot(scat->dir, rec->normal) > 0)
		return (true);
	return (false);
}

double	reflectance(double cosine, double ref_idx)
{
    //Use Schlick's approximation for reflectance
	double	r0;

    r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

bool	scatter_dielectric(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	double	refraction_ratio;
	t_vec3	unit_dir;
	double	cos_theta;
	bool	cannot_refract;
	t_vec3	direction;

	vec3_init(att, 1, 1, 1);
	if (rec->front_face)
		refraction_ratio = 1.0 / rec->mat->ir;
	else
		refraction_ratio = rec->mat->ir;
	unit_dir = vec3_unit(r->dir);
	cos_theta = fmin(vec3_dot(vec3_mul_scalar(unit_dir, -1), rec->normal), 1.0);
	cannot_refract = refraction_ratio * sqrt(1.0 - cos_theta * cos_theta) > 1.0;
	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = vec3_reflect(unit_dir, rec->normal);
    else
        direction = vec3_refract(unit_dir, rec->normal, refraction_ratio);
	scat->orig = rec->p;
	scat->dir = direction;
    return true;
}
