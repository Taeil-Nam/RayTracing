#include "object.h"

t_aabb		aabb_b_box(void *object)
{
	t_aabb	*ret;

	ret = (t_aabb *)object;
	return (*ret);
}
