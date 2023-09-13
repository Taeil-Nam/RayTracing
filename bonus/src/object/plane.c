#include "object.h"

void	get_plane_uv(t_vec3 o_n, t_point3 p, t_hit_rec *rec)
{
	t_vec3	u_vec;
    t_vec3	v_vec;
	t_vec3	q_minus_p;

	u_vec = vec3_cross(o_n, vec3_instant(1.0, 0.0, 0.0)); // Choose an arbitrary vector not collinear with normal
	v_vec = vec3_cross(o_n, u_vec);

    // Calculate Q - pointOnPlane
    vec3_init(&q_minus_p, rec->p.x - p.x, rec->p.y - p.y, rec->p.z - p.z);

    // Calculate dot products to find UV coordinates
    rec->u = fmod(vec3_dot(q_minus_p, u_vec), 40) / 40;
    rec->v = fmod(vec3_dot(q_minus_p, v_vec), 40) / 40;
}

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
	numer = vec3_dot(pl->n, vec3_sub(pl->p, r->orig));
	denomi = vec3_dot(pl->n, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < min_t || max_t < root)
		return (false);
	rec->center = pl->p;
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	outward_normal = pl->n;
	get_plane_uv(outward_normal, pl->p, rec);
	set_face_normal(r, outward_normal, rec);
	rec->mat = &pl->mat;
	return (true);
}
