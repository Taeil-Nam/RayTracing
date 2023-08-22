/* add, sub, mul_vec3, mul_scalar */

#include "vec3.h"

t_vec3	vec3_add(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x + right.x;
	v.y = left.y + right.y;
	v.z = left.z + right.z;
	return (v);
}

t_vec3	vec3_sub(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x - right.x;
	v.y = left.y - right.y;
	v.z = left.z - right.z;
	return (v);
}

t_vec3	vec3_mul_vec3(t_vec3 left, t_vec3 right)
{
	t_vec3	v;

	v.x = left.x * right.x;
	v.y = left.y * right.y;
	v.z = left.z * right.z;
	return (v);
}

t_vec3	vec3_mul_scalar(t_vec3 left, double right)
{
	t_vec3	v;

	v.x = left.x * right;
	v.y = left.y * right;
	v.z = left.z * right;
	return (v);
}
