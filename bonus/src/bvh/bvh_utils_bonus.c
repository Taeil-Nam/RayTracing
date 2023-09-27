/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:07 by tnam              #+#    #+#             */
/*   Updated: 2023/09/27 12:30:08 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_bonus.h"

void	dummy(void *object)
{
	(void)object;
	return ;
}

t_hittable	**list_to_hittable_arr(t_list *list)
{
	int			size;
	int			index;
	t_hittable	**arr;

	index = 0;
	if (list == NULL)
		return (NULL);
	size = ft_lstsize(list);
	arr = (t_hittable **)xmalloc(sizeof(t_hittable *) * (size + 1));
	while (list != NULL)
	{
		arr[index] = list->content;
		list = list->next;
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

t_sphere	**make_light_lst(t_hittable **hittables)
{
	int			count;
	int			i;
	t_sphere	*tmp;
	t_sphere	**light_lst;

	count = 0;
	i = 0;
	while (hittables[i] != NULL)
	{
		tmp = (t_sphere *)(hittables[i++]->object);
		if (tmp->mat.mat_type == light)
			count++;
	}
	light_lst = (t_sphere **)xmalloc(sizeof(t_sphere *) * (count + 1));
	i = 0;
	count = 0;
	while (hittables[i] != NULL)
	{
		tmp = (t_sphere *)(hittables[i++]->object);
		if (tmp->mat.mat_type == light)
			light_lst[count++] = tmp;
	}
	light_lst[count] = NULL;
	return (light_lst);
}

void	quick_sort(t_hittable **arr, int left, int right,
					t_comparator comparator)
{
	int			i;
	int			j;
	t_hittable	*key;

	i = left;
	j = right;
	key = arr[left];
	if (left >= right)
		return ;
	while (i < j)
	{
		while (i < j && comparator(arr[j], key) >= 0)
			j--;
		arr[i] = arr[j];
		while (i < j && comparator(arr[i], key) <= 0)
			i++;
		arr[j] = arr[i];
	}
	arr[i] = key;
	quick_sort(arr, left, i - 1, comparator);
	quick_sort(arr, i + 1, right, comparator);
}
