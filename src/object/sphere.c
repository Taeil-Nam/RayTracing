#include "object.h"

t_aabb		sphere_b_box(void *object)
{
	t_sphere	*sp;
	t_aabb		sp_box;

	sp = (t_sphere *)object;
	sp_box.p_min.x = sp->center.x - sp->radius;
	sp_box.p_min.y = sp->center.y - sp->radius;
	sp_box.p_min.z = sp->center.z - sp->radius;
	sp_box.p_max.x = sp->center.x + sp->radius;
	sp_box.p_max.y = sp->center.y + sp->radius;
	sp_box.p_max.z = sp->center.z + sp->radius;
	return (sp_box);
}