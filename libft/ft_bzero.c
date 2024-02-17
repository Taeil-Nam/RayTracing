#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*temp;

	index = 0;
	temp = (unsigned char *)s;
	while (index < n)
	{
		temp[index] = 0;
		index++;
	}
}
