/* near_zero, print, reflect, refract */

#include <stdio.h>
#include <math.h>
#include "vec3.h"

bool	vec3_near_zero(t_vec3 v)
{
	const double	s = 1e-8;

	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

void	vec3_print(t_vec3 v)
{
	printf("vecter | x = %.3f, y = %.3f, z = %.3f\n", v.x, v.y, v.z);
}

//t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
//{

//}

//t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
//{

//}
