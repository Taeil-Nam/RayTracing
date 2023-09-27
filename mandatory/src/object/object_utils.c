/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:54 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:29:55 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

bool	quadratic_formular(double constants[3], t_hit_rec *rec)
{
	double	discrement;
	double	sqrtd;
	double	root1;
	double	root2;

	discrement = pow(constants[1], 2) - constants[0] * constants[2];
	if (discrement < 0)
		return (false);
	sqrtd = sqrt(discrement);
	root1 = (-constants[1] - sqrtd) / constants[0];
	root2 = (-constants[1] + sqrtd) / constants[0];
	if (root1 > root2)
		swap_d(&root1, &root2);
	if (root1 < rec->min_t || rec->max_t < root1)
	{
		root1 = root2;
		if (root1 < rec->min_t || rec->max_t < root1)
			return (false);
	}
	rec->root = root1;
	return (true);
}
