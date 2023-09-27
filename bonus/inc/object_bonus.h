/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:38 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:40 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_BONUS_H
# define OBJECT_BONUS_H

# include "minirt_bonus.h"
# include "material_bonus.h"

# define DEFAULT_SIZE 5

typedef struct s_aabb
{
	t_point3	p_min;
	t_point3	p_max;
}	t_aabb;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	mat;
}	t_sphere;

typedef struct s_plane
{
	t_point3	p;
	t_vec3		n;
	t_material	mat;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_material	mat;
}	t_cylinder;

typedef struct s_cone
{
	t_point3	center;
	t_point3	top;
	t_vec3		axis;
	t_vec3		n_axis;
	int			is_inf;
	double		radius;
	t_material	mat;
}	t_cone;

bool		sphere_hit(t_ray *r, t_hit_rec *rec, void *object);
bool		aabb_hit(t_ray *r, t_hit_rec *rec, void *object);
bool		plane_hit(t_ray *r, t_hit_rec *rec, void *object);
bool		cylinder_hit(t_ray *r, t_hit_rec *rec, void *object);
bool		cone_hit(t_ray *r, t_hit_rec *rec, void *object);

t_aabb		sphere_b_box(void *object);
t_aabb		plane_b_box(void *object);
t_aabb		cylinder_b_box(void *object);
t_aabb		aabb_b_box(void *object);
t_aabb		cone_b_box(void *object);

bool		quadratic_formular(double constants[3], t_hit_rec *rec);

void		get_sphere_uv(t_vec3 o_n, t_hit_rec *rec);
void		get_cone_uv(t_vec3 o_n, t_hit_rec *rec,
				double p_height, t_cone *cone);
void		get_cylinder_uv(t_vec3 o_n, t_hit_rec *rec,
				double p_height, t_cylinder *cy);
void		get_plane_uv(t_vec3 o_n, t_point3 p, t_hit_rec *rec);

#endif
