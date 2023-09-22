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
