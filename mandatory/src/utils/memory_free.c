#include "minirt.h"
#include "bvh.h"
/*
	--- free variable list ---
	1. t_hittable**			hittables
		1-1. t_hittable*	hittables[i]
		1-2. void*			hittables[i]->object
	2. t_sphere**			light_lst
		2-1. t_sphere*		1-1과 겹침. free 불필요.
	3. t_hittable*			bvh(root node)
		: tree의 root node이기 때문에, bvh->left, bvh->right 타고 들어가서 자식 node들 전부 free 필요.
	4. t_aabb*				bvh->object
		: bvh tree의 맨 밑 노드들은 1-1과 겹치므로, double free 주의.
	---
*/

void	free_bvh(t_hittable *node)
{
	if (node->left == NULL && node->right == NULL)
		return ;
	free_bvh(node->left);
	free_bvh(node->right);
	free(node->object);
	free(node);
}

void	free_mem(t_hittable *bvh, t_hittable **hittables, t_sphere **light_lst)
{
	int	i;

	free_bvh(bvh);
	i = 0;
	while (hittables[i] != NULL)
	{
		free(hittables[i]->object);
		free(hittables[i]);
		i++;
	}
	free(hittables);
	free(light_lst);
}
