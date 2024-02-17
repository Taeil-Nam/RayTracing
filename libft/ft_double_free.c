#include "libft.h"

void	ft_double_free(char **argv)
{
	char	**tmp;

	tmp = argv;
	if (argv == NULL)
		return ;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(argv);
}
