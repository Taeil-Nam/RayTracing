#ifndef BVH_H
# define BVH_H

# include "minirt.h"

typedef bool	(*t_hit)(t_ray *, double, double, t_hit_rec *, void *);

typedef struct s_hittable
{
	void				*object;
	t_hit				hit;
	struct s_hittable	*left;
	struct s_hittable	*right;
}	t_hittable;

void	set_face_normal(t_ray *r, t_vec3 *o_n, t_hit_rec *rec);

#endif
