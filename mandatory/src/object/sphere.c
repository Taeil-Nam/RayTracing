#include "object.h"

t_aabb		sphere_b_box(void *object)
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

void	get_sphere_uv(t_vec3 o_n, t_hit_rec *rec)
{
	double	theta;
	double	phi;

	theta = acos(-(o_n.y));
    phi = atan2(-(o_n.z), o_n.x) + PI;
	rec->u = phi / (2 * PI);
	rec->v = theta / PI;
}

bool	sphere_hit(t_ray *r, double min_t, double max_t,
				t_hit_rec *rec, void *object)
{
	t_sphere	*sp;
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discrement;
	double		sqrtd;
	double		root;

	sp = (t_sphere *)object;
	if (rec->depth == 50 && sp->mat.mat_type == light)
		return (false);
	oc = vec3_sub(r->orig, sp->center);
	a = vec3_squared(r->dir);
	half_b = vec3_dot(oc, r->dir);
	c = vec3_squared(oc) - sp->radius * sp->radius;
	discrement = half_b * half_b - a * c;
	if (discrement < 0)
		return (false);
	sqrtd = sqrt(discrement);
	root = (-half_b - sqrtd) / a;
	if (root < min_t || max_t < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < min_t || max_t < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	t_vec3 outward_normal = vec3_mul_scalar(vec3_sub(rec->p, sp->center), 1 / sp->radius);
	set_face_normal(r, outward_normal, rec);
	get_sphere_uv(outward_normal, rec);
	rec->mat = &sp->mat;
	return (true);
}
