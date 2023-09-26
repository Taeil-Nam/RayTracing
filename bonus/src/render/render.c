#include "minirt.h"
#include "bvh.h"
#include "object.h"
#include "vec3.h"
#include "ray.h"

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
		printf("\rScanlines remaining : %d\n", thread->common->cnt++);
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
	int			s;
	t_thread	*thread;

	thread = (t_thread *)arg;
	j = thread->h_start;
	while (j <= thread->h_end)
	{
		pthread_mutex_lock(&thread->common->print_mutex);
		printf("\rScanlines remaining : %d\n", thread->common->cnt++);
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
