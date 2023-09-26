#include "parser.h"
#include "bvh.h"

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
	cam->a_background.x = background.x * ratio;
	cam->a_background.y = background.y * ratio;
	cam->a_background.z = background.z * ratio;
	cam->a_ratio = ratio;
}

void	set_camera_pos(t_point3 look_from, t_vec3 dir,
						double hfov, t_camera *cam)
{
	t_vec3	vup;
	double	viewport_h;
	double	viewport_w;

	if (dir.x == 0 && dir.z == 0 && dir.y < 0)
		vec3_init(&vup, 0, 0, 1);
	else if (dir.x == 0 && dir.z == 0 && dir.y > 0)
		vec3_init(&vup, 0, 0, -1);
	else
		vec3_init(&vup, 0, 1, 0);
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

int	camera_data(char **data, t_minirt *minirt)
{
	t_point3	look_from;
	t_vec3		dir;
	double		hfov;

	if (minirt->is_camera_in_map == false)
		minirt->is_camera_in_map = true;
	else
		return (-1);
	if (count_element_2pt_arr(data) != 4)
		return (-1);
	if (data_to_point(data[1], &look_from) == -1)
		return (-1);
	if (data_to_point(data[2], &dir) == -1)
		return (-1);
	if (check_nan_in_vec3(dir))
		return (-1);
	hfov = ft_atoi(data[3]);
	if (hfov < 0 || hfov > 180)
		return (-1);
	set_camera_pos(look_from, dir, hfov, &minirt->cam);
	return (1);
}
