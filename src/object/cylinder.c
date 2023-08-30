#include "object.h"

t_aabb	cylinder_b_box(void *object)
{
	t_cylinder	*cy;
	t_aabb		cy_box;
	t_point3	c_top;
	t_point3	c_bottom;

	cy = (t_cylinder *)object;
	c_top = vec3_add(cy->center, vec3_mul_scalar(cy->axis, (cy->height * 0.5)));
	c_bottom = vec3_mul_scalar(c_top, -1);
	cy_box.p_max.x = c_top.x + cy->diameter / 2;
	cy_box.p_max.y = c_top.y + cy->diameter / 2;
	cy_box.p_max.z = c_top.z + cy->diameter / 2;
	cy_box.p_min.x = c_bottom.x + cy->diameter / 2;
	cy_box.p_min.y = c_bottom.y + cy->diameter / 2;
	cy_box.p_min.z = c_bottom.z + cy->diameter / 2;
	return (cy_box);
}

bool	cylinder_hit(t_ray *r, double min_t, double max_t,
        t_hit_rec *rec, void *object)
{
	// Todo: 원기둥에 ray가 맞았는지 판별.
	// if(no hit) : return false;
	// else : rec에 정보 기록 후 return true;
	return (true);
}
