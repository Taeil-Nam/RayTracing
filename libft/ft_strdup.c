#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_with_null;
	size_t	index;
	char	*copy;

	index = 0;
	len_with_null = ft_strlen(s1) + 1;
	copy = (char *)malloc(sizeof(char) * len_with_null);
	if (copy == NULL)
		return (NULL);
	while (s1[index])
	{
		copy[index] = s1[index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}
