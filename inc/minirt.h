#ifndef MINIRT_H
# define MINIRT_H

# include "vec3.h"
# include "material.h"

typedef struct s_hit_record
{
	t_point3	*p;
	t_vec3		*normal;
	t_material	*mat;
	double		t;
	double		u;
	double		v;
	bool		front_face;
	int			depth;
}	t_hit_record;

#endif
