#include "minirt.h"
#include "object.h"
#include "bvh.h"

t_sphere	*light_initializer(t_point3 center, double ratio, t_color rgb)
{
	t_sphere	*new_light;

	new_light = (t_sphere *)xmalloc(sizeof(t_sphere));
	new_light->center = center;
	new_light->radius = DEFAULT_lIZE;
	new_light->mat.mat_type = light;
	new_light->mat.emit = emit_light;
	new_light->mat.scatter = scatter_light;
	new_light->mat.t.bmp_img.img_ptr = NULL;
	new_light->mat.t.img.img_ptr = NULL;
	new_light->mat.t.rgb = vec3_mul_scalar(rgb, ratio);
	new_light->mat.t.tex_type = solid;
	new_light->mat.t.value = solid_value;
	return (new_light);
}

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
