#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		real_len;
	char	*substr;

	real_len = len;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		real_len = ft_strlen(s + start);
	substr = (char *)malloc(sizeof(char) * real_len + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, real_len + 1);
	return (substr);
}
