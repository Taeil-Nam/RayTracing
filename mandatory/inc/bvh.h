/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:05 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:31:55 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"
# include "object.h"

typedef bool	(*t_hit)(t_ray *, t_hit_rec *, void *);
typedef t_aabb	(*t_b_box)(void *);

typedef struct s_hittable
{
	void				*object;
	t_vec3				center;
	t_hit				hit;
	t_b_box				b_box;
	struct s_hittable	*left;
	struct s_hittable	*right;
}	t_hittable;

typedef int		(*t_comparator)(t_hittable *, t_hittable *);

/* bvh.c */
t_hittable	*make_bvh(t_hittable **hittables, int i, int j);
bool		hit_bvh(t_hit_rec *rec, t_ray *r, t_hittable *tree);

/* bvh_utils.c */
void		dummy(void *object);
t_hittable	**list_to_hittable_arr(t_list *list);
t_sphere	**make_light_lst(t_hittable **hittables);
void		quick_sort(t_hittable **arr, int left, int right,
				t_comparator comparator);

/* comparator.c */
int			compare_x(t_hittable *left, t_hittable *right);
int			compare_y(t_hittable *left, t_hittable *right);
int			compare_z(t_hittable *left, t_hittable *right);

#endif
