#include "libft.h"
#include <stdio.h>

t_list	*ft_lstnew(void	*content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		perror("ft_lstnew");
		exit(1);
	}
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}
