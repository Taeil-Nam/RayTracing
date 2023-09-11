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
	t_vec3		normal;
	double		constants[3];

	sp = (t_sphere *)object;
	if (rec->depth == 50 && sp->mat.mat_type == light)
		return (false);
	oc = vec3_sub(r->orig, sp->center);
	constants[0] = vec3_squared(r->dir);
	constants[1] = vec3_dot(oc, r->dir);
	constants[2] = vec3_squared(oc) - sp->radius * sp->radius;
	if (quadratic_formular(constants, rec, min_t, max_t) == false)
		return (false);
	rec->t = rec->root;
	rec->p = ray_at(*r, rec->t);
	normal = vec3_mul_scalar(vec3_sub(rec->p, sp->center), 1 / sp->radius);
	set_face_normal(r, normal, rec);
	get_sphere_uv(normal, rec);
	rec->mat = &sp->mat;
	return (true);
}
