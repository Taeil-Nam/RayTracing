/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:22:07 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/09 15:20:02 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
