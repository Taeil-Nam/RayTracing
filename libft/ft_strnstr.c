#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_len;
	size_t	needle_len;
	size_t	i;

	i = 0;
	if (len == 0 && haystack == NULL)
		return (NULL);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	while (needle_len + i <= haystack_len && needle_len + i <= len)
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
