#include "bvh.h"

int	random_int_mm(int min, int max);

t_comparator	set_comparator(void)
{
	int	random_num;

	random_num = random_int_mm(0, 2);
	if (random_num == 0)
		return (compare_x);
	else if (random_num == 1)
		return (compare_y);
	return (compare_z);
}

t_aabb	*surrounding_box(t_aabb box1, t_aabb box2)
{
	t_aabb	*new_box;

	new_box = (t_aabb *)malloc(sizeof(t_aabb));
	new_box->p_min.x = fmin(box1.p_min.x, box2.p_min.x);
	new_box->p_min.y = fmin(box1.p_min.y, box2.p_min.y);
	new_box->p_min.z = fmin(box1.p_min.z, box2.p_min.z);
	new_box->p_max.x = fmax(box1.p_max.x, box2.p_max.x);
	new_box->p_max.y = fmax(box1.p_max.y, box2.p_max.y);
	new_box->p_max.z = fmax(box1.p_max.z, box2.p_max.z);
	return (new_box);
}

t_hittable	*make_bvh(t_hittable **hittables, int start, int end)
{
	t_hittable		*node;
	t_comparator	comparator;
	int				mid;

	if (start == end)
		return (hittables[start]);
	node = (t_hittable *)malloc(sizeof(t_hittable));
	comparator = set_comparator();
	quick_sort(hittables, start, end, comparator);
	mid = (start + end) / 2;
	// node->hit = aabb_hit;
	// node->b_box = aabb_b_box;
	node->left = make_bvh(hittables, start, mid);
	node->right = make_bvh(hittables, mid, end);
	node->object = surrounding_box(node->left->b_box(node->left->object),
			node->right->b_box(node->right->object));
	return (node);
}
