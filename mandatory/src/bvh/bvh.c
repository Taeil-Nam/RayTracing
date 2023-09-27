/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:35 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:29:36 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	new_box = (t_aabb *)xmalloc(sizeof(t_aabb));
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
	{
		hittables[start]->left = NULL;
		hittables[start]->right = NULL;
		return (hittables[start]);
	}
	node = (t_hittable *)xmalloc(sizeof(t_hittable));
	comparator = set_comparator();
	quick_sort(hittables, start, end, comparator);
	mid = (start + end) / 2;
	node->hit = aabb_hit;
	node->b_box = aabb_b_box;
	node->left = make_bvh(hittables, start, mid);
	node->right = make_bvh(hittables, mid + 1, end);
	node->object = surrounding_box(node->left->b_box(node->left->object),
			node->right->b_box(node->right->object));
	return (node);
}

bool	hit_bvh(t_hit_rec *rec, t_ray *r, t_hittable *tree)
{
	bool	left_hit;
	bool	right_hit;
	bool	is_hit;

	is_hit = tree->hit(r, rec, tree->object);
	if (!is_hit)
		return (false);
	if (is_hit && tree->left == NULL)
		return (true);
	left_hit = hit_bvh(rec, r, tree->left);
	right_hit = hit_bvh(rec, r, tree->right);
	return (left_hit || right_hit);
}
