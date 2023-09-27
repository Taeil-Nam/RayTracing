/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:37 by gunjkim           #+#    #+#             */
/*   Updated: 2023/09/27 12:31:04 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bvh.h"

void	free_bvh(t_hittable *node)
{
	if (node->left == NULL && node->right == NULL)
		return ;
	free_bvh(node->left);
	free_bvh(node->right);
	free(node->object);
	free(node);
}

void	free_mem(t_world *world, t_hittable **hittables)
{
	int	i;

	free_bvh(world->bvh);
	i = 0;
	while (hittables[i] != NULL)
	{
		free(hittables[i]->object);
		free(hittables[i]);
		i++;
	}
	free(hittables);
	free(world->light_lst);
}
