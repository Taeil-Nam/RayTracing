/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:56 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:57 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_BONUS_H
# define VEC3_BONUS_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

/* vec3_1.c */
t_vec3	vec3_add(t_vec3 left, t_vec3 right);
t_vec3	vec3_sub(t_vec3 left, t_vec3 right);
t_vec3	vec3_mul_vec3(t_vec3 left, t_vec3 right);
t_vec3	vec3_mul_scalar(t_vec3 left, double right);

/* vec3_2.c */
double	vec3_length(t_vec3 v);
double	vec3_squared(t_vec3 v);
double	vec3_dot(t_vec3 left, t_vec3 right);
t_vec3	vec3_cross(t_vec3 left, t_vec3 right);
t_vec3	vec3_unit(t_vec3 v);

/* vec3_3.c */
t_vec3	vec3_random(void);
t_vec3	vec3_random_mm(double min, double max);
t_vec3	vec3_random_in_unit_sphere(void);
t_vec3	vec3_random_unit(void);

/* vec3_4.c */
bool	vec3_near_zero(t_vec3 v);
void	vec3_print(t_vec3 v);
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);

/* vec3_5.c */
void	vec3_init(t_vec3 *v, double x, double y, double z);
t_vec3	vec3_instant(double x, double y, double z);

#endif
