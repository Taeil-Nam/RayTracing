/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:12:32 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/18 18:32:56 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	c_tmp;

	i = 0;
	temp = (unsigned char *)s;
	c_tmp = (unsigned char)c;
	while (i < n)
	{
		if (temp[i] == c_tmp)
			return ((void *)(&temp[i]));
		i++;
	}
	return (NULL);
}
