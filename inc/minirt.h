#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "vec3.h"
# include "ray.h"

typedef struct s_material	t_material;

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
}	t_hit_rec;

#endif
