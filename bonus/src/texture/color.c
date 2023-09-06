#include "texture.h"

t_color	solid_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	return (rgb);
}

t_color	checker_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	t_color	checker;
	double	sines;

	checker.x = 0.9;
	checker.y = 0.9;
	checker.z = 0.9;
	sines = sin(rec->p.x) * sin(rec->p.y) * sin(rec->p.z);
	if (sines < 0)
		return (rgb);
	return (checker);
}

t_color	img_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	double	u;
	double	v;
	double	color_scale;
	t_color	color;

	color_scale = 1.0f / 255;
	img->data = (unsigned char *)mlx_get_data_addr(img->img_ptr, &img->bytes_per_pixel,
			&img->bytes_per_scanline, &img->endian);
	img->bytes_per_pixel /= 8;
	u = clamp(rec->u, 0.0, 1.0);
	v = 1.0 - clamp(rec->v, 0.0, 1.0);
	img->i = (int)(u * img->img_width);
	img->j = (int)(v * img->img_height);
	img->pixel = img->data
		+ img->j * img->bytes_per_scanline
		+ img->i * img->bytes_per_pixel;
	color.x = clamp(color_scale * img->pixel[2], 0, 1);
	color.y = clamp(color_scale * img->pixel[1], 0 ,1);
	color.z = clamp(color_scale * img->pixel[0], 0 ,1);
	return (color);
}

/*
virtual color value(double u, double v, const vec3& p) const override {
	// If we have no texture data, then return solid cyan as a debugging aid.
	if (data == nullptr)
		return color(0,1,1);

	// Clamp input texture coordinates to [0,1] x [1,0]
	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (i >= width)  i = width-1;
	if (j >= height) j = height-1;

	const auto color_scale = 1.0 / 255.0;
	auto pixel = data + j*bytes_per_scanline + i*bytes_per_pixel;

	return color(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
}
*/
