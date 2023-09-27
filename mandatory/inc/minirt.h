/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:16 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:29:17 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# include "libft.h"
# include <mlx.h>
# include "vec3.h"
# include "ray.h"

# define SAMPLE_PER_PIXEL 3
# define DEFAULT_IMAGE_WID 1600
# define DEFAULT_IMAGE_HGT 1000
# define PI 3.1415926535897932385
# define KSN 64
# define KS 0.6

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"

# define ERR_ARGV_MSG "Error\nminiRT : Argument Error : filename with .rt"
# define ERR_INV_FILE "Error\nminiRT : invalid file format: .rt"
# define ERR_MAP "Error\nminiRT : Map Error!"

typedef struct s_material	t_material;
typedef struct s_hittable	t_hittable;
typedef struct s_sphere		t_sphere;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_hit_record
{
	t_point3	p;
	t_point3	center;
	t_vec3		normal;
	t_material	*mat;
	double		root;
	double		min_t;
	double		max_t;
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

typedef struct s_world
{
	t_hittable	*bvh;
	t_camera	cam;
	t_sphere	**light_lst;
	int			is_light_in_map;
	int			is_camera_in_map;
	int			is_ambient_in_map;
}	t_world;

/* rendering */
void	phong_trace(t_data *image, t_world *world);
t_color	phong_color(t_ray r, t_world *world);
void	write_color(t_color color, t_data *image, int i, int j);

/* utils */
void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec);
void	swap_d(double *left, double *right);
double	clamp(double x, double min, double max);
double	random_double(void);
t_color	black_color(void);
void	*xmalloc(size_t size);
void	minirt_error_exit(void);
void	minirt_str_error_exit(char *str);
void	free_mem(t_world *world, t_hittable **hittables);

/* miniRT utils */
int		exit_hook(void);
int		key_hook(int keycode, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	minirt_init(t_data *image, t_vars *vars);

/* parser */
int		minirt_parser(const char *filename, t_list **list, t_world *world);
int		data_to_rgb(char *str, t_color *rgb);
int		data_to_point(char *str, t_point3 *point);
int		count_element_2pt_arr(char **data);
int		ambient_data(char **data, t_world *world);
int		camera_data(char **data, t_world *world);
int		light_data(char **data, t_list **list, t_world *world);
int		sphere_data(char **data, t_list **list);
int		plane_data(char **data, t_list **list);
int		cylinder_data(char **data, t_list **list);
bool	check_nan_in_vec3(t_vec3 v);
bool	is_value_btw_one(t_vec3 vec);

/* camera */
double	degrees_to_radians(double degrees);
void	set_camera_pos(t_point3 look_from, t_vec3 dir,
			double hfov, t_camera *cam);
void	set_camera_image(t_color background, double ratio, t_camera *cam);
t_ray	get_ray(t_camera *cam, double s, double t);

#endif
