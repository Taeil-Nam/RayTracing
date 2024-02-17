#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len_with_null;
	size_t	i;

	len_with_null = ft_strlen(s) + 1;
	i = 0;
	c = (char)c;
	while (i < len_with_null)
	{
		if (s[i] == c)
			return ((char *)(&s[i]));
		i++;
	}
	return (NULL);
}
