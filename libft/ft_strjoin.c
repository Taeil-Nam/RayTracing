#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(sizeof(char) * total_len);
	if (new_str == NULL)
		return (NULL);
	if (total_len == 1)
	{
		*new_str = '\0';
		return (new_str);
	}
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, s2, total_len);
	return (new_str);
}
