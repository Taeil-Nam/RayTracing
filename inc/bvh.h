#ifndef BVH_H
# define BVH_H

# include "minirt.h"
# include "object.h"

typedef bool	(*t_hit)(t_ray *, double, double, t_hit_rec *, void *);
typedef t_aabb	(*t_b_box)(void *);

typedef struct s_hittable
{
	t_vec3				center;
	void				*object;
	t_hit				hit;
	t_b_box				b_box;
	struct s_hittable	*left;
	struct s_hittable	*right;
}	t_hittable;

#endif
