#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*temp;
	unsigned char	c_tmp;

	index = 0;
	temp = (unsigned char *)b;
	c_tmp = (unsigned char)c;
	while (index < len)
	{
		temp[index] = c_tmp;
		index++;
	}
	return ((void *)temp);
}
