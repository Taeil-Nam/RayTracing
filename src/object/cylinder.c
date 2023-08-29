#include "object.h"

t_aabb	cylinder_b_box(void *object)
{
	t_cylinder	*cy;
	t_aabb		cy_box;

	cy = (t_cylinder *)object;
	// Todo: cy_box의 p_min, p_max 지정.
	// axis * (height * 0.5) = 윗면의 중심. (vec3 연산 이용)
	// -(axis * (height * 0.5)) = 밑면의 중심. (vec3 연산 이용)
	// 윗면의 중심, 밑면의 중심에서 반지름 사용하면 p_min, p_max 나올듯? (생각해봐야함..)
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
