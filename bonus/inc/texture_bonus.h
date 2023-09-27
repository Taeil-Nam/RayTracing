/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:51 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:53 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_BONUS_H
# define TEXTURE_BONUS_H

# include "minirt_bonus.h"

enum e_texture_type
{
	solid,
	checker,
	image
};

typedef struct s_img
{
	void			*img_ptr;
	unsigned char	*data;
	int				img_width;
	int				img_height;
	int				bytes_per_pixel;
	int				bytes_per_scanline;
	int				endian;
	int				i;
	int				j;
	unsigned char	*pixel;
}	t_img;

typedef struct s_img_var
{
	double			u;
	double			v;
	double			color_scale;
	t_color			color;
	int				i;
	int				j;
	unsigned char	*pixel;
}	t_img_var;

typedef t_color	(*t_value)(t_hit_rec *, t_img *, t_color);

typedef struct s_texture
{
	enum e_texture_type	tex_type;
	t_color				rgb;
	t_img				img;
	t_img				bmp_img;
	t_value				value;
}	t_texture;

t_color	solid_value(t_hit_rec *rec, t_img *img, t_color rgb);
t_color	checker_value(t_hit_rec *rec, t_img *img, t_color rgb);
t_color	img_value(t_hit_rec *rec, t_img *img, t_color rgb);
t_vec3	bmp_value(t_hit_rec *rec, t_img *img);
#endif
