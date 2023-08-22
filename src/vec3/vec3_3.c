/* random, random_in_unit_sphere, random_unit, reflect, refract */

#include "vec3.h"

double	random_double(void);

t_vec3	vec3_random(void)
{
	t_vec3	v;

	v.x = random_double();
	v.y = random_double();
	v.z = random_double();
	return (v);
}

//t_vec3	vec3_random_in_unit_sphere(void)
//{

//}

//t_vec3	vec3_random_unit(void)
//{

//}

//t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
//{

//}

//t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
//{

//}
