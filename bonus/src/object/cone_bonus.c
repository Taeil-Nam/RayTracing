#include "object_bonus.h"

t_aabb	cone_b_box(void *object)
{
	t_cone		*cone;
	t_aabb		cone_box;

	cone = (t_cone *)object;
	if (cone->is_inf == 1)
	{
		vec3_init(&cone_box.p_min, -INFINITY, -INFINITY, -INFINITY);
		vec3_init(&cone_box.p_max, INFINITY, INFINITY, INFINITY);
	}
	else
	{
		cone_box.p_min.x = fmin(cone->center.x - cone->radius,
				cone->top.x - cone->radius);
		cone_box.p_min.y = fmin(cone->center.y - cone->radius,
				cone->top.y - cone->radius);
		cone_box.p_min.z = fmin(cone->center.z - cone->radius,
				cone->top.z - cone->radius);
		cone_box.p_max.x = fmax(cone->center.x + cone->radius,
				cone->top.x + cone->radius);
		cone_box.p_max.y = fmax(cone->center.y + cone->radius,
				cone->top.y + cone->radius);
		cone_box.p_max.z = fmax(cone->center.z + cone->radius,
				cone->top.z + cone->radius);
	}
	return (cone_box);
}

void	cal_abc_cone(double constants[3], t_ray *r, t_cone *cone)
{
	double	x_dot_y[5];
	double	m;

	x_dot_y[0] = vec3_dot(r->dir, r->dir);
	x_dot_y[1] = vec3_dot(r->dir, cone->n_axis);
	x_dot_y[2] = vec3_dot(r->dir, vec3_sub(r->orig, cone->top));
	x_dot_y[3] = vec3_dot(vec3_sub(r->orig, cone->top),
			vec3_sub(r->orig, cone->top));
	x_dot_y[4] = vec3_dot(vec3_sub(r->orig, cone->top), cone->n_axis);
	m = pow(cone->radius, 2) / pow(vec3_length(cone->axis), 2);
	constants[0] = x_dot_y[0] - m * pow(x_dot_y[1], 2) - pow(x_dot_y[1], 2);
	constants[1] = (x_dot_y[2] - m * x_dot_y[1] * x_dot_y[4]
			- x_dot_y[1] * x_dot_y[4]);
	constants[2] = x_dot_y[3] - m * pow(x_dot_y[4], 2) - pow(x_dot_y[4], 2);
}

bool	cone_side_hit(t_ray *r, t_hit_rec *rec, t_cone *cone)
{
	t_vec3		normal;
	double		constants[3];
	double		height;
	double		tmp;

	cal_abc_cone(constants, r, cone);
	if (quadratic_formular(constants, rec) == false)
		return (false);
	height = vec3_dot(vec3_sub(ray_at(*r, rec->root), cone->top), cone->n_axis);
	if (cone->is_inf != 1)
		if (!(0 <= height && height <= vec3_length(cone->axis)))
			return (false);
	rec->t = rec->root;
	rec->p = ray_at(*r, rec->t);
	rec->max_t = rec->t;
	normal = vec3_sub(rec->p, cone->top);
	tmp = vec3_length(normal) / vec3_dot(vec3_unit(normal), cone->n_axis);
	normal = vec3_unit(vec3_sub(normal, vec3_mul_scalar(cone->n_axis, tmp)));
	set_face_normal(r, normal, rec);
	get_cone_uv(normal, rec, height, cone);
	if (cone->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &cone->mat.t.bmp_img)));
	rec->mat = &cone->mat;
	return (true);
}

bool	cone_bottom_hit(t_ray *r, t_hit_rec *rec, t_cone *cone)
{
	double		numer;
	double		denomi;
	double		root;
	t_point3	p;

	numer = vec3_dot(cone->axis, vec3_sub(cone->center, r->orig));
	denomi = vec3_dot(cone->axis, r->dir);
	if (denomi == 0)
		return (false);
	root = numer / denomi;
	if (root < rec->min_t || rec->max_t < root)
		return (false);
	p = ray_at(*r, root);
	if (vec3_length(vec3_sub(p, cone->center)) > cone->radius)
		return (false);
	rec->t = root;
	rec->max_t = rec->t;
	rec->p = ray_at(*r, rec->t);
	get_cone_uv(cone->axis, rec, vec3_length(cone->axis), cone);
	set_face_normal(r, cone->n_axis, rec);
	if (cone->mat.t.bmp_img.img_ptr != NULL)
		rec->normal = vec3_unit(vec3_add(rec->normal,
					bmp_value(rec, &cone->mat.t.bmp_img)));
	rec->mat = &cone->mat;
	return (true);
}

bool	cone_hit(t_ray *r, t_hit_rec *rec, void *object)
{
	t_cone	*cone;
	bool	side;
	bool	bottom;

	cone = (t_cone *)object;
	side = cone_side_hit(r, rec, cone);
	if (cone->is_inf)
		return (side);
	bottom = cone_bottom_hit(r, rec, cone);
	return (side || bottom);
}
