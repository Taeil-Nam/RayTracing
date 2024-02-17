#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	c_tmp;

	i = 0;
	temp = (unsigned char *)s;
	c_tmp = (unsigned char)c;
	while (i < n)
	{
		if (temp[i] == c_tmp)
			return ((void *)(&temp[i]));
		i++;
	}
	return (NULL);
}
