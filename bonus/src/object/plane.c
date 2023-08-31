#include "object.h"

t_aabb	plane_b_box(void *object)
{
	t_plane	*pl;
	t_aabb	pl_box;

	pl = (t_plane *)object;
	pl_box.p_min.x = -INFINITY;
	pl_box.p_min.y = -INFINITY;
	pl_box.p_min.z = -INFINITY;
	pl_box.p_max.x = INFINITY;
	pl_box.p_max.y = INFINITY;
	pl_box.p_max.z = INFINITY;
	return (pl_box);
}

bool	plane_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, void *object)
{
	t_plane	*pl;
	double	numer;
	double	denomi;
	double	root;
	t_vec3	outward_normal;

	pl = (t_plane *)object;
	numer = vec3_dot(pl->n, vec3_sub(pl->p, r->orig)); // 분자
	denomi = vec3_dot(pl->n, r->dir); // 분모
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < min_t || max_t < root)
		return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	outward_normal = pl->n;
	set_face_normal(r, outward_normal, rec);
	// get_plane_uv(??); // 평면의 u, v를 구할 수 있는지
	rec->mat = &pl->mat;
	return (true);
}
