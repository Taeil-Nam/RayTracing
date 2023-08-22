/* near_zero, print */

#include <stdio.h>
#include "vec3.h"

void	vec3_print(t_vec3 *v)
{
	printf("vecter | x = %f, y = %f, z = %f\n", v->x, v->y, v->z);
}
