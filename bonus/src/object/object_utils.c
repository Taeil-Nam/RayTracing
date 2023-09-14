#include "object.h"

bool	quadratic_formular(double constants[3], t_hit_rec *rec, double min_t, double max_t)
{
	double	discrement;
	double	sqrtd;
	double	root;
	double	root1;
	double	root2;

	discrement = pow(constants[1], 2) - constants[0] * constants[2];
	if (discrement < 0)
		return (false);
	sqrtd = sqrt(discrement);
	root1 = (-constants[1] - sqrtd) / constants[0];
	root2 = (-constants[1] + sqrtd) / constants[0];
	if (root1 < root2)
	{
		root = root1;
		root1 = root2;
	}
	else
		root = root2;
	if (root < min_t || max_t < root)
	{
		root = root1;
		if (root < min_t || max_t < root)
			return (false);
	}
	rec->root = root;
	return (true);
}