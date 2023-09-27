/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:32:08 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:32:10 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "bvh_bonus.h"
#include "object_bonus.h"
#include "vec3_bonus.h"
#include "ray_bonus.h"

void	write_color(t_color color, t_data *image, int i, int j)
{
	double	scale;
	int		pixel;

	scale = 1.0 / (SAMPLE_PER_PIXEL);
	color.x = clamp(sqrt(scale * color.x), 0.0, 0.999);
	color.y = clamp(sqrt(scale * color.y), 0.0, 0.999);
	color.z = clamp(sqrt(scale * color.z), 0.0, 0.999);
	pixel = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8)
		+ ((int)(255.999 * color.z));
	my_mlx_pixel_put(image, i, DEFAULT_IMAGE_HGT - j - 1, pixel);
}

void	*path_trace(void *arg)
{
	t_color		color;
	int			i;
	int			j;
	t_thread	*thread;

	thread = (t_thread *)arg;
	j = thread->h_start;
	while (j <= thread->h_end)
	{
		pthread_mutex_lock(&thread->common->print_mutex);
		printf("\rScanlines remaining : %d\n", thread->common->cnt--);
		pthread_mutex_unlock(&thread->common->print_mutex);
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			color = aa_path(i, j,
					thread->common->minirt, thread->common->bvh);
			write_color(color, &thread->common->minirt->data, i++, j);
		}
		j++;
	}
	return (NULL);
}

void	*phong_trace(void *arg)
{
	t_color		color;
	int			i;
	int			j;
	t_thread	*thread;

	thread = (t_thread *)arg;
	j = thread->h_start;
	while (j <= thread->h_end)
	{
		pthread_mutex_lock(&thread->common->print_mutex);
		printf("\rScanlines remaining : %d\n", thread->common->cnt--);
		pthread_mutex_unlock(&thread->common->print_mutex);
		i = 0;
		while (i < DEFAULT_IMAGE_WID)
		{
			vec3_init(&color, 0, 0, 0);
			color = aa_phong(i, j, thread->common);
			write_color(color, &thread->common->minirt->data, i, j);
			i++;
		}
		j++;
	}
	return (NULL);
}
