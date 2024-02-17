#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_head;
	void	*f_content;

	new_head = NULL;
	while (lst)
	{
		f_content = f(lst->content);
		new_node = ft_lstnew(f_content);
		if (new_node == NULL)
		{
			del(f_content);
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		ft_lstadd_back(&new_head, new_node);
		lst = lst->next;
	}
	return (new_head);
}
