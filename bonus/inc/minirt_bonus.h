/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:29 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:31 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>

# include "libft.h"
# include "mlx_utils_bonus.h"
# include "vec3_bonus.h"
# include "ray_bonus.h"

# define LUMEN 3
# define THREAD_NUM 20
# define SAMPLE_PER_PIXEL 10
# define DEPTH 50
# define DEFAULT_IMAGE_WID 900
# define DEFAULT_IMAGE_HGT 600
# define PI 3.1415926535897932385
# define KSN 64
# define KS 0.6
# define TILE_SIZE 100

# define PHONG 0
# define PATH 1

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

typedef struct s_minirt
{
	t_vars		vars;
	t_data		data;
	t_camera	cam;
	int			sample_per_pixel;
	int			depth;
	int			illumination;
	int			is_camera_in_map;
	int			is_ambient_in_map;
	t_sphere	*light;
}	t_minirt;

typedef struct s_common
{
	pthread_mutex_t	print_mutex;
	t_hittable		*bvh;
	t_minirt		*minirt;
	t_sphere		**light_lst;
	int				cnt;
}	t_common;

typedef struct s_thread
{
	pthread_t		thread;
	t_common		*common;
	int				h_start;
	int				h_end;
}	t_thread;

/* rendering */
t_color	phong_color(t_ray r, t_common *common);
t_color	ray_color(t_ray r, t_camera *cam, t_hittable *bvh, int depth);
void	*path_trace(void *thread);
void	*phong_trace(void *thread);
t_ray	get_ray(t_camera *cam, double s, double t);
t_color	aa_path(int i, int j, t_minirt *minirt, t_hittable *bvh);
t_color	aa_phong(int i, int j, t_common *common);

/* miniRT utils */
void	set_face_normal(t_ray *r, t_vec3 o_n, t_hit_rec *rec);
void	swap_d(double *left, double *right);
double	clamp(double x, double min, double max);
double	random_double(void);
double	random_double_mm(double min, double max);
void	*xmalloc(size_t size);
void	minirt_error_exit(void);
void	minirt_str_error_exit(char *str);
void	free_mem(t_hittable *bvh, t_hittable **hittables, t_sphere **light_lst);

/* parser */
int		minirt_parser(const char *filename, t_list **list, t_minirt *minirt);

/* thread */
void	multi_threading(t_thread *threads, t_minirt *minirt);

#endif
