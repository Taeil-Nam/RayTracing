/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:24 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:29:24 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"

typedef t_color	(*t_value)(t_hit_rec *, t_color);

enum e_texture_type
{
	solid,
	checker,
	image
};

typedef struct s_texture
{
	enum e_texture_type	tex_type;
	t_color				rgb;
	t_value				value;
}	t_texture;

t_color	solid_value(t_hit_rec *rec, t_color rgb);

#endif
