#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;
	char	*last_loc;
	char	c_tmp;

	index = 0;
	s_len = ft_strlen(s);
	c_tmp = (char)c;
	last_loc = NULL;
	while (index <= s_len)
	{
		if (s[index] == c_tmp)
			last_loc = (char *)(&(s[index]));
		index++;
	}
	return (last_loc);
}
