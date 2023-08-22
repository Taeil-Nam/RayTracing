/* near_zero, print */

#include <stdio.h>
#include "vec3.h"

void	vec3_print(t_vec3 v)
{
	printf("======\n");
	printf("vecter | x = %.3f, y = %.3f, z = %.3f\n", v.x, v.y, v.z);
	printf("======\n");
}
