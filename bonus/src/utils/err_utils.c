#include "minirt.h"

void	minirt_error_exit(void)
{
	perror("Error\nminiRT : ");
	exit(-1);
}

void minirt_str_error_exit(char *str)
{
	errno = 0;
	perror(str);
	exit(-1);
}
