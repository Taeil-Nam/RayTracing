/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:23 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:25 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_BONUS_H
# define MATERIAL_BONUS_H

# include "minirt_bonus.h"
# include "texture_bonus.h"

typedef t_color	(*t_emit)(t_hit_rec *, t_point3 *, t_texture *);
typedef bool	(*t_scatter)(t_ray *, t_hit_rec *, t_color *, t_ray *);

enum e_mat_type
{
	diffuse,
	metal,
	light,
	dielectric
};

typedef struct s_material
{
	enum e_mat_type	mat_type;
	double			fuzz;
	double			ir;
	t_texture		t;
	t_emit			emit;
	t_scatter		scatter;
}	t_material;

bool	scatter_diffuse(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_light(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_metal(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
bool	scatter_dielectric(t_ray *r, t_hit_rec *rec, t_color *att, t_ray *scat);
t_color	emit_general(t_hit_rec *rec, t_point3 *p, t_texture *t);
t_color	emit_light(t_hit_rec *rec, t_point3 *p, t_texture *t);
#endif
