#include "minirt.h"

void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec)
{
	rec->front_face = vec3_dot(r->dir, o_n) < 0;
	if (rec->front_face)
		rec->normal = o_n;
	else
		rec->normal = vec3_mul_scalar(o_n, -1);
}

void	swap_d(double *left, double *right)
{
	double	tmp;

	tmp = *right;
	*right = *left;
	*left = tmp;
}
