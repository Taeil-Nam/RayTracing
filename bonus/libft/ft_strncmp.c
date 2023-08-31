/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:55:47 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/16 17:44:14 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	i = 0;
	if (n == 0)
		return (0);
	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	while (i < n && s1_tmp[i] != '\0')
	{
		if (s1_tmp[i] != s2_tmp[i] || i == n - 1)
			return (s1_tmp[i] - s2_tmp[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
