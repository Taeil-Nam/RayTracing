#ifndef OBJECT_H
# define OBJECT_H

# include "minirt.h"
# include "material.h"

# define DEFAULT_LIGHT_SIZE 5

typedef struct s_aabb
{
	t_point3	p_min;
	t_point3	p_max;
}	t_aabb;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	mat;
}	t_sphere;

typedef struct s_plane
{
	t_point3	p;
	t_vec3		n;
	t_material	mat;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_material	mat;
}	t_cylinder;

bool	sphere_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);
bool	aabb_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);
bool	plane_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);
bool	cylinder_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, void *object);

t_aabb		sphere_b_box(void *object);
t_aabb		plane_b_box(void *object);
t_aabb		cylinder_b_box(void *object);
t_aabb		aabb_b_box(void *object);

t_sphere	*sphere_constructor(t_point3 center, double radius, t_color rgb);
t_sphere	*light_constructor(t_point3 center, double ratio, t_color rgb);
t_plane		*plane_constructor(t_point3 p, t_point3 normal, t_color rgb);

#endif
