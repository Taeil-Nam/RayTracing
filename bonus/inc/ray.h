#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

t_point3	ray_at(t_ray ray, double t); //orig으로부터 t * dir 지점의 포인트

#endif
