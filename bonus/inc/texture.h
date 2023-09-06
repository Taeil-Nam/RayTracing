#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"


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

typedef t_color	(*t_value)(t_hit_rec *, t_img *, t_img *, t_color);

typedef struct s_texture
{
	enum e_texture_type	tex_type;
	t_color				rgb;
	t_img				img;
	t_img				bmp_img;
	t_value				value;
}	t_texture;

t_color	solid_value(t_hit_rec *rec, t_img *img,
			t_img *bum_img, t_color rgb);
t_color	checker_value(t_hit_rec *rec, t_img *img,
			t_img *bum_img, t_color rgb);
t_color	img_value(t_hit_rec *rec, t_img *img,
			t_img *bum_img, t_color rgb);

#endif
