#include "object_bonus.h"

void	get_cone_uv(t_vec3 o_n, t_hit_rec *rec, double p_height, t_cone *cone)
{
	double	theta;
	t_vec3	u_vec;
	t_vec3	tmp;
	t_vec3	w;
	t_vec3	std;

	if (o_n.x == 0 && o_n.z == 0)
		vec3_init(&std, 1, 0, 0);
	else
		vec3_init(&std, 0, 1, 0);
	u_vec = vec3_unit(vec3_cross(cone->n_axis, std));
	tmp = vec3_sub(vec3_sub(rec->p, cone->top),
			vec3_mul_scalar(cone->n_axis, p_height));
	tmp = vec3_unit(tmp);
	theta = vec3_dot(u_vec, tmp);
	w = vec3_cross(u_vec, tmp);
	if (vec3_dot(w, cone->n_axis) <= 0)
		rec->u = clamp(1 - (acos(theta) / (2 * PI)), 0, 1);
	else
		rec->u = clamp(acos(theta) / (2 * PI), 0, 1);
	p_height = fmod(fabs(p_height),
			vec3_length(vec3_sub(cone->top, cone->center)));
	rec->v = clamp(p_height
			/ vec3_length(vec3_sub(cone->top, cone->center)), 0, 1);
}

void	get_cylinder_uv(t_vec3 o_n, t_hit_rec *rec,
		double p_height, t_cylinder *cy)
{
	double	theta;
	t_vec3	u_vec;
	t_vec3	tmp;
	t_vec3	std;
	t_vec3	w;

	if (o_n.x == 0 && o_n.z == 0)
		vec3_init(&std, 1, 0, 0);
	else
		vec3_init(&std, 0, 1, 0);
	u_vec = vec3_unit(vec3_cross(cy->axis, std));
	tmp = vec3_sub(vec3_sub(rec->p, cy->center),
			vec3_mul_scalar(cy->axis, p_height));
	tmp = vec3_unit(tmp);
	theta = vec3_dot(u_vec, tmp);
	w = vec3_cross(u_vec, tmp);
	if (vec3_dot(w, cy->axis) <= 0)
		rec->u = clamp(1 - (acos(theta) / (2 * PI)), 0, 1);
	else
		rec->u = clamp(acos(theta) / (2 * PI), 0, 1);
	rec->v = clamp(p_height / cy->height, 0, 1);
}

void	get_plane_uv(t_vec3 o_n, t_point3 p, t_hit_rec *rec)
{
	t_vec3	u_vec;
	t_vec3	v_vec;
	t_vec3	q_minus_p;
	t_vec3	std;

	if (o_n.x == 0 && o_n.z == 0)
		vec3_init(&std, -1, 0, 0);
	else
		vec3_init(&std, 0, 1, 0);
	u_vec = vec3_unit(vec3_cross(o_n, std));
	v_vec = vec3_unit(vec3_cross(o_n, u_vec));
	vec3_init(&q_minus_p, rec->p.x - p.x, rec->p.y - p.y, rec->p.z - p.z);
	rec->u = fmod(vec3_dot(q_minus_p, u_vec), TILE_SIZE) / TILE_SIZE;
	rec->v = fmod(vec3_dot(q_minus_p, v_vec), TILE_SIZE) / TILE_SIZE;
}

void	get_sphere_uv(t_vec3 o_n, t_hit_rec *rec)
{
	double	theta;
	double	phi;

	theta = acos(-(o_n.y));
	phi = atan2(-(o_n.z), o_n.x) + PI;
	rec->u = phi / (2 * PI);
	rec->v = theta / PI;
}
