#include "bvh.h"

void	dummy(void *object)
{
	object = NULL;
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
	arr = (t_hittable **)malloc(sizeof(t_hittable *) * size);
	while (list != NULL)
	{
		arr[index] = list->content;
		list = list->next;
		index++;
	}
	return (arr);
}

void	quick_sort(t_hittable **arr, int left, int right,
					t_comparator comparator)
{
	int			i;
	int			j;
	t_hittable	*key;

	printf("%d, %d, %p\n", left, right,  comparator); //
	i = left;
	j = right;
	key = arr[left];
	if (left >= right)
        return;
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
