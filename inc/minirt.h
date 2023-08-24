#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>

# include "libft.h"
# include "vec3.h"
# include "ray.h"

# define DEFAULT_IMAGE_WID 1920
# define DEFAULT_IMAGE_HGT 1080
# define PI 3.1415926535897932385

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"

# define ERR_ARGV_MSG "miniRT : Argument Error : filename with .rt"

typedef struct s_material	t_material;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	t_material	mat;
	double		t;
	double		u;
	double		v;
	bool		front_face;
	int			depth;
}	t_hit_rec;

typedef struct s_camera
{
	t_point3	center;
    t_point3	lower_left_corner;
    t_vec3		horizontal;
    t_vec3		vertical;
    t_vec3		u;
	t_vec3		v;
	t_vec3		w;
	t_color		a_background;
	double		a_ratio;
}	t_camera;

void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec);
void	swap_d(double *left, double *right);

int		minirt_parser(const char *filename, t_list **list, t_camera *camera);

/* parser 관련함수 */
int		data_to_rgb(char *str, t_color *rgb);
int		data_to_point(char *str, t_point3 *point);
int		count_element_2pt_arr(char **data);
int		ambient_data(char **data, t_camera *cam);
int		camera_data(char **data, t_camera *cam);
int		light_data(char **data, t_list **list);
int		sphere_data(char **data, t_list **list);


/* camera.c 관련 함수 */
double	degrees_to_radians(double degrees);
void	set_camera_pos(t_point3 look_from, t_vec3 dir, double hfov, t_camera *cam);
void	set_camera_image(t_color background, double ratio, t_camera *cam);
t_ray	get_ray(t_camera *cam, double s, double t);
#endif
