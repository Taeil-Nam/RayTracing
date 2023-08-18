#ifndef BVH_H
# define BVH_H

# include "ray.h"
# include "object.h"
# include "material.h"
# include "stdbool.h"

typedef struct s_hittable
{
	void		*object;
	bool		(*hit)(t_ray *, double, double, t_hit_record *, void *);
	t_hittable	*left;
	t_hittable	*right;
}	t_hittable;

void	set_face_normal(t_ray *r, t_vec3 *o_n, t_hit_record *rec);

#endif
