/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:14 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:15 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_bonus.h"

t_color	solid_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	(void)rec;
	(void)img;
	return (rgb);
}

t_color	checker_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	int		width;
	int		height;
	t_color	checker;
	int		u;
	int		v;

	(void)img;
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
	t_img_var	var;

	var.color_scale = 1.0f / 255;
	var.u = clamp(fabs(rec->u), 0.0, 1.0);
	var.v = 1.0 - clamp(fabs(rec->v), 0.0, 1.0);
	var.i = (int)(var.u * img->img_width);
	var.j = (int)(var.v * img->img_height);
	if (var.i == img->img_width)
		var.i--;
	if (var.j == img->img_height)
		var.j--;
	var.pixel = img->data
		+ var.j * img->bytes_per_scanline
		+ var.i * img->bytes_per_pixel;
	var.color.x = clamp(var.color_scale * var.pixel[2], 0, 1) * 2 - 1;
	var.color.y = clamp(var.color_scale * var.pixel[1], 0, 1) * 2 - 1;
	var.color.z = clamp(var.color_scale * var.pixel[0], 0, 1) * 2 - 1;
	return (var.color);
}

t_color	img_value(t_hit_rec *rec, t_img *img, t_color rgb)
{
	t_img_var	var;

	rgb = (t_color)rgb;
	var.color_scale = 1.0f / 255;
	if (rec->u < 0)
		var.u = clamp(fabs(rec->u), 0.0, 1.0);
	else
		var.u = 1 - clamp(rec->u, 0.0, 1.0);
	if (rec->v < 0)
		var.v = (clamp(fabs(rec->v), 0.0, 1.0));
	else
		var.v = 1.0 - clamp(rec->v, 0.0, 1.0);
	var.i = (int)(var.u * img->img_width);
	var.j = (int)(var.v * img->img_height);
	if (var.i == img->img_width)
		var.i--;
	if (var.j == img->img_height)
		var.j--;
	var.pixel = img->data
		+ var.j * img->bytes_per_scanline
		+ var.i * img->bytes_per_pixel;
	var.color.x = clamp(var.color_scale * var.pixel[2], 0, 1);
	var.color.y = clamp(var.color_scale * var.pixel[1], 0, 1);
	var.color.z = clamp(var.color_scale * var.pixel[0], 0, 1);
	return (var.color);
}
