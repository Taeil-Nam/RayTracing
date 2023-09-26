#include "object_bonus.h"

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

bool	plane_hit(t_ray *r, t_hit_rec *rec, void *object)
{
	t_plane	*pl;
	double	numer;
	double	denomi;
	double	root;

	pl = (t_plane *)object;
	numer = vec3_dot(pl->n, vec3_sub(pl->p, r->orig));
	denomi = vec3_dot(pl->n, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < rec->min_t || rec->max_t < root)
		return (false);
	rec->center = pl->p;
	rec->t = root;
	rec->max_t = rec->t;
	rec->p = ray_at(*r, rec->t);
	set_face_normal(r, pl->n, rec);
	get_plane_uv(pl->n, pl->p, rec);
	if (pl->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &pl->mat.t.bmp_img)));
	rec->mat = &pl->mat;
	return (true);
}
