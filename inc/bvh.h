#ifndef BVH_H
# define BVH_H

# include "minirt.h"
# include "object.h"

typedef bool	(*t_hit)(t_ray *, double, double, t_hit_rec *, void *);
typedef t_aabb	(*t_b_box)(void *);
typedef int		(*t_comparator)(t_hittable *, t_hittable *);

typedef struct s_hittable
{
	t_vec3				center;
	void				*object;
	t_hit				hit;
	t_b_box				b_box;
	struct s_hittable	*left;
	struct s_hittable	*right;
}	t_hittable;

/* bvh_utils.c */
t_hittable	**list_to_hittable_arr(t_list *list);
void		quick_sort(t_hittable **arr, int left, int right,
					t_comparator comparator);

/* comparator.c */
int	compare_x(t_hittable *left, t_hittable *right);
int	compare_y(t_hittable *left, t_hittable *right);
int	compare_z(t_hittable *left, t_hittable *right);

#endif
