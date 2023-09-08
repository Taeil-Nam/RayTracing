#include "object.h"

t_aabb	cone_b_box(void *object)
{
	t_cone		*cone;
	t_aabb		cone_box;

	cone = (t_cone *)object;
	cone_box.p_min.x = -INFINITY;
	cone_box.p_min.y = -INFINITY;
	cone_box.p_min.z = -INFINITY;
	cone_box.p_max.x = INFINITY;
	cone_box.p_max.y = INFINITY;
	cone_box.p_max.z = INFINITY;
	return (cone_box);
}

bool	cone_side_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, t_cone *object)
{
	t_cone	*cone;
	t_vec3	axis;
	double	a;
	double	half_b;
	double	c;
	double	discrement;
	double	sqrtd;
	double	root;

	cone = (t_cone *)object;
	axis = vec3_sub(cone->center, cone->top);
	a = vec3_dot(r->dir, r->dir)
		- ((pow(cone->radius, 2) / pow(vec3_length(axis), 2))
			* pow(vec3_dot(r->dir, vec3_unit(axis)), 2))
		- pow(vec3_dot(r->dir, vec3_unit(axis)), 2);
	half_b = vec3_dot(r->dir, vec3_sub(r->orig, cone->top))
		- ((pow(cone->radius, 2) / pow(vec3_length(axis), 2))
			* vec3_dot(r->dir, vec3_unit(axis))
			* vec3_dot(vec3_sub(r->orig, cone->top), vec3_unit(axis)))
		- (vec3_dot(r->dir, vec3_unit(axis))
			* vec3_dot(vec3_sub(r->orig, cone->top), vec3_unit(axis)));
	c = vec3_dot(vec3_sub(r->orig, cone->top), vec3_sub(r->orig, cone->top))
		- ((pow(cone->radius, 2) / pow(vec3_length(axis), 2))
			* pow(vec3_dot(vec3_sub(r->orig, cone->top), vec3_unit(axis)), 2))
		- pow(vec3_dot(vec3_sub(r->orig, cone->top), vec3_unit(axis)), 2);
	discrement = half_b * half_b - a * c;
	if (discrement < 0)
		return (false);
	sqrtd = sqrt(discrement);
	root = (-half_b - sqrtd) / a;
	if (root < min_t || max_t < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < min_t || max_t < root)
			return (false);
	}
	// 아래 조건문 적용하면 finite cone
	// if (!(0 <= vec3_dot(vec3_sub(ray_at(*r, root), cone->top), vec3_unit(axis))
	// 		&& vec3_dot(vec3_sub(ray_at(*r, root), cone->top), vec3_unit(axis))
	// 		<= vec3_length(axis)))
	// 	return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	set_face_normal(r, vec3_unit(axis), rec);
	rec->mat = &cone->mat;
	return (true);
}

bool	cone_bottom_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, t_cone *object)
{
	t_vec3		axis;
	double		numer;
	double		denomi;
	double		root;
	t_point3	p;

	axis = vec3_sub(object->center, object->top);
	numer = vec3_dot(axis, vec3_sub(object->center, r->orig));
	denomi = vec3_dot(axis, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < min_t || max_t < root)
		return (false);
	p = ray_at(*r, root);
	if (vec3_length(vec3_sub(p, object->center)) > object->radius)
		return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	set_face_normal(r, vec3_unit(axis), rec);
	rec->mat = &object->mat;
	return (true);
}

bool	cone_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, void *object)
{
	t_cone	*cone;
	bool	side;
	bool	bottom;

	cone = (t_cone *)object;
	rec->t = max_t;
	side = cone_side_hit(r, min_t, rec->t, rec, cone);
	bottom = cone_bottom_hit(r, min_t, rec->t, rec, cone);
	return (side || bottom);
}
