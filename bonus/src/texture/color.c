#include "texture.h"

t_color	solid_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	return (rgb);
}

//t_color	checker_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
//{
//	// cy
//	int		width;
//	int		height;
//	t_color	checker;
//	double	u;
//	double	v;
//	int		u2;
//	int		v2;
//	int		u_div;
//	int		v_div;

//	width = 3;
//	height = 3;
//	checker.x = 0.9;
//	checker.y = 0.9;
//	checker.z = 0.9;

//	/*
//	function cylindrical_map(p)
//	# compute the azimuthal angle, same as with spherical_map()
//	let theta ← arctan2(p.x, p.z)
//	let raw_u ← theta / (2 * π)
//	let u ← 1 - (raw_u + 0.5)

//	# let v go from 0 to 1 between whole units of y
//	let v ← p.y mod 1

//	return (u, v)
//	end function
//	*/

//	u = 1 - ((atan2(rec->p.x, rec->p.z) / (2.0f * PI)) + 0.5f);
//	v = rec->p.y;
//	v_div = v / 1;
//	if (v >= 0)
//		v = v - v_div;
//	else
//		v = v - v_div + 1;

//	u2 = floor(u * width);
//	v2 = floor(v * height);
//	if ((u2 + v2) % 2 == 0)
//		return (rgb);
//	return (checker);
//}

//t_color	checker_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
//{
//	// sp
//	int		width;
//	int		height;
//	t_color	checker;
//	int		u;
//	int		v;

//	width = 10;
//	height = 10;
//	checker.x = 0.9;
//	checker.y = 0.9;
//	checker.z = 0.9;
//	u = floor(rec->u * width);
//	v = floor(rec->v * height);
//	if ((u + v) % 2 == 0)
//		return (rgb);
//	return (checker);
//}

//t_color	checker_value_pl(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
//{
//	//pl
//	t_color	checker;
//	double	sines;

//	checker.x = 0.9;
//	checker.y = 0.9;
//	checker.z = 0.9;
//	sines = sin(rec->p.x) * sin(rec->p.y) * sin(rec->p.z);
//	if (sines < 0)
//		return (rgb);
//	return (checker);
//}

t_color	checker_value(t_hit_rec *rec, t_img *img, t_img *bum_img, t_color rgb)
{
	// default checker
	t_color	checker;
	double	sines;

	checker.x = 0.9;
	checker.y = 0.9;
	checker.z = 0.9;
	sines = sin(rec->p.x) * sin(rec->p.y) * sin(rec->p.z);
	if (sines < 0)
		return (rgb);
	return (checker);
	// t_color checker;
    // double sines;

    // checker.x = 0.9;
    // checker.y = 0.9;
    // checker.z = 0.9;

    // // 평면의 normal 벡터를 기준으로 체커보드 패턴 배치
    // double dx = rec->p.x - rec->center.x;
	// double dy = rec->p.y - rec->center.y;
    // double dz = rec->p.z - rec->center.z;

    // int i = (int)(floor(dx)) + (int)(floor(dz));
    // int j = (int)(floor(dy));

    // // 체커보드 패턴 선택
    // if ((i + j) % 2 == 0)
    //     return checker;
    // else
    //     return rgb;
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
	u = clamp(rec->u, 0.0, 1.0);
	v = 1.0 - clamp(rec->v, 0.0, 1.0);
	img->i = (int)(u * img->img_width);
	img->j = (int)(v * img->img_height);
	img->pixel = img->data
		+ img->j * img->bytes_per_scanline
		+ img->i * img->bytes_per_pixel;
	color.x = clamp(color_scale * img->pixel[2], 0, 1);
	color.y = clamp(color_scale * img->pixel[1], 0, 1);
	color.z = clamp(color_scale * img->pixel[0], 0, 1);
	return (color);
}
