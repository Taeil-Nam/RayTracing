#include "object.h"

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
	rec->mat = &sp->mat;
	return (true);
}
