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
	t_sphere	*new_sp;

	new_sp = (t_sphere *)malloc(sizeof(t_sphere));
	new_sp->center = center;
	new_sp->radius = DEFAULT_LIGHT_SIZE;
	new_sp->mat.mat_type = light;
	new_sp->mat.emit = emit_light;
	new_sp->mat.scatter = scatter_light;
	new_sp->mat.t.bmp_img = NULL;
	new_sp->mat.t.img = NULL;
	new_sp->mat.t.rgb = vec3_mul_scalar(rgb, ratio);
	new_sp->mat.t.tex_type = solid;
	new_sp->mat.t.value = solid_value;
	return (new_sp);
}
