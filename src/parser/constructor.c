#include "minirt.h"
#include "object.h"

t_sphere	*sphere_constructor(t_point3 center, double radius, t_color rgb)
{
	t_sphere	*new_sp;

	new_sp = (t_sphere *)malloc(sizeof(t_sphere));
	new_sp->center = center;
	new_sp->radius = radius;
	new_sp->mat.mat_type = diffuse;
	new_sp->mat.emit = emit_general;
	new_sp->mat.scatter = scatter_diffuse;
	new_sp->mat.t.bmp_img = NULL;
	new_sp->mat.t.img = NULL;
	new_sp->mat.t.rgb = rgb;
	new_sp->mat.t.tex_type = solid;
	new_sp->mat.t.value = solid_value;
	return (new_sp);
}

t_sphere	*light_constructor(t_point3 center, double ratio, t_color rgb)
{
	t_sphere	*new_light;

	new_light = (t_sphere *)malloc(sizeof(t_sphere));
	new_light->center = center;
	new_light->radius = DEFAULT_LIGHT_SIZE;
	new_light->mat.mat_type = light;
	new_light->mat.emit = emit_light;
	new_light->mat.scatter = scatter_light;
	new_light->mat.t.bmp_img = NULL;
	new_light->mat.t.img = NULL;
	new_light->mat.t.rgb = vec3_mul_scalar(rgb, ratio);
	new_light->mat.t.tex_type = solid;
	new_light->mat.t.value = solid_value;
	return (new_light);
}

t_plane	*plane_constructor(t_point3 p, t_point3 normal, t_color rgb)
{
	t_plane	*new_pl;

	new_pl = (t_plane *)malloc(sizeof(t_plane));
	new_pl->p = p;
	new_pl->n = normal;
	new_pl->mat.mat_type = diffuse;
	new_pl->mat.emit = emit_general;
	new_pl->mat.scatter = scatter_diffuse;
	new_pl->mat.t.bmp_img = NULL;
	new_pl->mat.t.img = NULL;
	new_pl->mat.t.rgb = rgb;
	new_pl->mat.t.tex_type = solid;
	new_pl->mat.t.value = solid_value;
	return (new_pl);
}

t_cylinder	*cylinder_constructor(t_point3 center, t_vec3 axis, double diameter, double height, t_color rgb)
{
	t_cylinder	*new_cy;

	new_cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	new_cy->center = center;
	new_cy->axis = axis;
	new_cy->diameter = diameter;
	new_cy->height = height;
	new_cy->mat.mat_type = diffuse;
	new_cy->mat.emit = emit_general;
	new_cy->mat.scatter = scatter_diffuse;
	new_cy->mat.t.bmp_img = NULL;
	new_cy->mat.t.img = NULL;
	new_cy->mat.t.rgb = rgb;
	new_cy->mat.t.tex_type = solid;
	new_cy->mat.t.value = solid_value;
	return (new_cy);
}
