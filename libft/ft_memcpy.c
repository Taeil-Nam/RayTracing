#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*src_temp;
	unsigned char	*dst_temp;
	size_t			index;

	if (dst == src)
		return (dst);
	index = 0;
	src_temp = (unsigned char *)src;
	dst_temp = (unsigned char *)dst;
	while (index < n)
	{
		dst_temp[index] = src_temp[index];
		index++;
	}
	return (dst);
}
