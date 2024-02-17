#include "parser_bonus.h"
#include "bvh_bonus.h"

int	sphere_initializer(t_hittable *hittable, char **data, t_minirt *minirt)
{
	t_sphere	*tmp;

	tmp = (t_sphere *)hittable->object;
	if (init_material(&tmp->mat, data[1]) == -1)
		return (-1);
	if (init_texture(&tmp->mat.t, data[2], minirt) == -1)
		return (-1);
	hittable->center = tmp->center;
	hittable->hit = sphere_hit;
	hittable->b_box = sphere_b_box;
	return (1);
}

int	plane_initializer(t_hittable *hittable, char **data, t_minirt *minirt)
{
	t_plane	*tmp;

	tmp = (t_plane *)hittable->object;
	if (init_material(&tmp->mat, data[1]) == -1)
		return (-1);
	if (init_texture(&tmp->mat.t, data[2], minirt) == -1)
		return (-1);
	hittable->center = tmp->p;
	hittable->hit = plane_hit;
	hittable->b_box = plane_b_box;
	return (1);
}

int	cylinder_initializer(t_hittable *hittable, char **data, t_minirt *minirt)
{
	t_cylinder	*tmp;

	tmp = (t_cylinder *)hittable->object;
	if (init_material(&tmp->mat, data[1]) == -1)
		return (-1);
	if (init_texture(&tmp->mat.t, data[2], minirt) == -1)
		return (-1);
	hittable->center = tmp->center;
	hittable->hit = cylinder_hit;
	hittable->b_box = cylinder_b_box;
	return (1);
}

int	cone_initializer(t_hittable *hittable, char **data, t_minirt *minirt)
{
	t_cone	*tmp;

	tmp = (t_cone *)hittable->object;
	if (init_material(&tmp->mat, data[1]) == -1)
		return (-1);
	if (init_texture(&tmp->mat.t, data[2], minirt) == -1)
		return (-1);
	hittable->center = tmp->center;
	hittable->hit = cone_hit;
	hittable->b_box = cone_b_box;
	return (1);
}
