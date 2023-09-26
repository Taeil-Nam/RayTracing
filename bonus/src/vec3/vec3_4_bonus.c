/* near_zero, print, reflect, refract */

#include <stdio.h>
#include <math.h>
#include "vec3_bonus.h"

bool	vec3_near_zero(t_vec3 v)
{
	const double	s = 1e-8;

	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

void	vec3_print(t_vec3 v)
{
	printf("vecter | x = %.3f, y = %.3f, z = %.3f\n", v.x, v.y, v.z);
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul_scalar(n, vec3_dot(v, n) * 2)));
}

t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(vec3_dot(vec3_mul_scalar(uv, -1), n), 1.0);
	r_out_perp = vec3_mul_scalar(vec3_add(uv, vec3_mul_scalar(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vec3_mul_scalar(n,
			-sqrt(fabs(1.0 - vec3_squared(r_out_perp))));
	return (vec3_add(r_out_perp, r_out_parallel));
}
