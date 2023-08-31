#include "object.h"

t_aabb	cylinder_b_box(void *object)
{
	t_cylinder	*cy;
	t_aabb		cy_box;
	t_point3	c_top;

	cy = (t_cylinder *)object;
	c_top = vec3_add(cy->center, vec3_mul_scalar(cy->axis, cy->height));
	cy_box.p_min.x = fmin(cy->center.x - cy->diameter * 0.5,
			c_top.x - cy->diameter * 0.5);
	cy_box.p_min.y = fmin(cy->center.y - cy->diameter * 0.5,
			c_top.y - cy->diameter * 0.5);
	cy_box.p_min.z = fmin(cy->center.z - cy->diameter * 0.5,
			c_top.z - cy->diameter * 0.5);
	cy_box.p_max.x = fmax(cy->center.x + cy->diameter * 0.5,
			c_top.x + cy->diameter * 0.5);
	cy_box.p_max.y = fmax(cy->center.y + cy->diameter * 0.5,
			c_top.y + cy->diameter * 0.5);
	cy_box.p_max.z = fmax(cy->center.z + cy->diameter * 0.5,
			c_top.z + cy->diameter * 0.5);
	return (cy_box);
}

bool	cylinder_side_hit(t_ray *r, double min_t, double max_t,
			t_hit_rec *rec, t_cylinder *object)
{
	t_vec3	ray_d;
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discrement;
	double	sqrtd;
	double	root;

	ray_d = r->dir;
	oc = vec3_sub(r->orig, object->center);
	a = vec3_dot(ray_d, ray_d) - pow(vec3_dot(ray_d, object->axis), 2);
	half_b = vec3_dot(ray_d, oc) - vec3_dot(ray_d, object->axis) * vec3_dot(oc, object->axis);
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, object->axis), 2) - pow(object->diameter * 0.5, 2);
	discrement = pow(half_b, 2) - a * c;
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
	double	p_height = vec3_dot(vec3_sub(ray_at(*r, root), object->center), object->axis);
	if (p_height > object->height || p_height < 0)
		return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	t_vec3 outward_normal = vec3_unit(vec3_sub(vec3_sub(rec->p, object->center), vec3_mul_scalar(object->axis, p_height)));
	set_face_normal(r, outward_normal, rec);
	rec->mat = &object->mat;
	return (true);
}

bool	cylinder_cap_bottom_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, t_cylinder *object)
{
	double		numer;
	double		denomi;
	double		root;
	t_vec3		outward_normal;
	t_point3	p;

	numer = vec3_dot(object->axis, vec3_sub(object->center, r->orig));
	denomi = vec3_dot(object->axis, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < min_t || max_t < root)
		return (false);
	p = ray_at(*r, root);
	if (vec3_length(vec3_sub(p, object->center)) > object->diameter * 0.5)
		return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	outward_normal = object->axis;
	set_face_normal(r, outward_normal, rec);
	rec->mat = &object->mat;
	return (true);
}

bool	cylinder_cap_top_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, t_cylinder *object)
{
	double		numer;
	double		denomi;
	double		root;
	t_vec3		outward_normal;
	t_point3	top;
	t_point3	p;

	top = vec3_add(object->center, vec3_mul_scalar(object->axis, object->height));
	numer = vec3_dot(object->axis, vec3_sub(top, r->orig));
	denomi = vec3_dot(object->axis, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < min_t || max_t < root)
		return (false);
	p = ray_at(*r, root);
	if (vec3_length(vec3_sub(p, top)) > object->diameter * 0.5)
		return (false);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	outward_normal = object->axis;
	set_face_normal(r, outward_normal, rec);
	rec->mat = &object->mat;
	return (true);
}

bool	cylinder_hit(t_ray *r, double min_t, double max_t,
		t_hit_rec *rec, void *object)
{
	t_cylinder	*cy;
	bool		side;
	bool		top;
	bool		bottom;

	cy = (t_cylinder *)object;
	rec->t = max_t;
	side = cylinder_side_hit(r, min_t, rec->t, rec, cy);
	top = cylinder_cap_top_hit(r, min_t, rec->t, rec, cy);
	bottom = cylinder_cap_bottom_hit(r, min_t, rec->t, rec, cy);
	return (side || top || bottom);
}
