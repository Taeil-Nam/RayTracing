#ifndef OBJECT_H
# define OBJECT_H

# include "minirt.h"
# include "material.h"

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	*mat;
}	t_sphere;

bool	sphere_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);
bool	aabb_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);

#endif
