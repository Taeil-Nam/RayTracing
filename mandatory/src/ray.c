/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:31:44 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:31:46 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point3	ray_at(t_ray ray, double t)
{
	t_point3	ray_at;

	ray_at = vec3_add(ray.orig, vec3_mul_scalar(ray.dir, t));
	return (ray_at);
}
