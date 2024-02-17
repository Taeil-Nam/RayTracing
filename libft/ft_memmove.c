#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*dst_tmp;

	if (dst == src)
		return (dst);
	index = 0;
	dst_tmp = (unsigned char *)dst;
	if (dst >= src)
	{
		while (index < len)
		{
			dst_tmp[len - index - 1] = ((unsigned char *)src)[len - index - 1];
			index++;
		}
	}
	else
	{
		while (index < len)
		{
			dst_tmp[index] = ((unsigned char *)src)[index];
			index++;
		}
	}
	return (dst);
}
