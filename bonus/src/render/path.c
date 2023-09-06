#include "minirt.h"
#include "object.h"
#include "bvh.h"
#include "vec3.h"
#include "ray.h"

t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth)
{
	t_hit_rec	rec;
	t_color		basic;
	t_ray		scattered;
	t_color		attenuation;
	t_color		emit;

	basic.x = 0;
	basic.y = 0;
	basic.z = 0;
	rec.depth = depth;
	if (depth <= 0)
		return (basic);
	if (!hit_bvh(&rec, 0.001, INFINITY, &r, bvh))
		return (vec3_mul_scalar(cam->a_background, cam->a_ratio));
	emit = rec.mat->emit(&rec, &rec.p, &rec.mat->t);
	if (!rec.mat->scatter(&r, &rec, &attenuation, &scattered))
		return (vec3_mul_scalar(emit, 3));
	return (vec3_add(emit, vec3_mul_vec3(attenuation,
				ray_color(scattered, cam, bvh, depth - 1))));
}

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
