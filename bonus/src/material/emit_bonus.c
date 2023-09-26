#include "material_bonus.h"

t_color	emit_general(t_hit_rec *rec, t_point3 *p, t_texture *t)
{
	t_color	ret;

	rec = NULL;
	p = NULL;
	t = NULL;
	ret.x = 0;
	ret.y = 0;
	ret.z = 0;
	return (ret);
}

t_color	emit_light(t_hit_rec *rec, t_point3 *p, t_texture *t)
{
	p = NULL;
	return (t->value(rec, &t->img, t->rgb));
}