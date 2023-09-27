/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:16 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:30:17 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_bonus.h"

t_color	emit_general(t_hit_rec *rec, t_point3 *p, t_texture *t)
{
	t_color	ret;

	(void)rec;
	(void)p;
	(void)t;
	ret.x = 0;
	ret.y = 0;
	ret.z = 0;
	return (ret);
}

t_color	emit_light(t_hit_rec *rec, t_point3 *p, t_texture *t)
{
	(void)p;
	return (t->value(rec, &t->img, t->rgb));
}
