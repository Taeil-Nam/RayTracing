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
		return (emit);
	return (vec3_add(emit, vec3_mul_vec3(attenuation,
				ray_color(scattered, cam, bvh, depth - 1))));
}
