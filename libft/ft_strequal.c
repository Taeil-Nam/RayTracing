#include "libft.h"

int	ft_strequal(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}
