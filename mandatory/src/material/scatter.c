#include "material.h"

bool	scatter_diffuse(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	t_vec3	scatter_direction;

	r = NULL;
	scatter_direction = vec3_add(rec->normal, vec3_random_unit());
	if (vec3_near_zero(scatter_direction))
		scatter_direction = rec->normal;
	scat->orig = rec->p;
	scat->dir = scatter_direction;
	*att = rec->mat->t.value(rec, rec->mat->t.rgb);
	return (true);
}

bool	scatter_light(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat)
{
	r = NULL;
	rec = NULL;
	att = NULL;
	scat = NULL;
	return (false);
}
