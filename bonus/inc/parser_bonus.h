/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:43 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:29:44 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "minirt_bonus.h"

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"
# define CONE "co"

# define DIFFUSE "D"
# define METAL "M"
# define DIELECTRIC "DI"

# define INF "INF"
# define NOT_INF "NOT_INF"
# define NO_BMP "NO_BMP"

# define SOLID "S"
# define CHECKER "CH"
# define IMAGE "IMG"

# define COMMENT "#"

int			data_to_rgb(char *str, t_color *rgb);
int			data_to_point(char *str, t_point3 *point);
int			count_element_2pt_arr(char **data);
int			ambient_data(char **data, t_minirt *minirt);
int			camera_data(char **data, t_minirt *minirt);
int			light_data(char **data, t_list **list, t_minirt *minirt);
int			init_material(t_material *mat, char *mat_line);
int			init_object(t_hittable *hittable, char *obj_line);
int			init_texture(t_texture *tex, char *line, t_minirt *minirt);
int			plane_initializer(t_hittable *hittable,
				char **data, t_minirt *minirt);
int			cylinder_initializer(t_hittable *hittable,
				char **data, t_minirt *minirt);
int			cone_initializer(t_hittable *hittable,
				char **data, t_minirt *minirt);
int			sphere_initializer(t_hittable *hittable,
				char **data, t_minirt *minirt);
t_sphere	*light_initializer(t_point3 center, double ratio,
				t_color rgb, t_minirt *minirt);
int			object_constructor(char **data, t_list **list, t_minirt *minirt);
int			world_constructor(char *line, t_list **list, t_minirt *minirt);
void		free_hittables(void *hittable);
bool		check_nan_in_vec3(t_vec3 v);
double		degrees_to_radians(double degrees);
void		set_camera_pos(t_point3 look_from, t_vec3 dir,
				double hfov, t_camera *cam);
void		set_camera_image(t_color background, double ratio, t_camera *cam);
int			init_cone(t_hittable *new_object, char **data);
bool		is_value_btw_one(t_vec3 vec);

#endif