#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# include "libft.h"
# include "mlx_utils.h"
# include "vec3.h"
# include "ray.h"

# define SAMPLE_PER_PIXEL 10
# define DEPTH 50
# define DEFAULT_IMAGE_WID 1600
# define DEFAULT_IMAGE_HGT 900
# define PI 3.1415926535897932385
# define KSN 64
# define KS 0.6

# define PHONG 0
# define PATH 1
# define RENDERING 0
# define EDITING 1

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"

# define DIFFUSE "D"
# define METAL "M"
# define DIELECTRIC "DI"

# define SOLID "S"
# define CHECKER "CH"
# define IMAGE "IMG"

# define COMMENT "#"

# define ERR_ARGV_MSG "Error\nminiRT : Argument Error : filename with .rt"
# define ERR_INV_FILE "Error\nminiRT : invalid file format: .rt"
# define ERR_MAP "Error\nminiRT : Map Error!"

typedef struct s_material	t_material;
typedef struct s_texture	t_texture;
typedef struct s_hittable	t_hittable;
typedef struct s_sphere		t_sphere;


typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	t_material	*mat;
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

typedef struct s_minirt
{
	t_vars		vars;
	t_data		data;
	t_camera	cam;
	int			sample_per_pixel;
	int			depth;
	int			illumination; //phong or path
	int			mode; //editing or rendering
}	t_minirt;

/* rendering 함수 */
t_color	phong_color(t_ray r, t_camera *cam, t_hittable *bvh, t_sphere *l);
t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth);
void	path_trace(t_hittable *bvh, t_minirt *minirt);
void	phong_trace(t_hittable *bvh, t_minirt *minirt, t_sphere **light_lst);
void	write_color(t_color color, t_data *image, int i, int j);

/* miniRT utils */
void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec);
void	swap_d(double *left, double *right);
double	clamp(double x, double min, double max);
double	random_double(void);
void	*xmalloc(size_t size);
void	minirt_error_exit(void);
void	minirt_str_error_exit(char *str);

/* parser */
int			minirt_parser(const char *filename, t_list **list, t_minirt *minirt);
int			data_to_rgb(char *str, t_color *rgb);
int			data_to_point(char *str, t_point3 *point);
int			count_element_2pt_arr(char **data);
int			ambient_data(char **data, t_camera *cam);
int			camera_data(char **data, t_camera *cam);
int			light_data(char **data, t_list **list);
int			init_material(t_material *mat, char *mat_line);
int			init_object(t_hittable *hittable, char *obj_line);
int			init_texture(t_texture *tex, char *line, t_minirt *minirt);
int			plane_initializer(t_hittable *hittable, char **data, t_minirt *minirt);
int			cylinder_initializer(t_hittable *hittable, char **data, t_minirt *minirt);
int			sphere_initializer(t_hittable *hittable, char **data, t_minirt *minirt);
t_sphere	*light_initializer(t_point3 center, double ratio, t_color rgb);
int			object_constructor(char **data, t_list **list, t_minirt *minirt);
int			world_constructor(char *line, t_list **list, t_camera *camera);
void		free_hittables(void *hittable);

/* camera.c 관련 함수 */
double	degrees_to_radians(double degrees);
void	set_camera_pos(t_point3 look_from, t_vec3 dir,
			double hfov, t_camera *cam);
void	set_camera_image(t_color background, double ratio, t_camera *cam);
t_ray	get_ray(t_camera *cam, double s, double t);

#endif
