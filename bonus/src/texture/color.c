#include "texture.h"

t_color	solid_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	return (rgb);
}

t_color	checker_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
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

t_color	bmp_value(double u, double v, t_img *bmp_img)
{
	double	color_scale;
	t_color	color;

	color_scale = 1.0f / 255;
	bmp_img->data
		= (unsigned char *)mlx_get_data_addr(bmp_img->img_ptr,
			&bmp_img->bytes_per_pixel, &bmp_img->bytes_per_scanline, &bmp_img->endian);
	bmp_img->bytes_per_pixel /= 8;
	u = clamp(fabs(u), 0.0, 1.0);
	v = 1.0 - clamp(fabs(v), 0.0, 1.0);
	bmp_img->i = (int)(u * bmp_img->img_width);
	bmp_img->j = (int)(v * bmp_img->img_height);
	if (bmp_img->i == bmp_img->img_width)
		bmp_img->i--;
	if (bmp_img->j == bmp_img->img_height)
		bmp_img->j--;
	bmp_img->pixel = bmp_img->data
		+ bmp_img->j * bmp_img->bytes_per_scanline
		+ bmp_img->i * bmp_img->bytes_per_pixel;
	color.x = clamp(color_scale * bmp_img->pixel[2], 0, 1);
	color.y = clamp(color_scale * bmp_img->pixel[1], 0, 1);
	color.z = clamp(color_scale * bmp_img->pixel[0], 0, 1);
	return (color);
}

t_color	img_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	double	u;
	double	v;
	double	color_scale;
	t_color	color;

	color_scale = 1.0f / 255;
	img->data
		= (unsigned char *)mlx_get_data_addr(img->img_ptr,
			&img->bytes_per_pixel, &img->bytes_per_scanline, &img->endian);
	img->bytes_per_pixel /= 8;
	u = clamp(fabs(rec->u), 0.0, 1.0);
	v = 1.0 - clamp(fabs(rec->v), 0.0, 1.0);
	img->i = (int)(u * img->img_width);
	img->j = (int)(v * img->img_height);
	if (img->i == img->img_width)
		img->i--;
	if (img->j == img->img_height)
		img->j--;
	img->pixel = img->data
		+ img->j * img->bytes_per_scanline
		+ img->i * img->bytes_per_pixel;
	color.x = clamp(color_scale * img->pixel[2], 0, 1);
	color.y = clamp(color_scale * img->pixel[1], 0, 1);
	color.z = clamp(color_scale * img->pixel[0], 0, 1);
	if (bum_img->img_ptr != NULL)
		color = vec3_mul_scalar(vec3_add(color, bmp_value(rec->u, rec->v, bum_img)), 0.5);
	return (color);
}
