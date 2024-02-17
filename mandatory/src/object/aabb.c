#include "object.h"

t_aabb	aabb_b_box(void *object)
{
	t_aabb	*ret;

	ret = (t_aabb *)object;
	return (*ret);
}

double	find_inverse(t_vec3 dir, int i)
{
	if (i == 0)
		return (1.0f / dir.x);
	else if (i == 1)
		return (1.0f / dir.y);
	return (1.0f / dir.z);
}

double	sub_p_orig(t_vec3 p, t_vec3 orig, int i)
{
	if (i == 0)
		return (p.x - orig.x);
	else if (i == 1)
		return (p.y - orig.y);
	return (p.z - orig.z);
}

bool	aabb_hit(t_ray *r, t_hit_rec *rec, void *object)
{
	int		i;
	double	inv_d;
	t_aabb	*aabb;
	double	t0_t1[2];
	double	min_max[2];

	min_max[0] = rec->min_t;
	min_max[1] = rec->max_t;
	aabb = (t_aabb *)object;
	i = 0;
	while (i < 3)
	{
		inv_d = find_inverse(r->dir, i);
		t0_t1[0] = sub_p_orig(aabb->p_min, r->orig, i) * inv_d;
		t0_t1[1] = sub_p_orig(aabb->p_max, r->orig, i++) * inv_d;
		if (inv_d < 0.0f)
			swap_d(&t0_t1[0], &t0_t1[1]);
		if (t0_t1[0] > min_max[0])
			min_max[0] = t0_t1[0];
		if (t0_t1[1] < min_max[1])
			min_max[1] = t0_t1[1];
		if (min_max[1] <= min_max[0])
			return (false);
	}
	return (true);
}
