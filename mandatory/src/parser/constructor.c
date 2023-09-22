#include "minirt.h"
#include "object.h"

t_sphere	*sphere_constructor(t_point3 center, double radius, t_color rgb)
{
	t_sphere	*new_sp;

	new_sp = (t_sphere *)xmalloc(sizeof(t_sphere));
	new_sp->center = center;
	new_sp->radius = radius;
	new_sp->mat.mat_type = diffuse;
	new_sp->mat.emit = emit_general;
	new_sp->mat.scatter = scatter_diffuse;
	new_sp->mat.t.rgb = rgb;
	new_sp->mat.t.tex_type = solid;
	new_sp->mat.t.value = solid_value;
	return (new_sp);
}

t_sphere	*light_constructor(t_point3 center, double ratio, t_color rgb)
{
	t_sphere	*new_light;

	new_light = (t_sphere *)xmalloc(sizeof(t_sphere));
	new_light->center = center;
	new_light->radius = DEFAULT_SIZE;
	new_light->mat.mat_type = light;
	new_light->mat.emit = emit_light;
	new_light->mat.scatter = scatter_light;
	new_light->mat.t.rgb = vec3_mul_scalar(rgb, ratio);
	new_light->mat.t.tex_type = solid;
	new_light->mat.t.value = solid_value;
	return (new_light);
}

t_plane	*plane_constructor(t_point3 p, t_point3 normal, t_color rgb)
{
	t_plane	*new_pl;

	new_pl = (t_plane *)xmalloc(sizeof(t_plane));
	new_pl->p = p;
	new_pl->n = vec3_unit(normal);
	new_pl->mat.mat_type = diffuse;
	new_pl->mat.emit = emit_general;
	new_pl->mat.scatter = scatter_diffuse;
	new_pl->mat.t.rgb = rgb;
	new_pl->mat.t.tex_type = solid;
	new_pl->mat.t.value = solid_value;
	return (new_pl);
}

t_cylinder	*cylinder_constructor(t_cy_vars cy_vars)
{
	t_cylinder	*new_cy;

	new_cy = (t_cylinder *)xmalloc(sizeof(t_cylinder));
	new_cy->center = cy_vars.center;
	new_cy->axis = cy_vars.axis;
	new_cy->diameter = cy_vars.diameter;
	new_cy->height = cy_vars.height;
	new_cy->mat.mat_type = diffuse;
	new_cy->mat.emit = emit_general;
	new_cy->mat.scatter = scatter_diffuse;
	new_cy->mat.t.rgb = cy_vars.rgb;
	new_cy->mat.t.tex_type = solid;
	new_cy->mat.t.value = solid_value;
	return (new_cy);
}
