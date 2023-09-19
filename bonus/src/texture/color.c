#include "texture.h"

t_color	solid_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	return (rgb);
}

t_color	checker_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	int		width;
	int		height;
	t_color	checker;
	int		u;
	int		v;

	width = 10;
	height = 10;
	checker.x = 0.9;
	checker.y = 0.9;
	checker.z = 0.9;
	u = floor(rec->u * width);
	v = floor(rec->v * height);
	if ((u + v) % 2 == 0)
		return (rgb);
	return (checker);
}

t_vec3	bmp_value(t_hit_rec *rec, t_img *img)
{
	double	u;
	double	v;
	double	color_scale;
	t_color	color;
	int		i;
	int		j;
	unsigned char *pixel;

	color_scale = 1.0f / 255;
	u = clamp(fabs(rec->u), 0.0, 1.0);
	v = 1.0 - clamp(fabs(rec->v), 0.0, 1.0);
	i = (int)(u * img->img_width);
	j = (int)(v * img->img_height);
	if (i == img->img_width)
		i--;
	if (j == img->img_height)
		j--;
	pixel = img->data
		+ j * img->bytes_per_scanline
		+ i * img->bytes_per_pixel;
	color.x = clamp(color_scale * pixel[2], 0, 1) * 2 - 1;
	color.y = clamp(color_scale * pixel[1], 0, 1) * 2 - 1;
	color.z = clamp(color_scale * pixel[0], 0, 1) * 2 - 1;
	return (color);
}

t_color	img_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	double	u;
	double	v;
	double	color_scale;
	t_color	color;
	int		i;
	int		j;
	unsigned char *pixel;

	color_scale = 1.0f / 255;
	if (rec->u < 0)
		u = clamp(fabs(rec->u), 0.0, 1.0);
	else
		u = 1 - clamp(rec->u, 0.0, 1.0);
	if (rec->v < 0)
		v = (clamp(fabs(rec->v), 0.0, 1.0));
	else
		v = 1.0 - clamp(rec->v, 0.0, 1.0);
	i = (int)(u * img->img_width);
	j = (int)(v * img->img_height);
	if (i == img->img_width)
		i--;
	if (j == img->img_height)
		j--;
	pixel = img->data
		+ j * img->bytes_per_scanline
		+ i * img->bytes_per_pixel;
	color.x = clamp(color_scale * pixel[2], 0, 1);
	color.y = clamp(color_scale * pixel[1], 0, 1);
	color.z = clamp(color_scale * pixel[0], 0, 1);
	return (color);
}
