#include "minirt.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

t_vec3	get_lower_left_corner(t_camera *cam)
{
	t_vec3	ret;
	t_vec3	half_h;
	t_vec3	half_v;

	half_h = vec3_mul_scalar(cam->horizontal, 0.5);
	half_v = vec3_mul_scalar(cam->vertical, 0.5);
	ret = vec3_sub(cam->center, half_h);
	ret = vec3_sub(ret, half_v);
	ret = vec3_add(ret, cam->w);
	return (ret);
}

void	set_camera_image(t_color background, double ratio, t_camera *cam)
{
	cam->a_background.x = background.x;
	cam->a_background.y = background.y;
	cam->a_background.z = background.z;
	cam->a_ratio = ratio;
}

void	set_camera_pos(t_point3 look_from, t_vec3 dir,
						double hfov, t_camera *cam)
{
	t_vec3	vup;
	double	viewport_h;
	double	viewport_w;

	vup.x = 0;
	vup.y = 1.0;
	vup.z = 0;
	viewport_w = tan(degrees_to_radians(hfov) / 2) * 2.0;
	viewport_h = viewport_w * ((double)DEFAULT_IMAGE_HGT / DEFAULT_IMAGE_WID);
	cam->w = vec3_unit(dir);
	cam->u = vec3_unit(vec3_cross(vup, cam->w));
	cam->v = vec3_cross(cam->w, cam->u);
	cam->center = look_from;
	cam->horizontal = vec3_mul_scalar(cam->u, viewport_w);
	cam->vertical = vec3_mul_scalar(cam->v, viewport_h);
	cam->lower_left_corner = get_lower_left_corner(cam);
}

t_ray	get_ray(t_camera *cam, double s, double t)
{
	t_ray	ret;

	ret.orig = cam->center;
	ret.dir.x = cam->lower_left_corner.x + cam->horizontal.x * s + \
				cam->vertical.x * t - cam->center.x;
	ret.dir.y = cam->lower_left_corner.y + cam->horizontal.y * s + \
				cam->vertical.y * t - cam->center.y;
	ret.dir.z = cam->lower_left_corner.z + cam->horizontal.z * s + \
				cam->vertical.z * t - cam->center.z;
	return (ret);
}
