/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:47 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:49 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BONUS_H
# define RAY_BONUS_H

# include "vec3_bonus.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

t_point3	ray_at(t_ray ray, double t);

#endif
